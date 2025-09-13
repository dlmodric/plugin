#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "params.h"  // 添加NodeConfig的头文件

/* *
 * 这是一个插件接口。所有第三方开发者实现的类都必须继承此接口。
 */
class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual void execute(const NodeConfig& config) = 0;  // 修改函数签名，添加NodeConfig参数
};