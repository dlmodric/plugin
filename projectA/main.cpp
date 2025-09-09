#include <iostream>
#include <memory>
#include "include/PluginManager.h"

int main()
{
    // 创建插件管理器
    PluginManager manager;
    
    // 初始化插件管理器
    if (!manager.initialize()) {
        std::cerr << "❌ 插件管理器初始化失败" << std::endl;
        return 1;
    }
    
    // 打印状态信息
    manager.printStatus();
    
    // 执行指定插件
    manager.executePlugin("MyPluginA");
    manager.executePlugin("MyPluginB");
    
    // 无需手动清理，动态库会在程序结束时自动卸载
    std::cout << "=== 测试完成 ===" << std::endl;
    
    return 0;
}