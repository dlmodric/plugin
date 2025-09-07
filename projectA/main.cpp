#include <iostream>
#include <dlfcn.h>
#include <memory>
#include "include/IPlugin.h"
#include "include/class_factory.h"

int main()
{

    std::cout << "=== 动态插件加载测试（ClassFactory方案） ===" << std::endl;
    
    // 加载动态库
    const char* libPath = "libtestB.dylib";
    void* handle = dlopen(libPath, RTLD_LAZY);
    
    if (!handle) {
        std::cerr << "无法加载动态库: " << dlerror() << std::endl;
        std::cout << "请先编译 projectB 生成动态库" << std::endl;
        return 1;
    }
    
    std::cout << "✅ 成功加载动态库: " << libPath << std::endl;
    
    // 获取ClassFactory实例
    typedef ClassFactory* (*GetClassFactoryFunc)();
    GetClassFactoryFunc getClassFactory = (GetClassFactoryFunc) dlsym(handle, "getClassFactory");
    
    if (!getClassFactory) {
        std::cerr << "无法找到getClassFactory函数: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }
    
    ClassFactory* factory = getClassFactory();
    if (!factory) {
        std::cerr << "❌ 获取ClassFactory实例失败" << std::endl;
        dlclose(handle);
        return 1;
    }
    
    std::cout << "✅ 成功获取ClassFactory实例" << std::endl;
    
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
    
    // 清理
    dlclose(handle);
    std::cout << "=== 测试完成 ===" << std::endl;
    
    return 0;
}