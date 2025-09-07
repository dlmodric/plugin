# CMake链接动态库方案

## 概述

本文档说明如何将项目从使用 `dlopen` 动态加载库的方式改造为使用 CMake 直接链接动态库的方式。

## 两种方案对比

### 原方案（dlopen方式）
- **优点**：运行时动态加载，灵活性高，可以根据需要加载不同的插件
- **缺点**：需要手动管理库的加载和卸载，错误处理复杂，符号查找需要字符串匹配

### 新方案（CMake链接方式）
- **优点**：编译时确定依赖，自动处理库加载，代码简洁，类型安全
- **缺点**：灵活性较低，所有依赖在编译时确定

## 改造步骤

### 1. 修改 projectA/CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(PluginDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器和链接器标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

# 添加子目录，构建插件库
add_subdirectory(../projectB projectB_build)

# 构建主程序
add_executable(plugin_test main.cpp)
target_include_directories(plugin_test PRIVATE include)

# 直接链接插件动态库，而不是使用dlopen
target_link_libraries(plugin_test PRIVATE testB c++ c++abi)

# 设置运行时库路径（可选，用于找到动态库）
set_target_properties(plugin_test PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
)
```

### 2. 修改 main.cpp

移除 dlopen 相关代码：
- 移除 `#include <dlfcn.h>`
- 移除 `dlopen`, `dlsym`, `dlclose` 调用
- 直接声明和调用外部函数

```cpp
#include <iostream>
#include <memory>
#include "include/IPlugin.h"
#include "include/class_factory.h"

// 声明外部函数，这个函数在动态库中定义
extern "C" ClassFactory* getClassFactory();

int main()
{
    std::cout << "=== 动态插件加载测试（CMake链接方案） ===" << std::endl;
    
    // 直接调用链接的动态库函数，无需dlopen
    ClassFactory* factory = getClassFactory();
    if (!factory) {
        std::cerr << "❌ 获取ClassFactory实例失败" << std::endl;
        return 1;
    }
    
    std::cout << "✅ 成功获取ClassFactory实例（通过CMake链接）" << std::endl;
    
    // ... 其余代码保持不变
}
```

### 3. 优化 projectB/CMakeLists.txt

确保符号正确导出：

```cmake
cmake_minimum_required(VERSION 3.16)
project(testB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件路径
include_directories(../projectA/include)

# 构建插件动态库
add_library(testB SHARED MyPluginA.cpp MyPluginA.h MyPluginB.cpp MyPluginB.h)

# 设置输出名称
set_target_properties(testB PROPERTIES 
    OUTPUT_NAME "testB"
    # 确保符号可见性
    CXX_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN OFF
)
```

## 构建和运行

使用新的构建脚本：

```bash
./build_linked.sh
```

## 关键差异

### 依赖管理
- **dlopen方式**：运行时手动加载库文件
- **CMake链接方式**：编译时自动处理依赖关系

### 符号访问
- **dlopen方式**：通过 `dlsym` 查找符号，需要字符串匹配
- **CMake链接方式**：直接声明外部函数，编译器处理符号解析

### 错误处理
- **dlopen方式**：需要检查 `dlopen`, `dlsym` 返回值和 `dlerror()`
- **CMake链接方式**：链接时错误由编译器/链接器处理

### 库生命周期
- **dlopen方式**：手动调用 `dlclose` 卸载库
- **CMake链接方式**：程序结束时自动卸载

## 适用场景

### 使用 CMake 链接方式的场景：
- 插件数量固定，编译时已知
- 需要更好的类型安全和编译时检查
- 希望简化代码复杂度
- 性能要求较高（避免运行时符号查找）

### 继续使用 dlopen 方式的场景：
- 需要运行时动态发现和加载插件
- 插件可能在程序运行后才可用
- 需要支持插件的热插拔
- 插件数量不确定或很多

## 注意事项

1. **符号可见性**：确保动态库中的符号正确导出
2. **依赖顺序**：CMake 会自动处理依赖顺序
3. **运行时路径**：可能需要设置 `RPATH` 或 `LD_LIBRARY_PATH`
4. **平台差异**：不同平台的动态库扩展名不同（.so, .dylib, .dll）

## 总结

CMake 链接方式提供了更简洁、更安全的动态库使用方法，适合大多数固定插件架构的应用场景。如果您的应用不需要运行时动态发现插件，推荐使用这种方式。