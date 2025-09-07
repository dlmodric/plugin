cmake_minimum_required(VERSION 3.16)
project(PluginDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器和链接器标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

# 构建主程序
add_executable(plugin_test main.cpp)
target_include_directories(plugin_test PRIVATE include)

# 直接链接动态库（简化版本）
find_library(TESTB_LIBRARY testB PATHS ../projectB/build NO_DEFAULT_PATH REQUIRED)
target_link_libraries(plugin_test PRIVATE ${TESTB_LIBRARY})
set_target_properties(plugin_test PROPERTIES BUILD_RPATH "../projectB/build")