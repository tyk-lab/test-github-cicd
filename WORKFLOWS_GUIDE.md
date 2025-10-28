# 📋 GitHub Actions 工作流说明文档

> 本项目的 CI/CD 自动化流程完全指南

---

## 🎯 什么是工作流（Workflow）？

**工作流**是 GitHub Actions 的核心概念，是一个自动化流程的定义文件。

### 📁 工作流文件位置

```
.github/workflows/         # 固定目录名，GitHub会自动识别
├── ci.yml                # 主CI/CD工作流
└── publish-report.yml    # 测试报告发布工作流
```

**重要规则：**
- ✅ 所有放在 `.github/workflows/` 目录下的 `.yml` 或 `.yaml` 文件都会被GitHub识别为工作流
- ✅ 每个文件定义一个独立的工作流
- ✅ 工作流之间可以相互触发和依赖
- ✅ 文件名可以任意取，GitHub根据文件内容识别

---

## 📊 本项目的工作流架构

```
触发事件 (push/PR/手动)
         ↓
┌────────────────────────────────────────┐
│  工作流1: C++ CI/CD Pipeline           │
│  文件: ci.yml                          │
│                                        │
│  ┌──────────────────────────────────┐ │
│  │ Job 1: build-and-test            │ │
│  │  ├─ Ubuntu 构建和测试            │ │
│  │  ├─ macOS 构建和测试             │ │
│  │  └─ Windows 构建和测试           │ │
│  └──────────────────────────────────┘ │
│                                        │
│  ┌──────────────────────────────────┐ │
│  │ Job 2: code-quality              │ │
│  │  └─ 代码格式检查                 │ │
│  └──────────────────────────────────┘ │
│                                        │
│  ┌──────────────────────────────────┐ │
│  │ Job 3: summary                   │ │
│  │  └─ 生成执行摘要                 │ │
│  └──────────────────────────────────┘ │
│                                        │
│  ┌──────────────────────────────────┐ │
│  │ Job 4: release                   │ │
│  │  └─ 创建GitHub Release          │ │
│  └──────────────────────────────────┘ │
└────────────────────────────────────────┘
         ↓ (完成后自动触发)
┌────────────────────────────────────────┐
│  工作流2: Publish Test Report          │
│  文件: publish-report.yml              │
│                                        │
│  ┌──────────────────────────────────┐ │
│  │ Job: publish-report              │ │
│  │  ├─ 下载构建产物                 │ │
│  │  ├─ 生成HTML报告                 │ │
│  │  └─ 发布到GitHub Pages          │ │
│  └──────────────────────────────────┘ │
└────────────────────────────────────────┘
         ↓
    用户可访问的测试报告网页
```

---

## 📝 工作流详解

### 1️⃣ **C++ CI/CD Pipeline** (`ci.yml`)

这是主要的CI/CD工作流，负责构建、测试和发布。

#### 📌 触发条件

```yaml
on:
  push:
    branches: [ main, master ]      # 推送到main/master分支
  pull_request:
    branches: [ main, master ]      # 创建PR到main/master
  workflow_dispatch:                # 手动触发
```

**触发方式：**
1. **自动触发** - 推送代码到main分支
2. **自动触发** - 创建Pull Request
3. **手动触发** - 在GitHub Actions页面点击 "Run workflow"

#### 🎯 包含的任务（Jobs）

##### **Job 1: build-and-test**

并行在3个平台上构建和测试：

```yaml
strategy:
  matrix:
    os: [ubuntu-latest, macos-latest, windows-latest]
```

**关键步骤：**
1. 📥 检出代码
2. 🔧 安装CMake
3. 🛠️ 安装平台依赖
4. ⚙️ 配置CMake
5. 🔨 编译项目
6. 🧪 运行测试
7. 🚀 运行主程序
8. 📦 上传构建产物（Artifacts）

**矩阵策略的优势：**
- ✅ 同时在3个平台上测试，节省时间
- ✅ 确保跨平台兼容性
- ✅ 失败隔离 (`fail-fast: false`)

##### **Job 2: code-quality**

代码质量检查：

- 使用 `clang-format` 检查代码格式
- 仅在 Ubuntu 上运行（节省资源）
- 可扩展为更多质量检查（静态分析、Lint等）

##### **Job 3: summary**

生成执行摘要：

```yaml
needs: [build-and-test, code-quality]  # 依赖前两个任务
if: always()                            # 即使失败也运行
```

- 汇总所有任务的执行结果
- 生成可读性强的报告
- 显示在GitHub Actions的Summary页面

##### **Job 4: release**

自动创建Release：

```yaml
if: startsWith(github.ref, 'refs/tags/v') || 
    (github.event_name == 'push' && github.ref == 'refs/heads/main')
```

**触发条件：**
- 推送 `v` 开头的tag（如 `v1.0.0`）
- 或推送到main分支（自动版本号）

