cmake_minimum_required(VERSION 3.16)
project(testB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件路径
include_directories(../projectA/include)

# 构建插件动态库
add_library(testB SHARED MyPluginA.cpp MyPluginA.h MyPluginB.cpp MyPluginB.h)

# 设置输出名称
set_target_properties(testB PROPERTIES 
    OUTPUT_NAME "testB"
    # 确保符号可见性
    CXX_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN OFF
)