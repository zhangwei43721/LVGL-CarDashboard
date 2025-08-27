#include <stdio.h>

#include "head.h"

// 事件回调函数
static void button_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);              // 获取事件代码
  lv_obj_t *label = (lv_obj_t *)lv_event_get_user_data(e);  // 获取用户数据

  if (code == LV_EVENT_CLICKED) {  // 判断是点击事件
    lv_label_set_text(label, "Hello, World!");
  }
}

// 事件回调函数2
static void button_event_handler2(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);              // 获取事件代码
  lv_obj_t *label = (lv_obj_t *)lv_event_get_user_data(e);  // 获取用户数据

  if (code == LV_EVENT_CLICKED) {  // 判断是点击事件
    lv_label_set_text(label, "clicked");
  }
}
static lv_style_t style_btn_green;
void obj_pos1(void) {
  // 创建基础面板
  lv_obj_t *parent_screen = lv_scr_act();          // 获取当前屏幕
  lv_obj_t *panel = lv_obj_create(parent_screen);  // 创建一个面板
  lv_obj_set_size(panel, 200, 200);                // 设置面板大小
  lv_obj_center(panel);                            // 将面板居中
  // 在面创建一个标签
  lv_obj_t *label = lv_label_create(panel);      // 创建一个标签
  lv_label_set_text(label, "Hello, World!");     // 设置标签文本
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);  // 标签顶部中对齐，并向下偏移20

  // 创建并设置按钮样式
  lv_style_init(&style_btn_green);
  lv_style_set_bg_color(&style_btn_green, lv_palette_main(LV_PALETTE_GREEN));
  lv_style_set_radius(&style_btn_green, 10);

  // 创建一个按钮,父对象是panel
  lv_obj_t *btn = lv_btn_create(panel);
  lv_obj_center(btn);                                         // 将按钮居中
  lv_obj_add_style(btn, &style_btn_green, LV_STATE_DEFAULT);  // 给按钮添加样式

  // 给按钮创建一个标签作为按钮的文本
  lv_obj_t *btn_label = lv_label_create(btn);
  lv_label_set_text(btn_label, "click me");
  lv_obj_center(btn_label);  // 将文字标签居中

  // 添加事件回调
  lv_obj_add_event_cb(btn, button_event_handler, LV_EVENT_CLICKED, label);

  // 创建第二个按钮,父对象是panel
  lv_obj_t *btn2 = lv_btn_create(panel);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 60);  // 放在第一个按钮的下面

  // 给按钮创建一个标签作为按钮的文本
  lv_obj_t *btn_label2 = lv_label_create(btn2);
  lv_label_set_text(btn_label2, "click me 2");
  lv_obj_center(btn_label2);  // 将文字标签居中
  lv_obj_add_event_cb(btn2, button_event_handler2, LV_EVENT_CLICKED, label);
}
void obj_sjpg_1(void) {
  // 声明图片数据所在的数组名称
  LV_IMG_DECLARE(abc);
  // 创建对象
  lv_obj_t *img1 = lv_img_create(lv_scr_act());
  // 加载指定图片
  lv_img_set_src(img1, &abc);
}

void obj_sjpg_2(void) {
  lv_obj_t *wp;
  wp = lv_img_create(lv_scr_act());
  lv_img_set_src(wp, "A:/mnt/nfs/small_image.sjpg");
}
void obj_freetype_text() {
  static lv_ft_info_t info;
  info.name = "./MiSans.ttf";
  info.weight = 24;
  info.style = FT_FONT_STYLE_NORMAL;
  info.mem = NULL;

  if (!lv_ft_font_init(&info)) {
    LV_LOG_ERROR("create failed.");
    return;
  }

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, info.font);
  lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_obj_add_style(label, &style, 0);
  lv_label_set_text(label, "你好\nI'm a font created with FreeType");
  lv_obj_center(label);
}

void lv_flex_test(void) {
  static lv_ft_info_t info;
  info.name = "./MiSans.ttf";
  info.weight = 14;
  info.style = FT_FONT_STYLE_NORMAL;
  info.mem = NULL;

  if (!lv_ft_font_init(&info)) {
    LV_LOG_ERROR("create failed.");
    return;
  }

  /*Create a container with ROW flex direction*/
  lv_obj_t *cont_row = lv_obj_create(lv_scr_act());
  lv_obj_set_size(cont_row, 300, 75);
  lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
  lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

  /*Create a container with COLUMN flex direction*/
  lv_obj_t *cont_col = lv_obj_create(lv_scr_act());
  lv_obj_set_size(cont_col, 200, 150);
  lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
  lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

  uint32_t i;
  for (i = 0; i < 10; i++) {
    lv_obj_t *obj;
    lv_obj_t *label;

    /*Add items to the row*/
    obj = lv_btn_create(cont_row);
    lv_obj_set_size(obj, 100, LV_PCT(100));

    label = lv_label_create(obj);
    lv_obj_set_style_text_font(label, info.font, 0);
    lv_label_set_text_fmt(label, "项目: %u", i);
    lv_obj_center(label);

    if (i == 5) {
      /* Create a container for the two buttons */
      lv_obj_t *btn_container = lv_obj_create(cont_col);
      lv_obj_set_size(btn_container, LV_PCT(100), LV_SIZE_CONTENT);
      lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_ROW);

      /* First button */
      obj = lv_btn_create(btn_container);
      lv_obj_set_size(obj, LV_PCT(50), LV_SIZE_CONTENT);
      label = lv_label_create(obj);
      lv_obj_set_style_text_font(label, info.font, 0);
      lv_label_set_text_fmt(label, "项目: %" LV_PRIu32 "-1", i);
      lv_obj_center(label);

      /* Second button */
      obj = lv_btn_create(btn_container);
      lv_obj_set_size(obj, LV_PCT(50), LV_SIZE_CONTENT);
      label = lv_label_create(obj);
      lv_obj_set_style_text_font(label, info.font, 0);
      lv_label_set_text_fmt(label, "项目: %" LV_PRIu32 "-2", i);
      lv_obj_center(label);
    } else {
      obj = lv_btn_create(cont_col);
      lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);

      label = lv_label_create(obj);
      lv_obj_set_style_text_font(label, info.font, 0);
      lv_label_set_text_fmt(label, "项目: %" LV_PRIu32, i);
      lv_obj_center(label);
    }
  }
}

void obj_pos2(void) {}
void obj_xx(void) {}