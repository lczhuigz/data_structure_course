#!/bin/bash

echo -e "\e[36m========== 开始清理 build 目录 ==========\e[0m"

# 1. 遍历当前目录下所有以 lab 开头且紧跟数字的文件夹（排除 lab_report）
for dir in lab[0-9]*/; do
    # 如果没匹配到任何文件夹，跳过
    [ -d "$dir" ] || continue
    
    lab_dir=${dir%/}
    build_path="$lab_dir/build"
    
    if [ -d "$build_path" ]; then
        echo -e "\e[33m正在删除: $build_path\e[0m"
        rm -rf "$build_path"
        
        if [ -d "$build_path" ]; then
            echo -e "\e[31m[错误] 删除 $build_path 失败，文件可能被占用。\e[0m"
        fi
    else
        echo -e "\e[90m跳过: $lab_dir 没有 build 目录\e[0m"
    fi
done

# 2. 顺手清理根目录下可能存在的总 build 文件夹
if [ -d "build" ]; then
    echo -e "\e[33m正在删除根目录下的 build 文件夹\e[0m"
    rm -rf "build"
    
    if [ -d "build" ]; then
        echo -e "\e[31m[错误] 删除根目录 build 失败，文件可能被占用。\e[0m"
    fi
fi

echo -e "\e[36m========================================\e[0m"
echo -e "\e[32m清理完成！\e[0m"