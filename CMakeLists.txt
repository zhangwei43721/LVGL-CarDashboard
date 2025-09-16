cmake_minimum_required(VERSION 3.12)
project(main C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# --- 平台检测与配置 ---
set(TARGET_PLATFORM "unknown")

if(CMAKE_CROSSCOMPILING)
    # ARM 平台
    set(TARGET_PLATFORM "arm")
    add_library(freetype_local SHARED IMPORTED GLOBAL)
    set_target_properties(freetype_local PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype/lib/arm/libfreetype.so"
    )
    set(PLATFORM_LIBS pthread freetype_local m)

elseif(WIN32)
    # Windows 平台
    set(TARGET_PLATFORM "win")
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    set(PLATFORM_LIBS ${SDL2_LIBRARIES} Threads::Threads freetype m)

elseif(UNIX AND NOT APPLE)
    # Linux PC 平台
    set(TARGET_PLATFORM "pc")
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS SDL2::SDL2 Threads::Threads freetype m)
else()
    message(FATAL_ERROR "不支持的平台或操作系统！")
endif()

message(STATUS "检测到目标平台: ${TARGET_PLATFORM}")

# --- 动态修改配置文件 ---
set(LV_DRV_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_drv_conf.h")
set(LV_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h")
file(READ ${LV_DRV_CONF_PATH} LV_DRV_CONF_CONTENT)
file(READ ${LV_CONF_PATH} LV_CONF_CONTENT)
if(TARGET_PLATFORM STREQUAL "pc" OR TARGET_PLATFORM STREQUAL "win")
    message(STATUS "配置驱动: 启用 SDL, 禁用 Framebuffer/evdev")
    string(REGEX REPLACE "(#define[ \t]+USE_SDL[ \t]+)[01]" "\\11" LV_DRV_CONF_CONTENT "${LV_DRV_CONF_CONTENT}")
    string(REGEX REPLACE "(#define[ \t]+USE_FBDEV[ \t]+)[01]" "\\10" LV_DRV_CONF_CONTENT "${LV_DRV_CONF_CONTENT}")
    string(REGEX REPLACE "(#define[ \t]+USE_EVDEV[ \t]+)[01]" "\\10" LV_DRV_CONF_CONTENT "${LV_DRV_CONF_CONTENT}")
    message(STATUS "配置内核: 禁用 LV_TICK_CUSTOM (由 SDL 提供 tick)")
    string(REGEX REPLACE "(#define[ \t]+LV_TICK_CUSTOM[ \t]+)[01]" "\\10" LV_CONF_CONTENT "${LV_CONF_CONTENT}")
elseif(TARGET_PLATFORM STREQUAL "arm")
    message(STATUS "配置驱动: 禁用 SDL, 启用 Framebuffer/evdev")
    string(REGEX REPLACE "(#define[ \t]+USE_SDL[ \t]+)[01]" "\\10" LV_DRV_CONF_CONTENT "${LV_DRV_CONF_CONTENT}")
    string(REGEX REPLACE "(#define[ \t]+USE_FBDEV[ \t]+)[01]" "\\11" LV_DRV_CONF_CONTENT "${LV_DRV_CONF_CONTENT}")
    string(REGEX REPLACE "(#define[ \t]+USE_EVDEV[ \t]+)[01]" "\\11" LV_DRV_CONF_CONTENT "${LV_DRV_CONF_CONTENT}")
    message(STATUS "配置内核: 启用 LV_TICK_CUSTOM (使用 custom_tick_get)")
    string(REGEX REPLACE "(#define[ \t]+LV_TICK_CUSTOM[ \t]+)[01]" "\\11" LV_CONF_CONTENT "${LV_CONF_CONTENT}")
endif()
file(WRITE ${LV_DRV_CONF_PATH} "${LV_DRV_CONF_CONTENT}")
file(WRITE ${LV_CONF_PATH} "${LV_CONF_CONTENT}")
message(STATUS "配置文件修改完成。")


include_directories(
    .
    libs/freetype/include
    UI
    lvgl
    lv_drivers
    # lv_demos 
    # lv_examples
)

# --- 源文件 ---
file(GLOB_RECURSE ALL_SOURCES
    "lvgl/src/*.c"
    "lv_drivers/*.c"
    # "lvgl/demos/*.c" 
    # "lvgl/examples/*.c" 
    "UI/*.c"
    "obj/*.c"
)

# --- 构建主程序 ---
add_executable(${PROJECT_NAME} main.c  ${ALL_SOURCES})

# --- 链接平台库 ---
target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})