
cmake_minimum_required(VERSION 3.16)
project(PluginDemo)

# 全局设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子项目
add_subdirectory(projectA)
add_subdirectory(projectB)

# 打印项目信息
message(STATUS "=== 主项目配置 ===")
message(STATUS "项目名称: ${PROJECT_NAME}")
message(STATUS "CMake版本: ${CMAKE_VERSION}")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER}")
message(STATUS "==================")