**功能：**
1. 下载所有平台的构建产物
2. 打包成分发格式（`.tar.gz` / `.zip`）
3. 生成版本号和发布说明
4. 创建GitHub Release
5. 上传所有平台的二进制文件

---

### 2️⃣ **Publish Test Report** (`publish-report.yml`)

生成和发布精美的HTML测试报告。

#### 📌 触发条件

```yaml
on:
  workflow_run:
    workflows: ["C++ CI/CD Pipeline"]  # 监听CI/CD工作流
    types:
      - completed                      # 完成时触发
```

**说明：**
- 自动触发，无需手动操作
- 监听 "C++ CI/CD Pipeline" 的完成事件
- 无论成功或失败都会触发

#### 🎯 主要功能

1. **下载构建产物**
   ```yaml
   uses: actions/download-artifact@v4
   with:
     run-id: ${{ github.event.workflow_run.id }}
   ```

2. **生成HTML报告**
   - 提取测试结果
   - 生成精美的网页
   - 包含状态、时间、平台信息等

3. **发布到GitHub Pages**
   ```yaml
   uses: peaceiris/actions-gh-pages@v3
   with:
     publish_dir: ./public
   ```

**输出：**
- 📊 在线访问：`https://tyk-lab.github.io/test-github-cicd/`
- 🎨 精美的可视化界面
- 📈 详细的测试结果展示

---

## 🔧 工作流文件结构

每个工作流文件都遵循相同的结构：

```yaml
# 1. 工作流名称
name: 工作流名称

# 2. 触发条件
on:
  push:
    branches: [ main ]
  workflow_dispatch:

# 3. 权限配置（可选）
permissions:
  contents: write

# 4. 任务定义
jobs:
  # 任务1
  job-name-1:
    runs-on: ubuntu-latest
    steps:
      - name: 步骤1
        run: echo "Hello"
      - name: 步骤2
        uses: actions/checkout@v4
  
  # 任务2（依赖任务1）
  job-name-2:
    needs: [job-name-1]
    runs-on: ubuntu-latest
    steps:
      - name: 步骤1
        run: echo "World"
```

---

## 📚 核心概念解释

### 🔹 Workflow（工作流）

完整的自动化流程，定义在 `.yml` 文件中。

### 🔹 Job（任务）

工作流中的一个执行单元，可以包含多个步骤。

**特点：**
- 默认并行执行
- 可以设置依赖关系（`needs`）
- 可以在不同的虚拟机上运行

### 🔹 Step（步骤）

任务中的具体操作。

**两种类型：**
1. **运行命令** (`run`)
   ```yaml
   - name: 编译代码
     run: make build
   ```

2. **使用Action** (`uses`)
   ```yaml
   - name: 检出代码
     uses: actions/checkout@v4
   ```

### 🔹 Matrix（矩阵策略）

用同一套步骤在多个环境下运行。

```yaml
strategy:
  matrix:
    os: [ubuntu-latest, macos-latest, windows-latest]
    node: [14, 16, 18]
# 这将创建 3 × 3 = 9 个并行任务
```

### 🔹 Artifacts（构建产物）

任务之间共享的文件。

```yaml
# 上传
- uses: actions/upload-artifact@v4
  with:
    name: my-artifact
    path: build/

# 下载
- uses: actions/download-artifact@v4
  with:
    name: my-artifact
```

---

## 🚀 如何添加新的工作流

### 步骤1: 创建文件

在 `.github/workflows/` 目录下创建新的 `.yml` 文件：

```bash
touch .github/workflows/my-workflow.yml
```

### 步骤2: 编写工作流

```yaml
name: My Custom Workflow

on:
  push:
    branches: [ main ]

jobs:
  my-job:
    runs-on: ubuntu-latest
    steps:
      - name: Hello World
        run: echo "Hello from my workflow!"
```

### 步骤3: 提交并推送

```bash
git add .github/workflows/my-workflow.yml
git commit -m "feat: 添加自定义工作流"
git push
```

### 步骤4: 查看运行

访问：`https://github.com/你的用户名/仓库名/actions`

---

## 🎓 常用工作流示例

### 示例1: 定时任务

```yaml
name: Daily Report

on:
  schedule:
    - cron: '0 9 * * *'  # 每天UTC 9:00运行

jobs:
  report:
    runs-on: ubuntu-latest
    steps:
      - run: echo "生成每日报告"
```

### 示例2: 多工作流协作

```yaml
# workflow-a.yml
name: Workflow A
on: push
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - run: echo "Building..."

---

# workflow-b.yml
name: Workflow B
on:
  workflow_run:
    workflows: ["Workflow A"]  # 监听Workflow A
    types: [completed]
jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - run: echo "Deploying..."
```

### 示例3: 条件执行

```yaml
jobs:
  deploy:
    runs-on: ubuntu-latest
    # 只在main分支且推送事件时运行
    if: github.ref == 'refs/heads/main' && github.event_name == 'push'
    steps:
      - run: echo "Deploying to production"
```

