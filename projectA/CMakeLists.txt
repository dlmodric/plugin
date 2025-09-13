cmake_minimum_required(VERSION 3.16)
project(PluginDemo)

# 定义自定义变量
set(PROJECT_VERSION "1.0.0")
set(PROJECT_AUTHOR "DenisYang")
set(BUILD_TYPE "Release")
set(PLUGIN_DIR "../projectB/build")
set(INCLUDE_DIR "include")

# 打印变量值
message(STATUS "=== 项目配置信息 ===")
message(STATUS "项目名称: ${PROJECT_NAME}")
message(STATUS "项目版本: ${PROJECT_VERSION}")
message(STATUS "项目作者: ${PROJECT_AUTHOR}")
message(STATUS "构建类型: ${BUILD_TYPE}")
message(STATUS "插件目录: ${PLUGIN_DIR}")
message(STATUS "头文件目录: ${INCLUDE_DIR}")
message(STATUS "CMake版本: ${CMAKE_VERSION}")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER}")
message(STATUS "==================")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出路径为build目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# 打印编译标准信息
message(STATUS "C++标准: ${CMAKE_CXX_STANDARD}")
message(STATUS "C++标准要求: ${CMAKE_CXX_STANDARD_REQUIRED}")
message(STATUS "输出目录: ${CMAKE_CURRENT_SOURCE_DIR}/build")

# 构建动态链接库
add_library(pluginA SHARED PluginManager.cpp src/class_factory.cpp)
target_include_directories(pluginA PRIVATE ${INCLUDE_DIR})
target_include_directories(pluginA PUBLIC ${INCLUDE_DIR})

# Linux特定的链接器标志，确保静态初始化对象不被优化掉
if(UNIX AND NOT APPLE)
    # 先添加链接器标志
    target_link_options(pluginA PRIVATE -Wl,--no-as-needed)
else()
    # 设置编译器和链接器标志
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
    # macOS 和其他平台使用正常链接
endif()

# 打印构建信息
message(STATUS "=== 构建配置 ===")
message(STATUS "动态库: pluginA")
message(STATUS "源文件: PluginManager.cpp, src/class_factory.cpp")
message(STATUS "头文件目录: ${INCLUDE_DIR}")
message(STATUS "构建完成: pluginA 动态库")
message(STATUS "===============")
