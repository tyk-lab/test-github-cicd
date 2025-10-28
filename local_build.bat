@echo off
REM 本地构建脚本 (Windows)
REM 用于在推送到GitHub之前测试项目是否能正常构建

echo === 开始本地构建 ===

REM 创建构建目录
if not exist build mkdir build
cd build

REM 配置CMake
echo ⚙️ 配置CMake...
cmake ..

REM 编译
echo 🔨 编译项目...
cmake --build . --config Release

REM 运行测试
echo 🧪 运行测试...
ctest -C Release --output-on-failure

REM 运行主程序
echo 🚀 运行主程序...
Release\calculator_app.exe

echo.
echo === 构建完成 ===

cd ..
pause
