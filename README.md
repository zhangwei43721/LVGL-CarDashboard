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

---

## 使用说明（PC/SDL）

以下步骤在 Linux 下测试通过：

1. 获取子模块
   ```bash
   git submodule update --init --recursive
   ```
2. 配置与编译
   ```bash
   cmake -S . -B build
   cmake --build build -j
   ```
3. 运行
   ```bash
   ./bin/main
   ```

程序启动后会打开 SDL 窗口。主循环每 5ms 轮询 LVGL，同时每 100ms 通过定时器将“车辆状态数据模型”渲染到 UI。

启动后前 2 秒会进入“自检模式”，所有主要灯光将被点亮，方便检查灯光是否损坏；自检结束后恢复正常联动与告警逻辑。

## 控制台指令（实时模拟）

在程序运行的同时，直接在终端输入命令来模拟仪表数据。

简化指令（直接反转灯状态）：

- `左转`
- `右转`
- `远光`
- `安全带`

设置指令：`<目标> <数值>` 或 `胎压 <位置> <kPa>`。

- 速度：`速度 0..220`（km/h）
- 转速：`转速 0..8000`（RPM）
- 水温：`水温 0..150`（°C）
- 油量：`油量 0..100`（%）
- 胎压：`胎压 左前|右前|左后|右后 <0..500>`（kPa）

直接设置“表” 命令（将角度反向映射为数据）：

- `表一 0..90`   → 水温（0..150°C）
- `表二 0..245`  → 速度（0..220 km/h）
- `表三 0..243`  → 转速（0..8000 RPM）
- `表四 0..90`   → 油量（0..100%）

Roller 与 ECO 联动：滚轮选中索引 mod 3 == 1 时点亮 ECO

## 数据驱动与联动规则

- 单一数据源：`obj/head.h` 中定义 `VehicleState`，全局实例为 `g_vehicle_state`。
- 定时渲染：`obj/control.c::update_ui_from_state()` 每 100ms 根据 `g_vehicle_state` 更新：
  - 指针动画：`ui_KmPoint`（速度）、`ui_TMeterpoint`（转速）、`ui_TempPoint`（水温）、`ui_OilPoint`（油量）
  - 标签更新：四个胎压标签文本与颜色、`ui_ODO`、`ui_TRIP`
  - 告警逻辑：
    - 水温报警：`water_temp > 100°C` → 显示 `ui_TempWarning`
    - 低油量：`fuel_level < 10%` → 置 `ui_Low_engine_oil` 为 CHECKED
    - 胎压文字变红：`< 180` 或 `> 280 kPa`

### 表指针映射公式（角度单位为 0.1°）

- 速度：`0..220 km/h  →  0..2450`  即 `angle = 2450/220 * speed`
- 转速：`0..8000 rpm  →  0..2430`  即 `angle = 2430/8000 * rpm`
- 水温：`0..150 °C   →  0..900`   即 `angle = 900/150 * temp`
- 油量：`0..100 %    →  900..1800` 即 `angle = 900 + 900/100 * fuel`

这些映射在 `obj/control.c` 中实现。
所有角度通过统一动画函数缓动至目标值，过渡时间 300ms（ease-in-out）。

### 里程累加

每个渲染周期按速度积分：`Δkm = speed(km/h) * period_ms / 3600000`，累加至 `total_mileage` 与 `trip_mileage` 并取整显示。

## 代码入口与组织

- 主程序：`main.c`
  - 初始化 LVGL/UI
  - 创建时间显示定时器（1s）与数据渲染定时器（100ms）
  - 主循环：`handle_console_input()` + `lv_timer_handler()`
- 控制台解析：`obj/callback.c`
  - 保留简单注释，解析所有上述命令
  - 非数据项（如指示灯）直接操作 UI；数据项仅更新 `g_vehicle_state`
- 数据渲染与联动：`obj/control.c`
  - 全部 UI 联动在此集中处理，确保解耦与可维护性

## 常见问题

- 运行无窗口：请确认使用 SDL2 构建（PC 模式），并安装了 `libsdl2-dev`。
- 字体/图像缺失：请确认 `bin/` 与 `UI/images/`、`UI/fonts/` 资源完整。
- 角度命令无效：表命令现在只做“角度→数据”的反向映射，指针移动由渲染器自动完成。