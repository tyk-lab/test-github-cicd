cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(CalculatorProject VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 源文件
set(CALCULATOR_SOURCES
    src/calculator.cpp
)

# 创建计算器库
add_library(calculator_lib ${CALCULATOR_SOURCES})
target_include_directories(calculator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 主程序可执行文件
add_executable(calculator_app src/main.cpp)
target_link_libraries(calculator_app calculator_lib)

# 测试可执行文件
add_executable(calculator_tests tests/test_calculator.cpp)
target_link_libraries(calculator_tests calculator_lib)

# 启用测试
enable_testing()
add_test(NAME CalculatorTests COMMAND calculator_tests)

# 打印构建信息
message(STATUS "构建类型: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++标准: ${CMAKE_CXX_STANDARD}")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
