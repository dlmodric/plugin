# 插件系统演示项目

一个基于 C++ 的动态插件加载系统，演示如何使用工厂模式和动态库实现插件架构。

## 项目结构

```
plugin/
├── projectA/                 # 主程序
│   ├── include/             # 头文件
│   │   ├── IPlugin.h       # 插件接口
│   │   ├── class_factory.h # 类工厂
│   │   └── plugin_manager.h # 插件管理器
│   ├── dlopen_test.cpp     # 主测试程序
│   └── CMakeLists.txt      # 构建配置
├── projectB/                # 插件实现
│   ├── MyPluginA.h         # 插件头文件
│   ├── MyPluginA.cpp       # 插件实现
│   └── CMakeLists.txt      # 构建配置
└── clean.sh                # 清理脚本
```

## 核心特性

- **工厂模式**: 统一的插件创建接口
- **自动注册**: 静态对象自动注册插件类
- **动态加载**: 运行时加载插件动态库
- **类型安全**: 基于智能指针的内存管理

## 构建和运行

1. 构建插件库：
```bash
cd projectB
mkdir build && cd build
cmake ..
make
```

2. 构建主程序：
```bash
cd projectA
mkdir build && cd build
cmake ..
make
```

3. 运行测试：
```bash
./plugin_test
```

## 清理项目

```bash
./clean.sh
```