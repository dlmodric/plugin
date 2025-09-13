#!/bin/bash

# 构建脚本 - 按正确顺序构建所有项目
# 作者: DenisYang
# 版本: 1.0.0

set -e  # 遇到错误立即退出

echo "=== 开始构建所有项目 ==="

# 清理之前的构建
echo "清理之前的构建..."
rm -rf projectA/build projectB/build projectX/build

# 1. 首先构建 projectA (插件管理器库)
echo "=== 构建 ProjectA ==="
cd projectA
mkdir -p build
cd build
cmake ..
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
echo "✅ ProjectA 构建完成"
cd ../..


# 2. 然后构建 projectB (插件库)
echo "=== 构建 ProjectB ==="
cd projectB
mkdir -p build
cd build
cmake ..
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
echo "✅ ProjectB 构建完成"
cd ../..

# 3. 最后构建 projectX (主程序)
echo "=== 构建 ProjectX ==="
cd projectX
mkdir -p build
cd build
cmake ..
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
echo "✅ ProjectX 构建完成"
cd ../..

echo "=== 所有项目构建完成 ==="
echo ""
echo "运行方式："
echo "运行 ProjectX 主程序: ./projectX/build/projectX"
echo ""
echo "注意：ProjectX 通过动态库调用 ProjectA 的功能"