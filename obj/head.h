#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <time.h>
#include <unistd.h>

// #include "lv_png.h"
#define SDL_MAIN_HANDLED
#include "lv_drivers/sdl/sdl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/lvgl.h"

void init_time_display(void);  // 时间显示函数

#endif /* __HEAD_H__ */