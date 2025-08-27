/**
 * @file main
 * @brief 整合了 PC 和 ARM 平台的启动代码
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>

// 驱动配置文件
#include "lv_drv_conf.h"

// LVGL 核心库
#include "lvgl/lvgl.h"

// UI 代码头文件
#include "obj/head.h"
#include "UI/ui.h"

// 添加对examples的引用
#include "lvgl/examples/lv_examples.h"

// 根据 lv_drv_conf.h 中的 USE_SDL 宏来包含不同的平台驱动头文件
#if USE_SDL
    /* ========================= */
    /*     PC/SDL 平台头文件      */
    /* ========================= */
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL.h>
    #include "lv_drivers/sdl/sdl.h"
#else
    /* ================================ */
    /*     ARM/Framebuffer 平台头文件     */
    /* ================================ */
    #include "lv_drivers/display/fbdev.h"
    #include "lv_drivers/indev/evdev.h"
    #include <sys/time.h>
    uint32_t custom_tick_get(void); // ARM 平台 tick 函数声明
#endif


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int main(int argc, char **argv)
{
    (void)argc; /* Unused */
    (void)argv; /* Unused */

    /* 初始化 LVGL */
    lv_init();

    /* 初始化 HAL (显示, 输入设备, tick) */
    hal_init();

    /* === 调用 UI 代码 === */
    // obj_pos1();
    ui_init();

    
    // obj_sjpg_1();  // 用图片数组显示
    // obj_sjpg_2();  // 用指定路径显示 
    // obj_freetype_text();// 显示文字
    // lv_flex_test();   // 布局测试
    /* 主循环 */
    while(1) {
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief 初始化硬件抽象层 (HAL)
 *        根据 USE_SDL 的值选择初始化 PC/SDL 平台或 ARM/Framebuffer 平台
 */
static void hal_init(void)
{
#if USE_SDL
    /* ================================== */
    /*          PC/SDL 平台初始化           */
    /* ================================== */
    sdl_init();

    /* 创建一个显示缓冲区 */
    static lv_disp_draw_buf_t disp_buf1;
    static lv_color_t buf1_1[SDL_HOR_RES * 100];
    lv_disp_draw_buf_init(&disp_buf1, buf1_1, NULL, SDL_HOR_RES * 100);

    /* 创建一个显示驱动 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf1;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_t * disp = lv_disp_drv_register(&disp_drv);

    /* 设置默认主题 */
    lv_theme_t * th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
    lv_disp_set_theme(disp, th);

    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);

    /* 添加鼠标输入设备 */
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv_1);

    /* 添加键盘输入设备 */
    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2);
    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = sdl_keyboard_read;
    lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
    lv_indev_set_group(kb_indev, g);
    
    /* 添加鼠标滚轮输入设备 */
    static lv_indev_drv_t indev_drv_3;
    lv_indev_drv_init(&indev_drv_3);
    indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_3.read_cb = sdl_mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&indev_drv_3);
    lv_indev_set_group(enc_indev, g);

#else
    /* ======================================= */
    /*              ARM 平台初始化              */
    /* ======================================= */
    #define DISP_BUF_SIZE (128 * 1024)

    fbdev_init();

    static lv_color_t buf[DISP_BUF_SIZE];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act());
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse_indev, cursor_obj);

#endif
}

#if !USE_SDL
/**
 * @brief ARM/fbdev 平台 tick 获取函数实现
 */
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
#endif