# LVGL for frame buffer device

LVGL configured to work with /dev/fb0 on Linux.

When cloning this repository, also make sure to download submodules (`git submodule update --init --recursive`) otherwise you will be missing key components.

Check out this blog post for a step by step tutorial:
https://blog.lvgl.io/2018-01-03/linux_fb

## 项目结构

该项目是 LVGL 图形库在 Linux 平台下的一个移植模板，其结构清晰，模块化，主要包含以下部分：

*   **`main.c`**: 应用程序的主入口文件。LVGL的初始化、驱动注册以及UI界面的创建都在这里完成。

*   **`lvgl/`**: 核心的 LVGL 图形库。它以git子模块的形式被包含。这里包含了所有UI控件（按钮、标签、图表等）、渲染引擎和动画框架。

*   **`lv_drivers/`**: LVGL的驱动集合，同样以git子模块的形式存在。它负责将LVGL的绘图指令连接到具体的显示后端（如 Framebuffer, SDL），并从输入设备（如鼠标、键盘、触摸屏）读取数据。

*   **`lv_conf.h`**: LVGL库的配置文件，用于启用/禁用特性、调整内存缓冲区大小等。

*   **`lv_drv_conf.h`**: `lv_drivers` 驱动库的配置文件。

*   **`CMakeLists.txt` & `Makefile`**: 项目的构建系统文件。定义了如何编译源代码、链接库文件，并最终生成可执行文件。

*   **`build/`**: 默认的编译输出目录。CMake生成的所有中间文件和最终的可执行文件都存放在这里。