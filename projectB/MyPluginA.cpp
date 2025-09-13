#include "MyPluginA.h"
#include <iostream>

void MyPluginA::execute(const NodeConfig& config) {
    std::cout << "MyPluginA 正在执行..." << std::endl;
    std::cout << "=== NodeConfig 参数信息 ===" << std::endl;
    const_cast<NodeConfig&>(config).print();  // 调用print方法打印参数
    std::cout << "=== MyPluginA 执行完成 ===" << std::endl;
}

