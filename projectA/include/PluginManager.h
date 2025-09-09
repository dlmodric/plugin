#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "IPlugin.h"
#include "class_factory.h"

/**
 * 插件管理器类，封装插件的加载和执行功能
 */
class PluginManager {
public:
    PluginManager();
    ~PluginManager() = default;

    /**
     * 初始化插件管理器
     * @return 是否初始化成功
     */
    bool initialize();

    /**
     * 执行指定的插件
     * @param pluginName 插件名称
     * @return 是否执行成功
     */
    bool executePlugin(const std::string& pluginName);

    /**
     * 执行所有已注册的插件
     * @return 执行成功的插件数量
     */
    int executeAllPlugins();

    /**
     * 获取已注册的插件数量
     * @return 插件数量
     */
    size_t getPluginCount() const;

    /**
     * 获取所有已注册的插件名称
     * @return 插件名称列表
     */
    std::vector<std::string> getRegisteredPlugins() const;

    /**
     * 检查插件是否已注册
     * @param pluginName 插件名称
     * @return 是否已注册
     */
    bool isPluginRegistered(const std::string& pluginName) const;

    /**
     * 打印插件管理器状态信息
     */
    void printStatus() const;

private:
    ClassFactory* factory_;
    bool initialized_;
};