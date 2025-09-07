#pragma once

#include "../projectA/include/IPlugin.h"
#include "../projectA/include/class_factory.h"

/**
 * MyPluginB - 另一个示例插件实现
 */
class MyPluginB : public IPlugin {
public:
    MyPluginB() = default;
    void execute() override;
};

// 方案2：注册到ClassFactory
REGISTER_CLASS(MyPluginB)

