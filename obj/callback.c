#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

#include "../UI/ui.h"
#include "head.h"

// 用户控制相关代码

// 更新时间的定时器回调函数
static void update_time_timer_cb(lv_timer_t* timer) {
  time_t rawtime;
  struct tm* timeinfo;
  time(&rawtime);  // 获取当前时间
  timeinfo = localtime(&rawtime);
  static char time_str[20];  // 格式化时间字符串
  strftime(time_str, sizeof(time_str), "%H:%M", timeinfo);
  if (ui_TIME != NULL) {  // 更新标签文本
    lv_label_set_text(ui_TIME, time_str);
  }
}

// Roller 模式选择与 ECO 图标联动
static void roller_value_changed_cb(lv_event_t* e) {
  LV_UNUSED(e);
  if (!ui_Roller1 || !ui_ECO) return;
  uint16_t sel = lv_roller_get_selected(ui_Roller1);
  if ((sel % 3) == 1) {
    lv_obj_add_state(ui_ECO, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(ui_ECO, LV_STATE_CHECKED);
  }
}
// 绑定 Roller 的值改变事件
void init_roller_event_handler(void) {
  if (ui_Roller1) {
    lv_obj_add_event_cb(ui_Roller1, roller_value_changed_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
    roller_value_changed_cb(NULL);  // 同步 ECO 状态
  }
}

void init_time_display(void) {  // 初始化时间显示控件
  lv_timer_create(update_time_timer_cb, 1000,
                  NULL);  // 创建定时器，每秒更新一次时间
}

static lv_timer_t* left_turn_signal_timer = NULL;
static lv_timer_t* right_turn_signal_timer = NULL;

// 设置切换 "CHECKED" 状态属性来控制亮/灭的灯光
// (适用于远光灯, ECO, 安全带, 发动机, 机油灯)
static void set_light_state_by_checked(lv_obj_t* light_obj, bool state) {
  if (light_obj == NULL) return;
  if (state) {
    lv_obj_add_state(light_obj, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(light_obj, LV_STATE_CHECKED);
  }
}

// 直接切换 CHECKED 状态
static void toggle_light_by_checked(lv_obj_t* obj) {
  if (!obj) return;
  // 检查当前状态并切换
  bool now_on = lv_obj_has_state(obj, LV_STATE_CHECKED);
  set_light_state_by_checked(obj, !now_on);
}

// 通过显示/隐藏来控制报警灯 (用于水温报警)
static void set_light_state_by_hidden(lv_obj_t* light_obj, bool state) {
  if (light_obj == NULL) return;
  if (state) {
    lv_obj_clear_flag(light_obj, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(light_obj, LV_OBJ_FLAG_HIDDEN);
  }
}

// 创建一个统一的灯光控制函数
static void set_all_lights_state(bool state) {
  // 常亮指示类
  set_light_state_by_checked(ui_High_beam, state);
  set_light_state_by_checked(ui_ECO, state);
  set_light_state_by_checked(ui_seat_belt, state);
  set_light_state_by_checked(ui_Engine, state);
  set_light_state_by_checked(ui_Low_engine_oil, state);

  // 报警灯
  set_light_state_by_hidden(ui_TempWarning, state);

  // 转向灯 (自检时只亮/灭，不闪烁)
  lv_obj_set_style_opa(ui_Left, state ? LV_OPA_COVER : 50, 0);
  lv_obj_set_style_opa(ui_Right, state ? LV_OPA_COVER : 50, 0);
}

// 创建一个定时器，用于产生闪烁效果
static void manual_flash_cb(lv_timer_t* timer) {
  lv_obj_t* signal_icon = (lv_obj_t*)timer->user_data;
  if (signal_icon) {
    lv_opa_t current_opa = lv_obj_get_style_opa(signal_icon, 0);
    if (current_opa == 255) {
      lv_obj_set_style_opa(signal_icon, 50, 0);
    } else {
      lv_obj_set_style_opa(signal_icon, 255, 0);
    }
  }
}

// 控制转向灯闪烁的开启与关闭
static void control_manual_flashing(lv_obj_t* signal_icon, bool state,
                                    lv_timer_t** timer_p) {
  if (state) {
    if (*timer_p == NULL) {
      printf("开启闪烁\n");
      lv_obj_set_style_opa(signal_icon, LV_OPA_COVER, 0);
      *timer_p = lv_timer_create(manual_flash_cb, 500, signal_icon);
    }
  } else {
    if (*timer_p != NULL) {
      printf("关闭闪烁\n");
      lv_timer_del(*timer_p);
      *timer_p = NULL;
      lv_obj_set_style_opa(signal_icon, 50, 0);
    }
  }
}

// 启动自检结束时关闭灯光的一次性回调
static void startup_selftest_off_cb(lv_timer_t* timer) {
  set_all_lights_state(false);
  lv_timer_del(timer);  // 删除自身
}

// 启动时点亮所有主要灯光，便于自检
void init_all_lights_test(void) {
  set_all_lights_state(true);
  // 2秒后自动关闭所有灯
  lv_timer_create(startup_selftest_off_cb, 2000, NULL);
}

// --- 指令解析函数 ---
static void process_command(char* cmd) {
  char target[50];
  char action[20] = {0};

  int items = sscanf(cmd, "%49s %19s", target, action);
  if (items == 1) {
    if (strcmp(target, "左转") == 0) {
      // 根据是否在闪烁来反转
      bool turning_on = (left_turn_signal_timer == NULL);
      if (right_turn_signal_timer != NULL) {
        control_manual_flashing(ui_Right, false, &right_turn_signal_timer);
      }
      control_manual_flashing(ui_Left, turning_on, &left_turn_signal_timer);
      return;
    } else if (strcmp(target, "右转") == 0) {
      bool turning_on = (right_turn_signal_timer == NULL);
      if (left_turn_signal_timer != NULL) {
        control_manual_flashing(ui_Left, false, &left_turn_signal_timer);
      }
      control_manual_flashing(ui_Right, turning_on, &right_turn_signal_timer);
      return;
    } else if (strcmp(target, "双闪") == 0) {
      bool turning_on =
          (left_turn_signal_timer == NULL && right_turn_signal_timer == NULL);
      control_manual_flashing(ui_Left, turning_on, &left_turn_signal_timer);
      control_manual_flashing(ui_Right, turning_on, &right_turn_signal_timer);
      return;
    } else if (strcmp(target, "远光") == 0) {
      toggle_light_by_checked(ui_High_beam);
      return;
    } else if (strcmp(target, "近光") == 0) {
      toggle_light_by_checked(ui_Low_beam);
      return;
    } else if (strcmp(target, "安全带") == 0) {
      toggle_light_by_checked(ui_seat_belt);
      return;
    }
  }

  if (items != 2) {
    printf(
        "无效指令！ 可输入：左转/右转/远光/近光/安全带\n"
        "\t\t或 胎压 <左前/右前/左后/右后> <kPa>\n");
    return;
  }

  if (strcmp(target, "双闪") == 0) {
    bool is_on = (strcmp(action, "开") == 0);
    control_manual_flashing(ui_Left, is_on, &left_turn_signal_timer);
    control_manual_flashing(ui_Right, is_on, &right_turn_signal_timer);
  } else if (strcmp(target, "速度") == 0) {
    parse_and_set_state_value(action, 0, 220, &g_vehicle_state.speed, "速度");
  } else if (strcmp(target, "转速") == 0) {
    parse_and_set_state_value(action, 0, 8000, &g_vehicle_state.rpm, "转速");
  } else if (strcmp(target, "水温") == 0) {
    parse_and_set_state_value(action, 0, 150, &g_vehicle_state.water_temp,
                              "水温");
  } else if (strcmp(target, "油量") == 0) {
    parse_and_set_state_value(action, 0, 100, &g_vehicle_state.fuel_level,
                              "油量");
  } else if (strcmp(target, "胎压") == 0) {
    // 需要从整行解析: 胎压 <位置> <数值>
    char pos[16];
    int val = -1;
    if (sscanf(cmd, "%*s %15s %d", pos, &val) != 2) {
      printf("无效胎压命令, 用法: 胎压 <左前/右前/左后/右后> <kPa>\n");
      return;
    }
    if (val < 0) val = 0;
    if (val > 500) val = 500;  // 合理上限
    if (strcmp(pos, "左前") == 0) {
      g_vehicle_state.tire_pressure_fl = val;
      printf("设置左前胎压=%d kPa\n", val);
    } else if (strcmp(pos, "右前") == 0) {
      g_vehicle_state.tire_pressure_fr = val;
      printf("设置右前胎压=%d kPa\n", val);
    } else if (strcmp(pos, "左后") == 0) {
      g_vehicle_state.tire_pressure_bl = val;
      printf("设置左后胎压=%d kPa\n", val);
    } else if (strcmp(pos, "右后") == 0) {
      g_vehicle_state.tire_pressure_br = val;
      printf("设置右后胎压=%d kPa\n", val);
    }
  } else {
    printf("未知目标: %s\n", target);
  }
}

void handle_console_input(void) {  // 非阻塞地检查和处理控制台输入
  fd_set fds;
  struct timeval tv;
  int ret;

  // 设置文件描述符集，我们只关心标准输入 (stdin), 它的文件描述符是 0
  FD_ZERO(&fds);
  FD_SET(0, &fds);

  tv.tv_sec = 0;  // 超时时间为 0，即立即返回，不阻塞
  tv.tv_usec = 0;

  ret = select(1, &fds, NULL, NULL, &tv);  // 检查标准输入是否可读

  if (ret > 0) {
    char buffer[100];                               // 可读，说明用户输入了内容
    if (read(0, buffer, sizeof(buffer) - 1) > 0) {  // 读取到 buffer
      buffer[strcspn(buffer, "\n")] = 0;            // 移除末尾的换行符
      process_command(buffer);                      // 处理命令
    }
  }
}