# 设置目标系统名称
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 指定交叉编译工具链的路径
set(TOOLCHAIN_DIR "/usr/local/arm/5.4.0/usr/")

# 指定编译器
set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/arm-linux-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/arm-linux-g++")
set(CMAKE_C_FLAGS"-Wl -rpath=.")

# 指定 find_library, find_path 等命令的搜索路径模式
# 从不搜索宿主系统路径，只在工具链路径中找程序
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# 只在工具链路径中找库
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 只在工具链路径中找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# 只在工具链路径中找 CMake 包配置文件
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)