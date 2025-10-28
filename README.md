# C++ CI/CD 示例项目

这是一个简单的C++项目，用于演示GitHub CI/CD工作流程。

## 项目结构

```
.
├── src/                # 源代码目录
│   ├── main.cpp       # 主程序
│   ├── calculator.h   # 计算器头文件
│   └── calculator.cpp # 计算器实现
├── tests/             # 测试代码目录
│   └── test_calculator.cpp
├── .github/           # GitHub Actions配置
│   └── workflows/
│       └── ci.yml     # CI/CD工作流配置
├── CMakeLists.txt     # CMake构建配置
└── README.md          # 项目说明
```

## 构建项目

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 运行程序

```bash
./build/calculator_app
```

## 运行测试

```bash
./build/calculator_tests
```

## CI/CD 工作流说明

本项目使用GitHub Actions实现CI/CD，配置文件在`.github/workflows/ci.yml`。

### 工作流触发条件
- 推送到`main`分支时
- 创建Pull Request到`main`分支时
- 手动触发

### CI/CD 流程步骤

1. **代码检出**: 从仓库拉取最新代码
2. **环境设置**: 安装必要的编译工具和依赖
3. **构建**: 使用CMake编译项目
4. **测试**: 运行单元测试
5. **报告**: 生成测试报告和构建产物

### 多平台支持

CI配置支持在以下平台上构建和测试：
- Ubuntu (Linux)
- macOS
- Windows

## 学习要点

通过这个项目，你可以学习到：

1. **自动化���建**: 每次代码提交都会自动触发构建
2. **自动化测试**: 确保代码质量，防止引入bug
3. **多平台测试**: 确保代码在不同操作系统上都能正常工作
4. **持续集成**: 频繁地将代码集成到主分支
5. **工作流配置**: 如何编写GitHub Actions的YAML配置文件

## 如何使用

1. 将此项目推送到GitHub仓库
2. GitHub会自动检测`.github/workflows/ci.yml`文件
3. 在仓库的"Actions"标签页可以看到CI/CD运行情况
4. 每次推送代码或创建PR时，都会自动运行工作流

## 扩展建议

- 添加代码覆盖率检查
- 集成代码静态分析工具
- 添加自动部署步骤
- 配置构建产物上传
