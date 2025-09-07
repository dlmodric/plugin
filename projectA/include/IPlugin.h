#pragma once

#include <iostream>
#include <string>
#include <memory>

/* *
 * 这是一个插件接口。所有第三方开发者实现的类都必须继承此接口。
 */
class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual void execute() = 0;
};