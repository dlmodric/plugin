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

# 链接必要的库
target_link_libraries(plugin_test PRIVATE ${CMAKE_DL_LIBS} c++ c++abi)