#include "MyPluginB.h"
#include "MyPluginA.h"
#include "../projectA/include/class_factory.h"
#include <iostream>

void MyPluginB::execute() {
    std::cout << "MyPluginB 正在执行...这是第二个插件!" << std::endl;
}