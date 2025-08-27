#include <stdlib.h>
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
    lv_obj_add_event_cb(ui_Roller1, roller_value_changed_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
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

// 平滑将图片角度动画到目标角度（单位：0.1度）
static void animate_img_angle_to(lv_obj_t* img, int16_t to_angle,
                                 uint32_t dur_ms) {
  if (!img) return;
  int16_t from_angle = 0;
#if LVGL_VERSION_MAJOR >= 8
  from_angle = lv_img_get_angle(img);
#endif
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, img);
  lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_angle);
  lv_anim_set_time(&a, dur_ms);
  lv_anim_set_values(&a, (int32_t)from_angle, (int32_t)to_angle);
  lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
  lv_anim_start(&a);
}

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

  int items = sscanf(cmd, "%49s %19s", target, action);
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
  } else if (strcmp(target, "速度") == 0) {
    char* endp = NULL;
    long v = strtol(action, &endp, 10);
    if (endp == action) {
      printf("无效速度值: %s\n", action);
      return;
    }
    if (v < 0) v = 0;
    if (v > 220) v = 220;
    g_vehicle_state.speed = (int)v;
    printf("设置速度=%d km/h\n", (int)v);
  } else if (strcmp(target, "转速") == 0) {
    char* endp = NULL;
    long v = strtol(action, &endp, 10);
    if (endp == action) {
      printf("无效转速值: %s\n", action);
      return;
    }
    if (v < 0) v = 0;
    if (v > 8000) v = 8000;
    g_vehicle_state.rpm = (int)v;
    printf("设置转速=%d RPM\n", (int)v);
  } else if (strcmp(target, "水温") == 0) {
    char* endp = NULL;
    long v = strtol(action, &endp, 10);
    if (endp == action) {
      printf("无效水温值: %s\n", action);
      return;
    }
    if (v < 0) v = 0;
    if (v > 150) v = 150;
    g_vehicle_state.water_temp = (int)v;
    printf("设置水温=%d °C\n", (int)v);
  } else if (strcmp(target, "油量") == 0) {
    char* endp = NULL;
    long v = strtol(action, &endp, 10);
    if (endp == action) {
      printf("无效油量值: %s\n", action);
      return;
    }
    if (v < 0) v = 0;
    if (v > 100) v = 100;
    g_vehicle_state.fuel_level = (int)v;
    printf("设置油量=%d %%\n", (int)v);
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
    } else {
      printf("未知位置: %s，应为 左前/右前/左后/右后\n", pos);
      return;
    }
  } else if (strcmp(target, "左转向") == 0) {
    control_manual_flashing(ui_Left, is_on, &left_turn_signal_timer);
  } else if (strcmp(target, "右转向") == 0) {
    control_manual_flashing(ui_Right, is_on, &right_turn_signal_timer);
  } else if (strncmp(target, "表", 3) == 0 || strncmp(target, "表", 2) == 0) {
    // 阶段三：数据驱动。表命令不再直接操作 UI，而是反向映射更新 g_vehicle_state
    int gauge_index = -1;
    if (strcmp(target, "表一") == 0 || strcmp(target, "表1") == 0)
      gauge_index = 1;  // 水温
    else if (strcmp(target, "表二") == 0 || strcmp(target, "表2") == 0)
      gauge_index = 2;  // 速度
    else if (strcmp(target, "表三") == 0 || strcmp(target, "表3") == 0)
      gauge_index = 3;  // 转速
    else if (strcmp(target, "表四") == 0 || strcmp(target, "表4") == 0)
      gauge_index = 4;  // 油量

    if (gauge_index < 0) {
      printf("未知表目标: %s，应为 表一/表二/表三/表四 或 表1..表4\n", target);
      return;
    }

    char* endp = NULL;
    long deg = strtol(action, &endp, 10);  // 输入单位：度
    if (endp == action) {
      printf("角度无效: %s，应输入整数角度(度)\n", action);
      return;
    }

    // 约束角度并反向映射到领域数据
    switch (gauge_index) {
      case 1: {  // 水温：0..90度 -> 0..150°C
        if (deg < 0) deg = 0;
        if (deg > 90) deg = 90;
        int water = (int)(deg * (150.0f / 90.0f) + 0.5f);
        g_vehicle_state.water_temp = water;
        printf("设置水温=%d°C (由角度%ld°反推)\n", water, deg);
        break;
      }
      case 2: {  // 速度：0..245度 -> 0..220 km/h
        if (deg < 0) deg = 0;
        if (deg > 245) deg = 245;
        int speed = (int)(deg * (220.0f / 245.0f) + 0.5f);
        g_vehicle_state.speed = speed;
        printf("设置速度=%d km/h (由角度%ld°反推)\n", speed, deg);
        break;
      }
      case 3: {  // 转速：0..243度 -> 0..8000 rpm
        if (deg < 0) deg = 0;
        if (deg > 243) deg = 243;
        int rpm = (int)(deg * (8000.0f / 243.0f) + 0.5f);
        g_vehicle_state.rpm = rpm;
        printf("设置转速=%d RPM (由角度%ld°反推)\n", rpm, deg);
        break;
      }
      case 4: {  // 油量：0..90度(相对) -> 0..100%
        if (deg < 0) deg = 0;
        if (deg > 90) deg = 90;
        int fuel = (int)(deg * (100.0f / 90.0f) + 0.5f);
        g_vehicle_state.fuel_level = fuel;
        printf("设置油量=%d%% (由角度%ld°反推)\n", fuel, deg);
        break;
      }
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