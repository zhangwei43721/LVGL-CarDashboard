#include "head.h"

// 联动控制相关代码

// 全局车辆状态
VehicleState g_vehicle_state = {
    .speed = 0,                 // 车速 (km/h)
    .rpm = 0,                   // 发动机转速 (转/分钟)
    .water_temp = 40,           // 水温 (摄氏度)
    .fuel_level = 50,           // 燃油量 (百分比)

    .tire_pressure_fl = 250,    // 左前轮胎压力 (kPa)
    .tire_pressure_fr = 250,    // 右前轮胎压力 (kPa)
    .tire_pressure_bl = 250,    // 左后轮胎压力 (kPa)
    .tire_pressure_br = 250,    // 右后轮胎压力 (kPa)

    .total_mileage = 16863.0f,  // 总里程 (公里)
    .trip_mileage = 0.0f,       // 本次行程里程 (公里)
};

// 将值限制在 [min_v, max_v] 范围内，整形
static inline int clamp_i(int v, int min_v, int max_v) {
  if (v < min_v) return min_v;
  if (v > max_v) return max_v;
  return v;
}
// 将值限制在 [min_v, max_v] 范围内，浮点型
static inline float clamp_f(float v, float min_v, float max_v) {
  if (v < min_v) return min_v;
  if (v > max_v) return max_v;
  return v;
}

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

// 值到角度的映射（返回 0.1度）
// 通用的映射函数，取代之前所有的 value_to_angle_* 函数
static int map_value_to_angle(int value, int val_min, int val_max,
                              int angle_min, int angle_max) {
  // 防止除以零
  if (val_max == val_min) return angle_min;
  // 使用浮点数进行精确计算
  float ratio = (float)(value - val_min) / (val_max - val_min);
  int angle = angle_min + (int)(ratio * (angle_max - angle_min));
  // 确保结果在角度范围内
  return clamp_i(angle, angle_min, angle_max);
}

// 从状态结构体更新所有指针的角度
static void update_all_pointers_from_state(uint32_t anim_ms) {
  animate_img_angle_to(  // 速度表
      ui_KmPoint, map_value_to_angle(g_vehicle_state.speed, 0, 220, 0, 2450),
      anim_ms);
  animate_img_angle_to(  // 转速表
      ui_TMeterpoint, map_value_to_angle(g_vehicle_state.rpm, 0, 8000, 0, 2430),
      anim_ms);
  animate_img_angle_to(  // 水温
      ui_TempPoint,
      map_value_to_angle(g_vehicle_state.water_temp, 0, 150, 0, 900), anim_ms);
  animate_img_angle_to(  // 油量 (注意油量指针有900度的基准偏移)
      ui_OilPoint,
      map_value_to_angle(g_vehicle_state.fuel_level, 0, 100, 900, 1800),
      anim_ms);
}

// 更新单个轮胎显示的辅助函数
static void update_a_tire_display(lv_obj_t* label, int pressure) {
  if (!label) return;

  char buf[32];
  snprintf(buf, sizeof(buf), "%dkPa", pressure);
  lv_label_set_text(label, buf);

  bool is_warning =
      (pressure < TIRE_PRESSURE_MIN_OK || pressure > TIRE_PRESSURE_MAX_OK);
  lv_color_t color =
      is_warning ? lv_color_hex(0xC71616) : lv_color_hex(0xFFFFFF);
  lv_obj_set_style_text_color(label, color, LV_PART_MAIN | LV_STATE_DEFAULT);
}

// 更新所有胎压显示
static void update_tire_pressure_display(void) {
  update_a_tire_display(ui_Label3, g_vehicle_state.tire_pressure_fl);
  update_a_tire_display(ui_Label1, g_vehicle_state.tire_pressure_fr);
  update_a_tire_display(ui_Label4, g_vehicle_state.tire_pressure_bl);
  update_a_tire_display(ui_Label5, g_vehicle_state.tire_pressure_br);
}

// 创建一个通用的解析和设置函数
bool parse_and_set_state_value(const char* str_val, int min, int max,
                               int* target_state, const char* name) {
  char* endp = NULL;
  long v = strtol(str_val, &endp, 10);
  if (endp == str_val || *endp != '\0') {
    printf("无效数值: %s\n", str_val);
    return false;
  }
  *target_state = clamp_i((int)v, min, max);  // 使用已有的 clamp_i 函数
  printf("设置%s=%d\n", name, *target_state);
  return true;
}

// 更新里程显示
static void update_mileage_labels(uint32_t period_ms) {
  // 速度 km/h -> 增量 km： v * (period_ms/3600000)
  float delta_km = (g_vehicle_state.speed / 3600000.0f) * period_ms;
  g_vehicle_state.total_mileage =
      clamp_f(g_vehicle_state.total_mileage + delta_km, 0.f, 1e9f);
  g_vehicle_state.trip_mileage =
      clamp_f(g_vehicle_state.trip_mileage + delta_km, 0.f, 1e9f);

  if (ui_ODO) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d",
             (int)(g_vehicle_state.total_mileage + 0.5f));
    lv_label_set_text(ui_ODO, buf);
  }
  if (ui_TRIP) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d",
             (int)(g_vehicle_state.trip_mileage + 0.5f));
    lv_label_set_text(ui_TRIP, buf);
  }
}
// 检查并更新所有报警
static void check_and_update_warnings(void) {
  // 水温报警
  if (ui_TempWarning) {
    if (g_vehicle_state.water_temp > WATER_TEMP_WARN)
      lv_obj_clear_flag(ui_TempWarning, LV_OBJ_FLAG_HIDDEN);
    else
      lv_obj_add_flag(ui_TempWarning, LV_OBJ_FLAG_HIDDEN);
  }
  // 低油量灯
  if (ui_Low_engine_oil) {
    if (g_vehicle_state.fuel_level < FUEL_LOW)
      lv_obj_add_state(ui_Low_engine_oil, LV_STATE_CHECKED);
    else
      lv_obj_clear_state(ui_Low_engine_oil, LV_STATE_CHECKED);
  }
}
// 更新UI
void update_ui_from_state(lv_timer_t* timer) {
  uint32_t period = timer ? timer->period : 100;  // 兜底 100ms
  float dt_s = period / 1000.0f;
  // 启动前2秒为自检阶段：不覆盖灯光状态
  static uint32_t self_test_end_ms = 0;
  if (self_test_end_ms == 0) self_test_end_ms = lv_tick_get() + 2000;
  update_all_pointers_from_state(300);  // 指针
  update_tire_pressure_display();       // 胎压
  update_mileage_labels(period);        // 里程
  // 告警（自检阶段内跳过，以免覆盖全亮自检）
  if (lv_tick_get() >= self_test_end_ms) {
    check_and_update_warnings();
  }
}