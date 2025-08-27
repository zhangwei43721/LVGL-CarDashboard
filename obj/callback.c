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

// 初始化时间显示控件
void init_time_display(void) {
  // 创建定时器，每秒更新一次时间
  lv_timer_create(update_time_timer_cb, 1000, NULL);
}