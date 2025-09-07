# 从动态链接库中获取静态类的方法

本文档介绍了如何从动态链接库中获取和使用静态类（如ClassFactory）的几种方法。

## 问题背景

你有一个`ClassFactory`静态单例类，希望从动态链接库中获取并使用它。目前项目中有两套方案：
1. 直接通过C风格导出函数获取插件实例
2. 通过ClassFactory静态类管理插件注册和创建

## 解决方案

### 方案1：导出ClassFactory实例（推荐）

**实现步骤：**

1. **在class_factory.h中添加导出宏：**
```cpp
#define EXPORT_CLASS_FACTORY() \
    extern "C" { \
        ClassFactory* getClassFactory() { \
            return &ClassFactory::getInstance(); \
        } \
    }
```

2. **在插件头文件中使用宏：**
```cpp
// MyPluginA.h
#include "../projectA/include/class_factory.h"

class MyPluginA : public IPlugin {
    // ... 类定义
};

// 注册到ClassFactory
REGISTER_CLASS(MyPluginA)

// 导出ClassFactory实例
EXPORT_CLASS_FACTORY()
```

3. **在主程序中获取ClassFactory：**
```cpp
// 加载动态库
void* handle = dlopen("libtestB.dylib", RTLD_LAZY);

// 获取ClassFactory函数
typedef ClassFactory* (*GetClassFactoryFunc)();
GetClassFactoryFunc getClassFactory = (GetClassFactoryFunc) dlsym(handle, "getClassFactory");

// 使用ClassFactory
if (getClassFactory) {
    ClassFactory* factory = getClassFactory();
    auto plugin = factory->createObject("MyPluginA");
    if (plugin) {
        plugin->execute();
    }
}
```

### 方案2：直接C风格导出（当前使用）

**实现步骤：**

1. **使用EXPORT_PLUGIN宏：**
```cpp
// MyPluginA.h
EXPORT_PLUGIN(MyPluginA)  // 生成 createMyPluginA() 函数
```

2. **在主程序中直接调用：**
```cpp
typedef IPlugin* (*CreatePluginFunc)();
CreatePluginFunc createPlugin = (CreatePluginFunc) dlsym(handle, "createMyPluginA");
IPlugin* plugin = createPlugin();
```

### 方案3：混合使用（最灵活）

同时支持两种方式，在插件头文件中：
```cpp
// 方案1：直接导出
EXPORT_PLUGIN(MyPluginA)

// 方案2：注册到ClassFactory
REGISTER_CLASS(MyPluginA)

// 方案3：导出ClassFactory
EXPORT_CLASS_FACTORY()
```

## 当前项目状态

### 已实现功能：
- ✅ ClassFactory单例类设计
- ✅ 自动注册宏REGISTER_CLASS
- ✅ C风格导出宏EXPORT_PLUGIN
- ✅ ClassFactory导出宏EXPORT_CLASS_FACTORY
- ✅ 基本的动态库加载测试

### 测试程序：
1. **plugin_test** - 基本的C风格导出测试（✅ 工作正常）
2. **factory_test** - 简化的ClassFactory测试（✅ 工作正常）
3. **complete_factory_test** - 完整ClassFactory测试（❌ 链接问题）

### 链接问题解决：

complete_factory_test出现std::function链接错误，这是因为ClassFactory使用了std::function。解决方案：

1. **简化ClassFactory设计**（推荐）：
   - 使用函数指针替代std::function
   - 避免复杂的C++特性

2. **修改链接选项**：
   - 添加更多的C++标准库链接选项
   - 使用静态链接

## 使用建议

1. **对于简单插件系统**：使用方案2（直接C风格导出）
2. **对于复杂插件管理**：使用方案1（ClassFactory）
3. **对于最大兼容性**：使用方案3（混合方式）

## 测试命令

```bash
# 编译动态库
cd projectB && make

# 编译主程序
cd projectA && cmake . && make

# 复制动态库
cp projectB/libtestB.dylib projectA/

# 测试基本功能
cd projectA && ./plugin_test

# 测试ClassFactory
cd projectA && ./factory_test
```

## 总结

从动态链接库中获取静态类的关键是：
1. 通过extern "C"导出获取静态类实例的函数
2. 在主程序中使用dlsym获取该函数
3. 调用函数获取静态类实例
4. 通过实例调用静态类的方法

这种方式可以让你在不同的动态库之间共享静态类实例，实现插件的统一管理。