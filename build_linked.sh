#!/bin/bash

echo "=== 使用CMake链接方式构建项目 ==="

# 清理之前的构建
echo "🧹 清理之前的构建文件..."
rm -rf projectA/build
rm -rf projectB/build

# 创建构建目录
mkdir -p projectA/build

# 进入projectA构建目录
cd projectA/build

echo "🔨 开始构建项目（CMake链接方式）..."

# 配置项目
cmake ..

# 编译项目
make

echo "✅ 构建完成！"

# 检查生成的文件
echo "📁 生成的文件："
ls -la

echo ""
echo "🚀 运行测试程序："
./plugin_test

echo ""
echo "=== 构建和测试完成 ==="