#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>  // io操作
#include <time.h>
#include <unistd.h>

// #include "lv_png.h"
#define SDL_MAIN_HANDLED
#include "lv_drivers/sdl/sdl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/lvgl.h"

// --- 常量定义 ---
#define WATER_TEMP_WARN 100
#define FUEL_LOW 10
#define TIRE_PRESSURE_MIN_OK 180
#define TIRE_PRESSURE_MAX_OK 280

// --- 车辆状态数据模型 ---
typedef struct {
  // --- 主要仪表数据 ---
  int speed;       // 速度 (0-220 km/h)
  int rpm;         // 转速 (0-8000 RPM)
  int water_temp;  // 水温 (0-150 °C)
  int fuel_level;  // 油量 (0-100 %)

  // --- 轮胎数据 ---
  int tire_pressure_fl;  // 左前胎压 (kPa)
  int tire_pressure_fr;  // 右前胎压
  int tire_pressure_bl;  // 左后胎压
  int tire_pressure_br;  // 右后胎压

  // --- 里程数据 ---
  float total_mileage;  // ODO 总里程 (km)
  float trip_mileage;   // TRIP 行程里程 (km)
} VehicleState;

// 全局状态单例
extern VehicleState g_vehicle_state;

// 根据 VehicleState 更新 UI 的渲染器（定时器回调）
void update_ui_from_state(lv_timer_t *timer);

// 解析并设置状态值的函数
bool parse_and_set_state_value(const char *str_val, int min, int max,
                               int *target_state, const char *name);

void init_time_display(void);          // 时间显示函数
void handle_console_input(void);       // 处理控制台输入的函数
void init_roller_event_handler(void);  // 绑定 Roller 事件并同步 ECO
void init_all_lights_test(void);       // 启动自检：点亮所有灯光

#endif /* __HEAD_H__ */