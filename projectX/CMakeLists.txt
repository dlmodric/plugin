cmake_minimum_required(VERSION 3.16)
project(ProjectX)

# 定义自定义变量
set(PROJECT_VERSION "1.0.0")
set(PROJECT_AUTHOR "DenisYang")
set(BUILD_TYPE "Release")
set(PLUGIN_A_DIR "../projectA/build")
set(PLUGIN_B_DIR "../projectB/build")
set(INCLUDE_DIR "include")

# 打印变量值
message(STATUS "=== 项目配置信息 ===")
message(STATUS "项目名称: ${PROJECT_NAME}")
message(STATUS "项目版本: ${PROJECT_VERSION}")
message(STATUS "项目作者: ${PROJECT_AUTHOR}")
message(STATUS "构建类型: ${BUILD_TYPE}")
message(STATUS "插件A目录: ${PLUGIN_A_DIR}")
message(STATUS "插件B目录: ${PLUGIN_B_DIR}")
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

# 构建主程序
add_executable(projectX main.cpp)
target_include_directories(projectX PRIVATE ${INCLUDE_DIR})
target_include_directories(projectX PRIVATE ../projectA/include)

# Linux特定的链接器标志，确保静态初始化对象不被优化掉
if(UNIX AND NOT APPLE)
    # 先添加链接器标志
    target_link_options(projectX PRIVATE -Wl,--no-as-needed)
else()
    # 设置编译器和链接器标志
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    # macOS 和其他平台使用正常链接
endif()

# 打印构建信息
message(STATUS "=== 构建配置 ===")
message(STATUS "可执行文件: projectX")
message(STATUS "源文件: main.cpp")
message(STATUS "头文件目录: ${INCLUDE_DIR}")

# 查找并链接projectA动态库
find_library(PLUGIN_A_LIBRARY pluginA PATHS ${PLUGIN_A_DIR} NO_DEFAULT_PATH REQUIRED)
message(STATUS "找到pluginA动态库: ${PLUGIN_A_LIBRARY}")

# 查找并链接projectB动态库
find_library(PLUGIN_B_LIBRARY testB PATHS ${PLUGIN_B_DIR} NO_DEFAULT_PATH REQUIRED)
message(STATUS "找到testB动态库: ${PLUGIN_B_LIBRARY}")

target_link_libraries(projectX PRIVATE ${PLUGIN_A_LIBRARY} ${PLUGIN_B_LIBRARY})
set_target_properties(projectX PROPERTIES BUILD_RPATH "${PLUGIN_A_DIR}:${PLUGIN_B_DIR}")

# 打印最终配置
message(STATUS "链接库: ${PLUGIN_A_LIBRARY}, ${PLUGIN_B_LIBRARY}")
message(STATUS "运行时路径: ${PLUGIN_A_DIR}:${PLUGIN_B_DIR}")
message(STATUS "===============")