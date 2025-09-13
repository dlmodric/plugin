#pragma once

#include "../projectA/include/IPlugin.h"
#include "../projectA/include/class_factory.h"

/**
 * MyPluginB - 另一个示例插件实现
 */
class MyPluginB : public IPlugin {
public:
    MyPluginB() = default;
    void execute(const NodeConfig& config) override;  // 修改函数签名
};

// 方案2：注册到ClassFactory
REGISTER_CLASS(MyPluginB)

