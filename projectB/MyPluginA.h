#pragma once

#include "../projectA/include/IPlugin.h"
#include "../projectA/include/class_factory.h"

/**
 * MyPluginA - 示例插件实现
 */
class MyPluginA : public IPlugin {
public:
    MyPluginA() = default;
    void execute() override;
};

// 方案2：注册到ClassFactory
REGISTER_CLASS(MyPluginA)