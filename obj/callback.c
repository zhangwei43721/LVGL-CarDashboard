#include <time.h>

#include "../UI/ui.h"
#include "head.h"

// 更新时间的定时器回调函数
static void update_time_timer_cb(lv_timer_t* timer) {
  // 获取当前时间
  time_t rawtime;
  struct tm* timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // 格式化时间字符串
  static char time_str[20];
  strftime(time_str, sizeof(time_str), "%H:%M", timeinfo);

  // 更新标签文本
  if (ui_TIME != NULL) {
    lv_label_set_text(ui_TIME, time_str);
  }
}

// Roller 模式选择与 ECO 图标联动
static void roller_value_changed_cb(lv_event_t* e) {
  LV_UNUSED(e);
  if (!ui_Roller1 || !ui_ECO) return;
  uint16_t sel = lv_roller_get_selected(ui_Roller1);
  if ((sel % 3) == 1) {
    /* 经济模式 */
    lv_obj_add_state(ui_ECO, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(ui_ECO, LV_STATE_CHECKED);
  }
}

void init_phase2_features(void) {
  // 绑定 Roller 的值改变事件
  if (ui_Roller1) {
    lv_obj_add_event_cb(ui_Roller1, roller_value_changed_cb, LV_EVENT_VALUE_CHANGED, NULL);
    // 根据当前初始选择同步 ECO 状态 
    roller_value_changed_cb(NULL);
  }
}

// 阶段二：为 Screen2 的四个面板标签设置固定文本
void init_screen2_static_data(void) {
  if (ui_Label1) lv_label_set_text(ui_Label1, "2.5 Kpa\n30°C");
  if (ui_Label3) lv_label_set_text(ui_Label3, "2.5 Kpa\n30°C");
  if (ui_Label4) lv_label_set_text(ui_Label4, "2.5 Kpa\n30°C");
  if (ui_Label5) lv_label_set_text(ui_Label5, "2.5 Kpa\n30°C");
}

void init_time_display(void) {  // 初始化时间显示控件
  lv_timer_create(update_time_timer_cb, 1000,
                  NULL);  // 创建定时器，每秒更新一次时间
}

static lv_timer_t* left_turn_signal_timer = NULL;
static lv_timer_t* right_turn_signal_timer = NULL;

// 设置使用 "CHECKED" 状态来控制亮/灭的灯光
// (适用于远光灯, ECO, 安全带, 发动机, 机油灯)
static void set_light_state_by_checked(lv_obj_t* light_obj, bool state) {
  if (light_obj == NULL) return;
  if (state) {
    lv_obj_add_state(light_obj, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(light_obj, LV_STATE_CHECKED);
  }
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

// 切换图标的可见性以产生闪烁效果
static void signal_flash_cb(lv_timer_t* timer) {
  lv_obj_t* signal_icon = (lv_obj_t*)timer->user_data;
  if (signal_icon) {
    if (lv_obj_has_flag(signal_icon, LV_OBJ_FLAG_HIDDEN)) {
      lv_obj_clear_flag(signal_icon, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(signal_icon, LV_OBJ_FLAG_HIDDEN);
    }
  }
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

// --- 指令解析函数 ---
static void process_command(char* cmd) {
  char target[50];
  char action[20];

  int items = sscanf(cmd, "%s %s", target, action);
  if (items != 2) {
    printf("无效指令, 格式应为: <目标> <动作> (例如: 远光灯 开)\n");
    return;
  }

  bool is_on = (strcmp(action, "开") == 0);

  if (strcmp(target, "远光灯") == 0) {
    set_light_state_by_checked(ui_High_beam, is_on);
  } else if (strcmp(target, "eco") == 0) {
    set_light_state_by_checked(ui_ECO, is_on);
  } else if (strcmp(target, "安全带") == 0) {
    set_light_state_by_checked(ui_seat_belt, is_on);
  } else if (strcmp(target, "发动机") == 0) {
    set_light_state_by_checked(ui_Engine, is_on);
  } else if (strcmp(target, "机油") == 0) {
    set_light_state_by_checked(ui_Low_engine_oil, is_on);
  } else if (strcmp(target, "水温报警") == 0) {
    set_light_state_by_hidden(ui_TempWarning, is_on);
  } else if (strcmp(target, "左转向") == 0) {
    control_manual_flashing(ui_Left, is_on, &left_turn_signal_timer);
  } else if (strcmp(target, "右转向") == 0) {
    control_manual_flashing(ui_Right, is_on, &right_turn_signal_timer);
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