#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <unistd.h>

// #include "lv_png.h"
#define SDL_MAIN_HANDLED
#include "lv_drivers/sdl/sdl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/lvgl.h"

void obj_pos1(void);
void obj_xx(void);
void obj_sjpg_1(void);
void obj_sjpg_2(void);
void obj_freetype_text(void);
void lv_flex_test(void);

#endif /* __HEAD_H__ */