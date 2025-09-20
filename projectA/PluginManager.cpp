#include "include/PluginManager.h"

PluginManager::PluginManager() : factory_(nullptr), initialized_(false) {
}

PluginManager::~PluginManager() {
    // 卸载所有已加载的动态库
    for (void* handle : loadedLibraries_) {
        if (handle) {
            dlclose(handle);
        }
    }
    loadedLibraries_.clear();
}

bool PluginManager::initialize() {
    std::cout << "=== 动态插件加载测试（动态加载方案） ===" << std::endl;
    
    // 获取ClassFactory单例
    factory_ = &ClassFactory::getInstance();
    if (!factory_) {
        std::cerr << "❌ 获取ClassFactory实例失败" << std::endl;
        return false;
    }
    
    std::cout << "✅ 成功获取ClassFactory实例" << std::endl;
    initialized_ = true;
    return true;
}

bool PluginManager::loadPluginLibrary(const std::string& libraryPath) {
    if (!initialized_) {
        std::cerr << "❌ PluginManager未初始化" << std::endl;
        return false;
    }

    std::cout << "🔄 正在加载插件库: " << libraryPath << std::endl;

    // 使用dlopen加载动态库
    void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (!handle) {
        std::cerr << "❌ 加载动态库失败: " << dlerror() << std::endl;
        return false;
    }

    // 保存句柄
    loadedLibraries_.push_back(handle);
    
    std::cout << "✅ 成功加载插件库: " << libraryPath << std::endl;
    std::cout << "📋 当前已注册插件数量: " << factory_->getRegisteredCount() << std::endl;
    
    return true;
}

bool PluginManager::executePlugin(const std::string& pluginName, const NodeConfig& config) {
    if (!initialized_) {
        std::cerr << "❌ PluginManager未初始化" << std::endl;
        return false;
    }

    if (factory_->isRegistered(pluginName)) {
        std::cout << "✅ 找到已注册的插件: " << pluginName << std::endl;
        
        auto plugin = factory_->createObject(pluginName);
        if (plugin) {
            std::cout << "✅ 成功创建插件实例" << std::endl;
            plugin->execute(config);  // 传递NodeConfig参数
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

// 向后兼容的无参数版本
bool PluginManager::executePlugin(const std::string& pluginName) {
    // 创建一个默认的NodeConfig
    NodeConfig defaultConfig;
    defaultConfig.id = "default";
    defaultConfig.name = "Default Config";
    defaultConfig.type = NodeType::PROCESS;
    defaultConfig.description = "Default configuration for backward compatibility";
    
    return executePlugin(pluginName, defaultConfig);
}

int PluginManager::executeAllPlugins(const NodeConfig& config) {
    if (!initialized_) {
        std::cerr << "❌ PluginManager未初始化" << std::endl;
        return 0;
    }

    auto registeredClasses = factory_->getRegisteredClasses();
    int successCount = 0;
    
    for (const auto& className : registeredClasses) {
        if (executePlugin(className, config)) {
            successCount++;
        }
    }
    
    return successCount;
}

// 向后兼容的无参数版本
int PluginManager::executeAllPlugins() {
    // 创建一个默认的NodeConfig
    NodeConfig defaultConfig;
    defaultConfig.id = "default";
    defaultConfig.name = "Default Config";
    defaultConfig.type = NodeType::PROCESS;
    defaultConfig.description = "Default configuration for backward compatibility";
    
    return executeAllPlugins(defaultConfig);
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