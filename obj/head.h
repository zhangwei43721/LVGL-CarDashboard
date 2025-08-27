#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
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

void init_time_display(void);     // 时间显示函数
void handle_console_input(void);  // 处理控制台输入的函数
void init_phase2_features(void);   // 绑定 Roller 事件并同步 ECO
void init_screen2_static_data(void); // 设置 Screen2 的静态胎压与温度值

lv_anim_t * Leftflash_Animation(lv_obj_t * TargetObject, int delay);
lv_anim_t * Rightflash_Animation(lv_obj_t * TargetObject, int delay);

#endif /* __HEAD_H__ */