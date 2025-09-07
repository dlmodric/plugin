#include <iostream>
#include <memory>
#include "include/IPlugin.h"
#include "include/class_factory.h"

int main()
{

    std::cout << "=== 动态插件加载测试（CMake链接方案） ===" << std::endl;
    
    // 直接使用ClassFactory单例，通过链接的动态库自动初始化
    ClassFactory* factory = &ClassFactory::getInstance();
    if (!factory) {
        std::cerr << "❌ 获取ClassFactory实例失败" << std::endl;
        return 1;
    }
    
    std::cout << "✅ 成功获取ClassFactory实例（通过CMake链接）" << std::endl;
    
    // 显示已注册的类
    auto registeredClasses = factory->getRegisteredClasses();
    std::cout << "📋 已注册的类数量: " << factory->getRegisteredCount() << std::endl;
    for (const auto& className : registeredClasses) {
        std::cout << "   - " << className << std::endl;
    }
    
    // 创建插件实例
     std::string pluginName = "MyPluginA";
    if (factory->isRegistered(pluginName)) {
        std::cout << "✅ 找到已注册的插件: " << pluginName << std::endl;
        
        auto plugin = factory->createObject(pluginName);
        if (plugin) {
            std::cout << "✅ 成功创建插件实例" << std::endl;
            plugin->execute();
        } else {
            std::cout << "❌ 创建插件实例失败" << std::endl;
        }
    } else {
        std::cout << "❌ 插件 " << pluginName << " 未注册" << std::endl;
    }
    pluginName = "MyPluginB";
    if (factory->isRegistered(pluginName)) {
        std::cout << "✅ 找到已注册的插件: " << pluginName << std::endl;

        auto plugin = factory->createObject(pluginName);
        if (plugin) {
            std::cout << "✅ 成功创建插件实例" << std::endl;
            plugin->execute();
        } else {
            std::cout << "❌ 创建插件实例失败" << std::endl;
        }
    } else {
        std::cout << "❌ 插件 " << pluginName << " 未注册" << std::endl;
    }
    
    // 无需手动清理，动态库会在程序结束时自动卸载
    std::cout << "=== 测试完成 ===" << std::endl;
    
    return 0;
}