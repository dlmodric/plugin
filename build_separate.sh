#!/bin/bash

echo "=== 分离构建模式：先构建动态库，再构建主程序 ==="

# 设置错误时退出
set -e

# 1. 构建 projectB 动态库
echo "步骤1: 构建 projectB 动态库..."
cd projectB

# 清理之前的构建
rm -rf build
mkdir -p build
cd build

# 配置和构建
cmake ..
make -j$(nproc 2>/dev/null || echo 4)

echo "✅ projectB 动态库构建完成"
ls -la libtestB.*

# 2. 构建 projectA 主程序
echo ""
echo "步骤2: 构建 projectA 主程序..."
cd ../../projectA

# 清理之前的构建
rm -rf build
mkdir -p build
cd build

# 配置和构建
cmake ..
make -j$(nproc 2>/dev/null || echo 4)

echo "✅ projectA 主程序构建完成"
ls -la plugin_test

# 3. 运行测试
echo ""
echo "步骤3: 运行测试..."
echo "动态库位置："
ls -la ../../projectB/build/libtestB.*

echo ""
echo "运行主程序："
./plugin_test

echo ""
echo "🎉 构建和测试完成！"