#include "MyPluginB.h"
#include "MyPluginA.h"
#include "../projectA/include/class_factory.h"
#include <iostream>

void MyPluginB::execute(const NodeConfig& config) {
    std::cout << "MyPluginB 正在执行...这是第二个插件!" << std::endl;
    std::cout << "=== NodeConfig 参数信息 ===" << std::endl;
    const_cast<NodeConfig&>(config).print();  // 调用print方法打印参数
    std::cout << "=== MyPluginB 执行完成 ===" << std::endl;
}