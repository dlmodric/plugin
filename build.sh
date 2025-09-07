#!/bin/bash

# 构建脚本
# 用于编译projectA和projectB

set -e  # 遇到错误立即退出

echo "🔨 开始构建项目..."

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 检查是否存在必要的文件
check_files() {
    echo -e "${BLUE}📋 检查项目文件...${NC}"
    
    if [ ! -f "projectA/CMakeLists.txt" ]; then
        echo -e "${RED}❌ projectA/CMakeLists.txt 不存在${NC}"
        exit 1
    fi
    
    if [ ! -f "projectB/CMakeLists.txt" ]; then
        echo -e "${RED}❌ projectB/CMakeLists.txt 不存在${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}✅ 项目文件检查通过${NC}"
}

# 构建projectB (动态库)
build_projectB() {
    echo -e "${BLUE}🔧 构建 projectB (动态库)...${NC}"
    
    cd projectB
    
    # 清理之前的构建产物
    make clean 2>/dev/null || true
    rm -f *.dylib *.so *.a
    
    # CMake配置
    echo -e "${YELLOW}⚙️  配置CMake...${NC}"
    cmake . || {
        echo -e "${RED}❌ projectB CMake配置失败${NC}"
        exit 1
    }
    
    # 编译
    echo -e "${YELLOW}🔨 编译中...${NC}"
    make || {
        echo -e "${RED}❌ projectB 编译失败${NC}"
        exit 1
    }
    
    # 检查生成的动态库
    if [ -f "libtestB.dylib" ] || [ -f "libtestB.so" ]; then
        echo -e "${GREEN}✅ projectB 动态库构建成功${NC}"
        ls -la *.dylib *.so 2>/dev/null || true
    else
        echo -e "${RED}❌ projectB 动态库生成失败${NC}"
        exit 1
    fi
    
    cd ..
}

# 构建projectA (主程序)
build_projectA() {
    echo -e "${BLUE}🔧 构建 projectA (主程序)...${NC}"
    
    cd projectA
    
    # 清理之前的构建产物
    make clean 2>/dev/null || true
    rm -f plugin_test
    
    # CMake配置
    echo -e "${YELLOW}⚙️  配置CMake...${NC}"
    cmake . || {
        echo -e "${RED}❌ projectA CMake配置失败${NC}"
        exit 1
    }
    
    # 编译
    echo -e "${YELLOW}🔨 编译中...${NC}"
    make || {
        echo -e "${RED}❌ projectA 编译失败${NC}"
        exit 1
    }
    
    # 检查生成的可执行文件
    if [ -f "plugin_test" ]; then
        echo -e "${GREEN}✅ projectA 主程序构建成功${NC}"
        ls -la plugin_test
    else
        echo -e "${RED}❌ projectA 主程序生成失败${NC}"
        exit 1
    fi
    
    cd ..
}

# 复制动态库到主程序目录
copy_libraries() {
    echo -e "${BLUE}📦 复制动态库...${NC}"
    
    # 复制动态库到projectA目录
    if [ -f "projectB/libtestB.dylib" ]; then
        cp projectB/libtestB.dylib projectA/
        echo -e "${GREEN}✅ 已复制 libtestB.dylib${NC}"
    elif [ -f "projectB/libtestB.so" ]; then
        cp projectB/libtestB.so projectA/
        echo -e "${GREEN}✅ 已复制 libtestB.so${NC}"
    else
        echo -e "${RED}❌ 找不到动态库文件${NC}"
        exit 1
    fi
}

# 运行测试
run_test() {
    echo -e "${BLUE}🧪 运行测试...${NC}"
    
    cd projectA
    
    echo -e "${YELLOW}📋 当前目录文件:${NC}"
    ls -la
    
    echo -e "${YELLOW}🚀 运行主程序:${NC}"
    ./plugin_test || {
        echo -e "${RED}❌ 程序运行失败${NC}"
        exit 1
    }
    
    cd ..
}

# 主函数
main() {
    echo -e "${GREEN}🎯 插件系统构建脚本${NC}"
    echo "=================================="
    
    check_files
    build_projectB
    build_projectA
    copy_libraries
    
    echo ""
    echo -e "${GREEN}🎉 构建完成！${NC}"
    echo "=================================="
    echo -e "${BLUE}📁 构建产物位置:${NC}"
    echo "  - projectA/plugin_test (主程序)"
    echo "  - projectB/libtestB.* (动态库)"
    echo ""
    
    # 询问是否运行测试
    read -p "是否运行测试程序? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        run_test
        echo -e "${GREEN}✅ 测试完成！${NC}"
    fi
}

# 执行主函数
main "$@"