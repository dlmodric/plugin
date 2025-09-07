# 构建和清理脚本使用说明

本项目提供了两个便捷的脚本来管理项目的构建和清理工作。

## 📁 脚本文件

- **`clean.sh`** - 清理无用文件脚本
- **`build.sh`** - 自动构建脚本

## 🧹 清理脚本 (clean.sh)

### 功能
清理项目中的编译产物、临时文件和缓存文件，保持项目目录整洁。

### 清理内容
- **编译产物**: `*.o`, `*.so`, `*.dylib`, `*.a`, `*.exe`
- **可执行文件**: `plugin_test`, `testB`
- **CMake产物**: `CMakeCache.txt`, `cmake_install.cmake`, `Makefile`, `CMakeFiles/`
- **构建目录**: `build/`, `cmake-build-debug/`, `cmake-build-release/`
- **临时文件**: `*.tmp`, `*.bak`, `*.swp`, `*.swo`, `*~`
- **IDE配置**: `.vscode/`, `.idea/`, `*.user`
- **日志文件**: `*.log`
- **系统文件**: `.DS_Store`

### 使用方法
```bash
./clean.sh
```

### 输出示例
```
🧹 开始清理无用文件...
清理编译产物...
清理CMake产物...
清理构建目录...
清理临时文件...
清理IDE配置文件...
清理日志文件...
清理系统文件...
✅ 清理完成！
📊 清理统计：
   清理前文件数: 89
   清理后文件数: 25
   已清理文件数: 64

📁 剩余主要文件：
./projectA/CMakeLists.txt
./projectA/include/IPlugin.h
./projectA/main.cpp
./projectB/CMakeLists.txt
./projectB/MyPluginA.cpp
./projectB/MyPluginA.h
...
```

## 🔨 构建脚本 (build.sh)

### 功能
自动化构建整个项目，包括动态库和主程序的编译、链接和测试。

### 构建流程
1. **文件检查** - 验证必要的CMakeLists.txt文件存在
2. **构建projectB** - 编译动态库 (`libtestB.dylib`)
3. **构建projectA** - 编译主程序 (`plugin_test`)
4. **复制动态库** - 将动态库复制到主程序目录
5. **运行测试** - 可选择运行测试程序验证功能

### 使用方法
```bash
./build.sh
```

### 交互式运行
脚本会在构建完成后询问是否运行测试：
```
是否运行测试程序? (y/n): 
```

### 自动运行测试
```bash
echo "y" | ./build.sh
```

### 输出示例
```
🔨 开始构建项目...
🎯 插件系统构建脚本
==================================
📋 检查项目文件...
✅ 项目文件检查通过
🔧 构建 projectB (动态库)...
⚙️  配置CMake...
🔨 编译中...
✅ projectB 动态库构建成功
🔧 构建 projectA (主程序)...
⚙️  配置CMake...
🔨 编译中...
✅ projectA 主程序构建成功
📦 复制动态库...
✅ 已复制 libtestB.dylib

🎉 构建完成！
==================================
📁 构建产物位置:
  - projectA/plugin_test (主程序)
  - projectB/libtestB.* (动态库)

🧪 运行测试...
🚀 运行主程序:
=== 动态插件加载测试 ===
✅ 成功加载动态库: libtestB.dylib
✅ 成功创建插件实例
MyPluginA 正在执行...
=== 测试完成 ===
✅ 测试完成！
```

## 🚀 快速开始

### 完整的开发流程
```bash
# 1. 清理项目
./clean.sh

# 2. 构建项目并运行测试
echo "y" | ./build.sh
```

### 仅构建不测试
```bash
echo "n" | ./build.sh
```

### 手动运行程序
```bash
cd projectA
./plugin_test
```

## 📋 构建产物

构建成功后，会生成以下文件：

- **projectA/plugin_test** - 主程序可执行文件
- **projectB/libtestB.dylib** - 插件动态库
- **projectA/libtestB.dylib** - 复制到主程序目录的动态库

## ⚠️ 注意事项

1. **权限设置**: 首次使用前需要给脚本添加执行权限：
   ```bash
   chmod +x clean.sh build.sh
   ```

2. **依赖要求**: 
   - CMake 3.16+
   - C++17 支持的编译器
   - macOS/Linux 系统

3. **错误处理**: 
   - 脚本遇到错误会立即退出
   - 详细的错误信息会显示在终端

4. **平台兼容**: 
   - macOS: 生成 `.dylib` 动态库
   - Linux: 生成 `.so` 动态库

## 🔧 自定义配置

如需修改构建配置，可以编辑相应的 `CMakeLists.txt` 文件：
- **projectA/CMakeLists.txt** - 主程序配置
- **projectB/CMakeLists.txt** - 动态库配置