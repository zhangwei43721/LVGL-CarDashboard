#include "../UI/ui.h"
#include "head.h"

// 联动控制相关代码


// 全局车辆状态
VehicleState g_vehicle_state = {
    .speed = 20,                // 车速 (km/h)
    .rpm = 1000,                // 发动机转速 (转/分钟)
    .water_temp = 60,           // 水温 (摄氏度)
    .fuel_level = 50,           // 燃油量 (百分比)
    .tire_pressure_fl = 250,    // 左前轮胎压力 (kPa)
    .tire_pressure_fr = 250,    // 右前轮胎压力 (kPa)
    .tire_pressure_bl = 250,    // 左后轮胎压力 (kPa)
    .tire_pressure_br = 250,    // 右后轮胎压力 (kPa)
    .total_mileage = 16863.0f,  // 总里程 (公里)
    .trip_mileage = 136.0f,     // 行程里程 (公里)
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
// 速度表角度映射
static int value_to_angle_speed(int speed_kmh) {  // 0..220 -> 0..2450
  speed_kmh = clamp_i(speed_kmh, 0, 220);
  return (int)((2450.0f / 220.0f) * speed_kmh);
}
// 转速角度映射
static int value_to_angle_rpm(int rpm) {  // 0..8000 -> 0..2430
  rpm = clamp_i(rpm, 0, 8000);
  return (int)((2430.0f / 8000.0f) * rpm);
}
// 水温角度映射
static int value_to_angle_water(int temp_c) {  // 0..150 -> 0..900
  temp_c = clamp_i(temp_c, 0, 150);
  return (int)((900.0f / 150.0f) * temp_c);
}
// 油量角度映射
static int value_to_angle_fuel(int percent) {  // 0..100 -> base(900)+0..900
  percent = clamp_i(percent, 0, 100);
  return 900 + (int)((900.0f / 100.0f) * percent);
}
// 从状态结构体更新所有指针的角度
static void update_all_pointers_from_state(uint32_t anim_ms) {
  // 速度表
  if (ui_KmPoint) {
    int ang = value_to_angle_speed(g_vehicle_state.speed);
    animate_img_angle_to(ui_KmPoint, (int16_t)ang, anim_ms);
  }
  // 转速表
  if (ui_TMeterpoint) {
    int ang = value_to_angle_rpm(g_vehicle_state.rpm);
    animate_img_angle_to(ui_TMeterpoint, (int16_t)ang, anim_ms);
  }
  // 水温
  if (ui_TempPoint) {
    int ang_rel = value_to_angle_water(g_vehicle_state.water_temp);  // 0..900
    animate_img_angle_to(ui_TempPoint, (int16_t)ang_rel, anim_ms);
  }
  // 油量（带基准）
  if (ui_OilPoint) {
    int ang_abs = value_to_angle_fuel(g_vehicle_state.fuel_level);
    animate_img_angle_to(ui_OilPoint, (int16_t)ang_abs, anim_ms);
  }
}
// 更新所有胎压显示
static void update_tire_pressure_display(void) {
  if (ui_Label3) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%dkPa", g_vehicle_state.tire_pressure_fl);
    lv_label_set_text(ui_Label3, buf);
    bool warn = (g_vehicle_state.tire_pressure_fl < 180 ||
                 g_vehicle_state.tire_pressure_fl > 280);
    lv_obj_set_style_text_color(
        ui_Label3, warn ? lv_color_hex(0xC71616) : lv_color_hex(0xFFFFFF),
        LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  if (ui_Label1) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%dkPa", g_vehicle_state.tire_pressure_fr);
    lv_label_set_text(ui_Label1, buf);
    bool warn = (g_vehicle_state.tire_pressure_fr < 180 ||
                 g_vehicle_state.tire_pressure_fr > 280);
    lv_obj_set_style_text_color(
        ui_Label1, warn ? lv_color_hex(0xC71616) : lv_color_hex(0xFFFFFF),
        LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  if (ui_Label4) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%dkPa", g_vehicle_state.tire_pressure_bl);
    lv_label_set_text(ui_Label4, buf);
    bool warn = (g_vehicle_state.tire_pressure_bl < 180 ||
                 g_vehicle_state.tire_pressure_bl > 280);
    lv_obj_set_style_text_color(
        ui_Label4, warn ? lv_color_hex(0xC71616) : lv_color_hex(0xFFFFFF),
        LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  if (ui_Label5) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%dkPa", g_vehicle_state.tire_pressure_br);
    lv_label_set_text(ui_Label5, buf);
    bool warn = (g_vehicle_state.tire_pressure_br < 180 ||
                 g_vehicle_state.tire_pressure_br > 280);
    lv_obj_set_style_text_color(
        ui_Label5, warn ? lv_color_hex(0xC71616) : lv_color_hex(0xFFFFFF),
        LV_PART_MAIN | LV_STATE_DEFAULT);
  }
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
    if (g_vehicle_state.water_temp > 100)
      lv_obj_clear_flag(ui_TempWarning, LV_OBJ_FLAG_HIDDEN);
    else
      lv_obj_add_flag(ui_TempWarning, LV_OBJ_FLAG_HIDDEN);
  }
  // 低油量灯
  if (ui_Low_engine_oil) {
    if (g_vehicle_state.fuel_level < 10)
      lv_obj_add_state(ui_Low_engine_oil, LV_STATE_CHECKED);
    else
      lv_obj_clear_state(ui_Low_engine_oil, LV_STATE_CHECKED);
  }
}
// 更新UI
void update_ui_from_state(lv_timer_t* timer) {
  uint32_t period = timer ? timer->period : 100;  // 兜底 100ms
  float dt_s = period / 1000.0f;

  // 过温保护限转速
  // 超过110°C时将转速限制到3000 RPM
  if (g_vehicle_state.water_temp >= 110 && g_vehicle_state.rpm > 3000) {
    g_vehicle_state.rpm = 3000;
  }

  // 水温动态（升温与冷却）
  // - 转速越高升温越快：最大转速(8000)时 +0.08 °C/s
  // - 车速越快升温越快：最大车速(220 km/h)时 +0.04 °C/s
  // - 向目标温度(90°C)以 0.06 °C/s 进行冷却/回升
  float heat_rpm = 0.08f * (g_vehicle_state.rpm / 8000.0f);
  float heat_speed = 0.04f * (g_vehicle_state.speed / 220.0f);
  float cool = 0.0f;
  if (g_vehicle_state.water_temp > 90) {
    cool = 0.06f;
  } else if (g_vehicle_state.water_temp < 90) {
    cool = -0.06f;
  }
  float new_temp =
      g_vehicle_state.water_temp + (heat_rpm + heat_speed - cool) * dt_s;
  g_vehicle_state.water_temp = clamp_i((int)(new_temp + 0.5f), 0, 150);

  // 1. 指针
  update_all_pointers_from_state(300);
  // 2. 胎压
  update_tire_pressure_display();
  // 3. 里程
  update_mileage_labels(period);
  // 4. 告警
  check_and_update_warnings();
}
