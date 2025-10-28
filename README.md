# C++ CI/CD 示例项目 🚀

[![CI/CD Pipeline](https://github.com/tyk-lab/test-github-cicd/actions/workflows/ci.yml/badge.svg)](https://github.com/tyk-lab/test-github-cicd/actions/workflows/ci.yml)
[![GitHub release](https://img.shields.io/github/v/release/tyk-lab/test-github-cicd)](https://github.com/tyk-lab/test-github-cicd/releases)
[![GitHub last commit](https://img.shields.io/github/last-commit/tyk-lab/test-github-cicd)](https://github.com/tyk-lab/test-github-cicd/commits/main)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

这是一个简单的C++项目，用于演示GitHub CI/CD工作流程。

## 📥 快速下载

从 [Releases](https://github.com/tyk-lab/test-github-cicd/releases/latest) 页面下载适合你操作系统的预编译版本：
- 🐧 Linux (Ubuntu)
- 🍎 macOS
- 🪟 Windows

## 项目结构

```text
.
├── src/                       # 源代码目录
│   ├── main.cpp              # 主程序
│   ├── calculator.h          # 计算器头文件
│   └── calculator.cpp        # 计算器实现
├── tests/                    # 测试代码目录
│   └── test_calculator.cpp  # 单元测试
├── .github/                  # GitHub配置
│   └── workflows/
│       └── ci.yml           # CI/CD工作流配置
├── CMakeLists.txt           # CMake构建配置
├── LICENSE                  # MIT许可证
├── README.md               # 本文件
├── CICD_GUIDE.md          # CI/CD详细教程
└── RELEASE_GUIDE.md       # Release发布指南
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

本项目使用GitHub Actions实现完整的CI/CD流程，配置文件在 `.github/workflows/ci.yml`。

### 工作流触发条件

- 推送到 `main` 或 `master` 分支时
- 创建Pull Request到 `main` 或 `master` 分支时
- 手动触发（workflow_dispatch）
- 推送版本tag时（如 `v1.0.0`）

### CI/CD 流程步骤

1. **代码检出**: 从仓库拉取最新代码
2. **环境设置**: 安装必要的编译工具和依赖
3. **构建**: 使用CMake在多个平台上编译项目
4. **测试**: 运行单元测试确保代码质量
5. **质量检查**: 代码格式和静态分析
6. **打包**: 将编译产物打包成分发格式
7. **发布**: 自动创建GitHub Release并上传文件

### 多平台支持

CI配置支持在以下平台上构建和测试：

- 🐧 Ubuntu (Linux) - gcc编译器
- 🍎 macOS - clang编译器
- 🪟 Windows - MSVC编译器

每次运行都会在这3个平台上并行执行，确保跨平台兼容性。

## 学习要点

通过这个项目，你可以学习到：

1. **自动化构建**: 每次代码提交都会自动触发构建
2. **自动化测试**: 确保代码质量，防止引入bug
3. **多平台测试**: 确保代码在不同操作系统上都能正常工作
4. **持续集成**: 频繁地将代码集成到主分支
5. **工作流配置**: 如何编写GitHub Actions的YAML配置文件
6. **自动发布**: 如何自动创建Release并分发二进制文件
7. **徽章使用**: 在README中展示项目状态

## 🎓 学习资源

- **CI/CD概念**: 阅读 [CICD_GUIDE.md](CICD_GUIDE.md) 了解持续集成和持续部署的原理
- **Release流程**: 阅读 [RELEASE_GUIDE.md](RELEASE_GUIDE.md) 了解自动发布机制
- **GitHub Actions**: [官方文档](https://docs.github.com/en/actions)
- **CMake教程**: [CMake官方文档](https://cmake.org/documentation/)

## 📥 下载和使用

### 下载预编译版本

从 [Releases页面](https://github.com/tyk-lab/test-github-cicd/releases/latest) 下载适合你系统的版本：

**Linux/macOS:**
```bash
# 解压
tar -xzf calculator-*-x64.tar.gz

# 运行程序
./calculator_app

# 运行测试
./calculator_tests
```

**Windows:**
1. 下载 `calculator-windows-x64.zip`
2. 解压文件
3. 双击 `calculator_app.exe` 运行

### 从源码编译

```bash
# 克隆仓库
git clone https://github.com/tyk-lab/test-github-cicd.git
cd test-github-cicd

# 创建构建目录
mkdir build && cd build

# 配置和编译
cmake ..
cmake --build .

# 运行
./calculator_app
```

## 🔄 CI/CD工作流

### 自动化流程

每次推送代码到 `main` 分支时：
1. ✅ 自动在3个平台（Ubuntu、macOS、Windows）上构建
2. ✅ 运行所有单元测试
3. ✅ 进行代码质量检查
4. ✅ 自动创建GitHub Release
5. ✅ 上传各平台的编译产物

### 手动触发

1. 访问仓库的 [Actions](https://github.com/tyk-lab/test-github-cicd/actions) 页面
2. 选择 "C++ CI/CD Pipeline"
3. 点击 "Run workflow" 按钮
4. 选择分支并运行

### 创建版本发布

```bash
# 创建带版本号的tag
git tag v1.0.0

# 推送tag到远程
git push origin v1.0.0
```

这将触发CI/CD并创建一个正式版本的Release。

## 📊 项目状态

- **构建状态**: 查看顶部的徽章
- **最新版本**: [Releases](https://github.com/tyk-lab/test-github-cicd/releases)
- **CI/CD历史**: [Actions](https://github.com/tyk-lab/test-github-cicd/actions)

## 📚 更多文档

- [CI/CD详细教程](CICD_GUIDE.md) - 深入了解GitHub Actions的工作原理
- [Release发布指南](RELEASE_GUIDE.md) - 了解自动发布流程

## 🤝 贡献

欢迎提交Issue和Pull Request！

## 📄 许可证

本项目采用 [MIT License](LICENSE) 开源许可证。
