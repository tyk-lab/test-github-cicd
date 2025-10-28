#!/bin/bash

# 本地构建脚本
# 用于在推送到GitHub之前测试项目是否能正常构建

echo "=== 开始本地构建 ==="

# 创建构建目录
mkdir -p build
cd build

# 配置CMake
echo "⚙️ 配置CMake..."
cmake ..

# 编译
echo "🔨 编译项目..."
cmake --build .

# 运行测试
echo "🧪 运行测试..."
ctest --output-on-failure

# 运行主程序
echo "🚀 运行主程序..."
./calculator_app

echo ""
echo "=== 构建完成 ==="
