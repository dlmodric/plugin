# 插件导出宏使用说明

## EXPORT_PLUGIN 宏

`EXPORT_PLUGIN` 宏定义在 `IPlugin.h` 中，用于自动生成C风格的导出函数，避免C++名称修饰问题。

### 宏定义
```cpp
#define EXPORT_PLUGIN(className) \
    extern "C" { \
        IPlugin* create##className() { \
            return new className(); \
        } \
    }
```

### 使用方法

1. **在插件头文件中**：
   ```cpp
   #pragma once
   #include "../projectA/include/IPlugin.h"
   
   class MyPlugin : public IPlugin {
   public:
       MyPlugin() = default;
       void execute() override;
   };
   ```

2. **在插件实现文件中**：
   ```cpp
   #include "MyPlugin.h"
   #include <iostream>
   
   void MyPlugin::execute() {
       std::cout << "MyPlugin 正在执行..." << std::endl;
   }
   
   // 使用宏自动生成导出函数
   EXPORT_PLUGIN(MyPlugin)
   ```

### 宏展开结果

`EXPORT_PLUGIN(MyPlugin)` 会展开为：
```cpp
extern "C" {
    IPlugin* createMyPlugin() {
        return new MyPlugin();
    }
}
```

### 优势

1. **简化代码**：无需手动编写C风格导出函数
2. **避免错误**：减少手动编写时的拼写错误
3. **统一格式**：所有插件使用相同的导出函数命名规则
4. **易于维护**：修改导出逻辑只需修改宏定义

### 示例

参见 `MyPluginA.cpp` 和 `MyPluginB.cpp` 中的使用示例。