---

## 🛠️ 调试技巧

### 1. 查看日志

- 进入Actions页面
- 点击工作流运行记录
- 展开每个步骤查看详细日志

### 2. 本地测试

使用 [act](https://github.com/nektos/act) 在本地运行工作流：

```bash
# 安装act
brew install act  # macOS
choco install act  # Windows

# 运行工作流
act push
```

### 3. 调试输出

```yaml
- name: 调试信息
  run: |
    echo "当前分支: ${{ github.ref }}"
    echo "事件类型: ${{ github.event_name }}"
    echo "运行ID: ${{ github.run_id }}"
    ls -la
    env | sort
```

### 4. 使用tmate调试

```yaml
- name: 进入SSH调试模式
  uses: mxschmitt/action-tmate@v3
  if: failure()  # 失败时才进入
```

---

## 📖 进阶主题

### 🔹 Secret管理

存储敏感信息（API密钥、密码等）：

```yaml
steps:
  - name: 使用Secret
    run: echo "API Key: ${{ secrets.API_KEY }}"
    env:
      API_KEY: ${{ secrets.API_KEY }}
```

**设置Secret：**
`Settings → Secrets and variables → Actions → New repository secret`

### 🔹 环境变量

```yaml
env:
  GLOBAL_VAR: "全局变量"

jobs:
  my-job:
    env:
      JOB_VAR: "任务变量"
    steps:
      - name: 使用变量
        env:
          STEP_VAR: "步骤变量"
        run: |
          echo $GLOBAL_VAR
          echo $JOB_VAR
          echo $STEP_VAR
```

### 🔹 缓存依赖

加速构建：

```yaml
- name: 缓存依赖
  uses: actions/cache@v3
  with:
    path: ~/.cache
    key: ${{ runner.os }}-build-${{ hashFiles('**/package-lock.json') }}
```

---

## 🔍 常见问题

### Q1: 为什么我的工作流没有运行？

**检查清单：**
- ✅ 文件在 `.github/workflows/` 目录下
- ✅ 文件扩展名是 `.yml` 或 `.yaml`
- ✅ YAML语法正确（使用在线验证器检查）
- ✅ 触发条件满足

### Q2: 如何让工作流只在特定文件改变时运行？

```yaml
on:
  push:
    paths:
      - 'src/**'        # 只有src目录改变时触发
      - 'tests/**'
```

### Q3: 工作流运行时间过长怎么办？

**优化建议：**
1. 使用缓存 (`actions/cache`)
2. 并行执行任务
3. 只在必要时运行（`if` 条件）
4. 使用自托管Runner（self-hosted）

### Q4: 如何在Pull Request中运行工作流？

```yaml
on:
  pull_request:
    types: [opened, synchronize, reopened]
```

---

## 📊 监控和通知

### Slack通知

```yaml
- name: 发送Slack通知
  uses: 8398a7/action-slack@v3
  with:
    status: ${{ job.status }}
    webhook_url: ${{ secrets.SLACK_WEBHOOK }}
  if: always()
```

### 邮件通知

GitHub默认会发送失败通知邮件到你的邮箱。

可以在个人设置中配置：
`Settings → Notifications → GitHub Actions`

---

## 🎯 最佳实践

1. ✅ **命名清晰** - 使用描述性的工作流、任务和步骤名称
2. ✅ **添加注释** - 解释复杂的逻辑
3. ✅ **使用矩阵** - 减少重复代码
4. ✅ **设置超时** - 防止任务无限运行
   ```yaml
   jobs:
     my-job:
       timeout-minutes: 30
   ```
5. ✅ **失败处理** - 使用 `continue-on-error` 和 `if: always()`
6. ✅ **安全第一** - 敏感信息使用Secrets，不要硬编码
7. ✅ **版本固定** - Actions使用特定版本（如 `@v4`）
8. ✅ **文档化** - 在README中说明工作流的作用

---

## 📚 参考资源

- [GitHub Actions官方文档](https://docs.github.com/en/actions)
- [工作流语法参考](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)
- [Actions市场](https://github.com/marketplace?type=actions)
- [Awesome Actions](https://github.com/sdras/awesome-actions)

---

## 🎉 总结

本项目的工作流系统展示了：

1. ✅ **多平台CI/CD** - 同时在3个操作系统上构建测试
2. ✅ **自动化发布** - 自动创建Release并上传二进制文件
3. ✅ **可视化报告** - 生成精美的HTML测试报告
4. ✅ **工作流协作** - 多个工作流相互触发和协作
5. ✅ **完整文档** - 详细的注释和说明

通过学习这些工作流，你可以：
- 🎓 理解GitHub Actions的核心概念
- 🛠️ 创建自己的自动化流程
- 🚀 提高开发效率和代码质量
- 📊 实现CI/CD最佳实践

**开始你的自动化之旅吧！** 🚀
