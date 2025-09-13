#!/bin/bash

# 清理无用文件脚本
# 用于清理编译产物、临时文件等

echo "🧹 开始清理无用文件..."

# 统计清理前的文件数量
total_files_before=$(find . -type f | wc -l)

# 清理编译产物
echo "清理编译产物..."
find . -name "*.o" -delete 2>/dev/null
find . -name "*.so" -delete 2>/dev/null
find . -name "*.dylib" -delete 2>/dev/null
find . -name "*.a" -delete 2>/dev/null
find . -name "*.exe" -delete 2>/dev/null

# 清理可执行文件（排除脚本）
find . -name "plugin_test" -delete 2>/dev/null
find . -name "testB" -delete 2>/dev/null

# 清理CMake产物
echo "清理CMake产物..."
find . -name "CMakeCache.txt" -delete 2>/dev/null
find . -name "cmake_install.cmake" -delete 2>/dev/null
find . -name "Makefile" -delete 2>/dev/null
find . -name "CMakeFiles" -type d -exec rm -rf {} + 2>/dev/null

# 清理构建目录
echo "清理构建目录..."
# 清理根目录的构建目录
rm -rf build/ 2>/dev/null
rm -rf cmake-build-debug/ 2>/dev/null
rm -rf cmake-build-release/ 2>/dev/null

# 清理所有子项目的构建目录
echo "清理子项目构建目录..."
find . -name "build" -type d -exec rm -rf {} + 2>/dev/null
find . -name "cmake-build-debug" -type d -exec rm -rf {} + 2>/dev/null
find . -name "cmake-build-release" -type d -exec rm -rf {} + 2>/dev/null

# 清理临时文件
echo "清理临时文件..."
find . -name "*.tmp" -delete 2>/dev/null
find . -name "*.bak" -delete 2>/dev/null
find . -name "*.swp" -delete 2>/dev/null
find . -name "*.swo" -delete 2>/dev/null
find . -name "*~" -delete 2>/dev/null

# 清理IDE配置文件
echo "清理IDE配置文件..."
rm -rf .vscode/ 2>/dev/null
rm -rf .idea/ 2>/dev/null
find . -name "*.user" -delete 2>/dev/null

# 清理日志文件
echo "清理日志文件..."
find . -name "*.log" -delete 2>/dev/null

# 清理macOS系统文件
echo "清理系统文件..."
find . -name ".DS_Store" -delete 2>/dev/null

# 统计清理后的文件数量
total_files_after=$(find . -type f | wc -l)
cleaned_files=$((total_files_before - total_files_after))

echo "✅ 清理完成！"
echo "📊 清理统计："
echo "   清理前文件数: $total_files_before"
echo "   清理后文件数: $total_files_after"
echo "   已清理文件数: $cleaned_files"

# 显示剩余的主要文件
echo ""
echo "📁 剩余主要文件："
find . -name "*.h" -o -name "*.cpp" -o -name "*.sh" -o -name "CMakeLists.txt" -o -name "*.md" | sort