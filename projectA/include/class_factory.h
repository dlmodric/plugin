#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "IPlugin.h"

/**
 * 类工厂单例，负责管理和创建所有已注册的类
 */
class ClassFactory {
public:
    static ClassFactory& getInstance() {
        static ClassFactory instance;
        return instance;
    }

    using CreateFunc = IPlugin*(*)();
    
    /**
     * 注册类到工厂
     * @param className 类名
     * @param creator 创建函数
     */
    void registerClass(const std::string& className, CreateFunc creator) {
        registry[className] = creator;
    }

    /**
     * 创建对象实例
     * @param className 类名
     * @return 对象智能指针，失败返回nullptr
     */
    std::unique_ptr<IPlugin> createObject(const std::string& className) {
        auto it = registry.find(className);
        if (it != registry.end()) {
            return std::unique_ptr<IPlugin>(it->second());
        }
        return nullptr;
    }

    /**
     * 检查类是否已注册
     * @param className 类名
     * @return 是否已注册
     */
    bool isRegistered(const std::string& className) const {
        return registry.find(className) != registry.end();
    }

    /**
     * 获取已注册类的数量
     * @return 注册类数量
     */
    size_t getRegisteredCount() const {
        return registry.size();
    }

    /**
     * 获取所有已注册的类名
     * @return 类名列表
     */
    std::vector<std::string> getRegisteredClasses() const {
        std::vector<std::string> classes;
        for (const auto& pair : registry) {
            classes.push_back(pair.first);
        }
        return classes;
    }

private:
    ClassFactory() = default;
    ClassFactory(const ClassFactory&) = delete;
    ClassFactory& operator=(const ClassFactory&) = delete;

    std::map<std::string, CreateFunc> registry;
};

/**
 * 类注册辅助类，利用静态对象的生命周期自动完成注册
 */
template<typename T>
class ClassRegisterHelper {
public:
    explicit ClassRegisterHelper(const std::string& className) {
        ClassFactory::getInstance().registerClass(className, &createInstance);
    }
    
private:
    static IPlugin* createInstance() {
        return new T();
    }
};

/**
 * 宏定义，简化类注册过程
 */
#define REGISTER_CLASS(className) \
    static ClassRegisterHelper<className> reg_##className(#className);

/**
 * 导出ClassFactory实例的宏
 * 用于从动态库中获取ClassFactory
 */
#define EXPORT_CLASS_FACTORY() \
    extern "C" { \
        ClassFactory* getClassFactory() { \
            return &ClassFactory::getInstance(); \
        } \
    }