#include "include/PluginManager.h"

PluginManager::PluginManager() : factory_(nullptr), initialized_(false) {
}

bool PluginManager::initialize() {
    std::cout << "=== 动态插件加载测试（CMake链接方案） ===" << std::endl;
    
    // 直接使用ClassFactory单例，通过链接的动态库自动初始化
    factory_ = &ClassFactory::getInstance();
    if (!factory_) {
        std::cerr << "❌ 获取ClassFactory实例失败" << std::endl;
        return false;
    }
    
    std::cout << "✅ 成功获取ClassFactory实例（通过CMake链接）" << std::endl;
    initialized_ = true;
    return true;
}

bool PluginManager::executePlugin(const std::string& pluginName) {
    if (!initialized_) {
        std::cerr << "❌ PluginManager未初始化" << std::endl;
        return false;
    }

    if (factory_->isRegistered(pluginName)) {
        std::cout << "✅ 找到已注册的插件: " << pluginName << std::endl;
        
        auto plugin = factory_->createObject(pluginName);
        if (plugin) {
            std::cout << "✅ 成功创建插件实例" << std::endl;
            plugin->execute();
            return true;
        } else {
            std::cout << "❌ 创建插件实例失败" << std::endl;
            return false;
        }
    } else {
        std::cout << "❌ 插件 " << pluginName << " 未注册" << std::endl;
        return false;
    }
}

int PluginManager::executeAllPlugins() {
    if (!initialized_) {
        std::cerr << "❌ PluginManager未初始化" << std::endl;
        return 0;
    }

    auto registeredClasses = factory_->getRegisteredClasses();
    int successCount = 0;
    
    for (const auto& className : registeredClasses) {
        if (executePlugin(className)) {
            successCount++;
        }
    }
    
    return successCount;
}

size_t PluginManager::getPluginCount() const {
    if (!initialized_ || !factory_) {
        return 0;
    }
    return factory_->getRegisteredCount();
}

std::vector<std::string> PluginManager::getRegisteredPlugins() const {
    if (!initialized_ || !factory_) {
        return {};
    }
    return factory_->getRegisteredClasses();
}

bool PluginManager::isPluginRegistered(const std::string& pluginName) const {
    if (!initialized_ || !factory_) {
        return false;
    }
    return factory_->isRegistered(pluginName);
}

void PluginManager::printStatus() const {
    if (!initialized_) {
        std::cout << "❌ PluginManager未初始化" << std::endl;
        return;
    }

    // 显示已注册的类
    auto registeredClasses = factory_->getRegisteredClasses();
    std::cout << "📋 已注册的类数量: " << factory_->getRegisteredCount() << std::endl;
    for (const auto& className : registeredClasses) {
        std::cout << "   - " << className << std::endl;
    }
}