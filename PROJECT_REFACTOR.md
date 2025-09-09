# 项目重构说明

## 项目结构

```
plugin/
├── projectA/           # 插件管理器库
│   ├── include/
│   │   ├── IPlugin.h           # 插件接口
│   │   ├── class_factory.h     # 类工厂
│   │   └── PluginManager.h     # 插件管理器接口 (新增)
│   ├── PluginManager.cpp       # 插件管理器实现 (新增)
│   ├── main.cpp               # 测试程序
│   └── CMakeLists.txt         # 构建配置 (修改为生成动态库)
├── projectB/           # 插件实现库 (无变化)
│   ├── MyPluginA.h
│   ├── MyPluginA.cpp
│   ├── MyPluginB.h
│   ├── MyPluginB.cpp
│   └── CMakeLists.txt
├── projectX/           # 主程序项目 (新增)
│   ├── main.cpp               # 调用projectA动态库
│   └── CMakeLists.txt         # 构建配置
└── build_all.sh        # 一键构建脚本 (新增)
```

## 主要变化

### 1. ProjectA 的变化
- **新增**: `PluginManager.h` 和 `PluginManager.cpp` - 将原main函数功能封装成类
- **修改**: `CMakeLists.txt` - 现在编译成动态链接库 `libpluginA.so`
- **修改**: `main.cpp` - 现在使用新的PluginManager类

### 2. ProjectB 的变化
- **无变化**: 保持原有的插件实现，不需要任何修改

### 3. ProjectX (新项目)
- **新增**: 完整的新项目，调用ProjectA的动态库
- 通过PluginManager接口使用插件功能
- 保持了A调用B的方式不变

## 构建和运行

### 一键构建所有项目
```bash
./build_all.sh
```

### 手动构建
```bash
# 1. 构建 ProjectB
cd projectB && mkdir -p build && cd build
cmake .. && make
cd ../..

# 2. 构建 ProjectA
cd projectA && mkdir -p build && cd build
cmake .. && make
cd ../..

# 3. 构建 ProjectX
cd projectX && mkdir -p build && cd build
cmake .. && make
cd ../..
```

### 运行程序
```bash
# 运行 ProjectA 测试程序
./projectA/build/plugin_test

# 运行 ProjectX 主程序 (通过动态库调用ProjectA)
./projectX/build/projectX
```

## 技术实现

### PluginManager 接口
```cpp
class PluginManager {
public:
    bool initialize();                                    // 初始化插件管理器
    bool executePlugin(const std::string& pluginName);   // 执行指定插件
    int executeAllPlugins();                             // 执行所有插件
    size_t getPluginCount() const;                       // 获取插件数量
    std::vector<std::string> getRegisteredPlugins() const; // 获取插件列表
    bool isPluginRegistered(const std::string& pluginName) const; // 检查插件是否注册
    void printStatus() const;                            // 打印状态信息
};
```

### 动态库链接
- ProjectA 编译成 `libpluginA.so` 动态库
- ProjectX 链接 ProjectA 和 ProjectB 的动态库
- 保持了原有的插件加载机制不变

## 优势

1. **模块化**: ProjectA 现在是一个可重用的动态库
2. **接口封装**: 通过PluginManager提供清晰的API
3. **向后兼容**: ProjectB 无需任何修改
4. **灵活性**: ProjectX 可以灵活使用插件管理功能
5. **可扩展**: 其他项目也可以使用ProjectA的动态库