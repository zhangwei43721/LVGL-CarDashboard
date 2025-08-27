#!/bin/bash

# 检查参数数量
if [ "$#" -ne 1 ]; then
    echo "用法: $0 <pc|arm>"
    exit 1
fi

TARGET_ARCH=$1
LV_DRV_CONF_PATH="lv_drv_conf.h"
LV_CONF_PATH="lv_conf.h"

# 检查文件是否存在
if [ ! -f "$LV_DRV_CONF_PATH" ]; then
    echo "错误：未找到 lv_drv_conf.h 文件: $LV_DRV_CONF_PATH"
    exit 1
fi
if [ ! -f "$LV_CONF_PATH" ]; then
    echo "错误：未找到 lv_conf.h 文件: $LV_CONF_PATH"
    exit 1
fi

echo "正在为 '$TARGET_ARCH' 架构配置驱动和内核..."

if [ "$TARGET_ARCH" = "pc" ]; then
    # --- 配置 lv_drv_conf.h (驱动层) ---
    echo "配置 lv_drv_conf.h: 启用 SDL, 禁用 Framebuffer/evdev"
    sed -i 's/^\([[:space:]]*#\s*define\s*USE_SDL\s*\)[01]/#define USE_SDL 1/' "$LV_DRV_CONF_PATH"
    sed -i 's/^\([[:space:]]*#\s*define\s*USE_FBDEV\s*\)[01]/#define USE_FBDEV 0/' "$LV_DRV_CONF_PATH"
    sed -i 's/^\([[:space:]]*#\s*define\s*USE_EVDEV\s*\)[01]/#define USE_EVDEV 0/' "$LV_DRV_CONF_PATH"

    # --- 配置 lv_conf.h (内核层) ---
    echo "配置 lv_conf.h: 禁用自定义 Tick (LV_TICK_CUSTOM=0)，因为 SDL 会处理"
    sed -i 's/^\([[:space:]]*#\s*define\s*LV_TICK_CUSTOM\s*\)[01]/#define LV_TICK_CUSTOM 0/' "$LV_CONF_PATH"

elif [ "$TARGET_ARCH" = "arm" ]; then
    # --- 配置 lv_drv_conf.h (驱动层) ---
    echo "配置 lv_drv_conf.h: 禁用 SDL, 启用 Framebuffer/evdev"
    sed -i 's/^\([[:space:]]*#\s*define\s*USE_SDL\s*\)[01]/#define USE_SDL 0/' "$LV_DRV_CONF_PATH"
    sed -i 's/^\([[:space:]]*#\s*define\s*USE_FBDEV\s*\)[01]/#define USE_FBDEV 1/' "$LV_DRV_CONF_PATH"
    sed -i 's/^\([[:space:]]*#\s*define\s*USE_EVDEV\s*\)[01]/#define USE_EVDEV 1/' "$LV_DRV_CONF_PATH"

    # --- 配置 lv_conf.h (内核层) ---
    echo "配置 lv_conf.h: 启用自定义 Tick (LV_TICK_CUSTOM=1) 以使用 custom_tick_get()"
    sed -i 's/^\([[:space:]]*#\s*define\s*LV_TICK_CUSTOM\s*\)[01]/#define LV_TICK_CUSTOM 1/' "$LV_CONF_PATH"

else
    echo "无效参数: '$TARGET_ARCH'。请使用 'pc' 或 'arm'"
    exit 1
fi

echo "配置完成。"