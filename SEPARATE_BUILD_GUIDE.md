# 分离构建方案说明

## 🎯 方案概述

本方案实现了项目A和项目B的完全分离构建，项目A通过链接预构建的动态库来使用项目B的功能，而不是使用 `add_subdirectory`。

## 📁 项目结构

```
plugin/
├── projectA/                 # 主程序项目
│   ├── CMakeLists.txt        # 不包含add_subdirectory
│   ├── main.cpp              # 直接调用getClassFactory()
│   └── include/
│       └── class_factory.h
├── projectB/                 # 插件库项目
│   ├── CMakeLists.txt        # 构建动态库
│   ├── MyPluginA.cpp/h       # 插件实现
│   └── MyPluginB.cpp/h       # 插件实现
└── build_separate.sh         # 分离构建脚本
```

## 🔧 关键技术点

### 1. projectA/CMakeLists.txt
- **移除了** `add_subdirectory(../projectB projectB_build)`
- **使用** `find_library()` 查找预构建的动态库
- **设置** `BUILD_RPATH` 确保运行时能找到动态库

```cmake
# 查找预构建的动态库
find_library(TESTB_LIBRARY 
    NAMES testB libtestB
    PATHS ../projectB/build
    NO_DEFAULT_PATH
)

# 链接预构建的动态库
target_link_libraries(plugin_test PRIVATE ${TESTB_LIBRARY} c++ c++abi)
```

### 2. 构建流程
1. **第一步**：独立构建 projectB 动态库
2. **第二步**：构建 projectA 主程序，链接步骤1的动态库
3. **第三步**：运行测试

## 🚀 使用方法

### 方法1：使用构建脚本（推荐）
```bash
./build_separate.sh
```

### 方法2：手动构建
```bash
# 1. 构建动态库
cd projectB
mkdir -p build && cd build
cmake .. && make

# 2. 构建主程序
cd ../../projectA  
mkdir -p build && cd build
cmake .. && make

# 3. 运行
./plugin_test
```

## ✅ 验证结果

```
=== 动态插件加载测试（CMake链接方案） ===
✅ 成功获取ClassFactory实例（通过CMake链接）
📋 已注册的类数量: 2
   - MyPluginA
   - MyPluginB
✅ 找到已注册的插件: MyPluginA
✅ 成功创建插件实例
MyPluginA 正在执行...
✅ 找到已注册的插件: MyPluginB
✅ 成功创建插件实例
MyPluginB 正在执行...这是第二个插件!
=== 测试完成 ===
```

## 🎯 方案优势

1. **完全分离**：项目A和项目B可以独立开发和构建
2. **符合约束**：项目A不使用 `add_subdirectory`
3. **动态链接**：使用标准的动态库链接方式
4. **类型安全**：编译时检查，避免dlopen的运行时错误
5. **依赖管理**：CMake自动处理库依赖关系

## 🔍 技术细节

- **库查找**：使用 `find_library()` 在指定路径查找动态库
- **运行时路径**：设置 `BUILD_RPATH` 确保程序能找到动态库
- **符号导出**：在 MyPluginB.cpp 中使用 `EXPORT_CLASS_FACTORY()` 宏
- **错误处理**：构建时检查库是否存在，提供清晰的错误信息

## 📋 注意事项

1. 必须先构建 projectB，再构建 projectA
2. 动态库路径在 CMakeLists.txt 中硬编码为 `../projectB/build`
3. 如果修改了 projectB，需要重新构建两个项目
4. 运行时需要确保动态库在正确的路径下