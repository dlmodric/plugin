cmake_minimum_required(VERSION 3.16)
project(testB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出路径为build目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# 打印输出目录信息
message(STATUS "输出目录: ${CMAKE_CURRENT_SOURCE_DIR}/build")

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

# 链接projectA的动态库以解决ClassFactory符号未定义问题
find_library(PLUGINA_LIBRARY pluginA PATHS ../projectA/build NO_DEFAULT_PATH)
if(PLUGINA_LIBRARY)
    target_link_libraries(testB PRIVATE ${PLUGINA_LIBRARY})
    message(STATUS "找到并链接projectA库: ${PLUGINA_LIBRARY}")
else()
    message(WARNING "未找到projectA库，请先构建projectA")
endif()