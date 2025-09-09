#include <iostream>
#include <memory>
#include "PluginManager.h"

int main()
{
    std::cout << "=== ProjectX 调用 ProjectA 动态库测试 ===" << std::endl;
    
    // 创建插件管理器实例
    PluginManager manager;
    
    // 初始化插件管理器
    if (!manager.initialize()) {
        std::cerr << "❌ 插件管理器初始化失败" << std::endl;
        return 1;
    }
    
    std::cout << "✅ ProjectX 成功初始化 PluginManager" << std::endl;
    
    // 打印插件状态信息
    manager.printStatus();
    
    // 执行所有插件
    std::cout << "\n=== 开始执行插件 ===" << std::endl;
    int successCount = manager.executeAllPlugins();
    std::cout << "成功执行了 " << successCount << " 个插件" << std::endl;
    
    // 也可以单独执行指定插件
    std::cout << "\n=== 单独执行指定插件 ===" << std::endl;
    manager.executePlugin("MyPluginA");
    manager.executePlugin("MyPluginB");
    
    std::cout << "\n=== ProjectX 测试完成 ===" << std::endl;
    
    return 0;
}