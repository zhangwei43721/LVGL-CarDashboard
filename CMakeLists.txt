cmake_minimum_required(VERSION 3.12)
project(main C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# --- 平台配置 ---
if(CMAKE_CROSSCOMPILING)
    set(TARGET_ARCH "arm")
    set(PLATFORM_LIBS pthread freetype m)
else() # PC
    set(TARGET_ARCH "pc")
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS SDL2::SDL2 Threads::Threads freetype m)
endif()

link_directories("libs/freetype/lib/${TARGET_ARCH}")

execute_process(COMMAND bash configure.sh ${TARGET_ARCH} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# --- 头文件 ---
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
)

# --- 构建主程序 ---
add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c ${ALL_SOURCES})

# --- 链接平台库 ---
target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})