cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(Calculator)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O3 -Wall")

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src)

# 添加库文件路径
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 添加可执行文件
add_executable(calculator
        src/main.cpp
        src/calculator.cpp
        src/fraction.cpp
)

# 链接 GMP 库
target_link_libraries(calculator gmp gmpxx)
