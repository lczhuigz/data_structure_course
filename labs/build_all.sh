#!/bin/bash

echo -e "\e[36m开始批量构建实验...\e[0m"

# 遍历当前目录下所有以 lab 开头的目录
for dir in lab*/; do
    # 如果没匹配到任何文件夹，跳过
    [ -d "$dir" ] || continue
    
    lab_dir=${dir%/}
    
    # 核心过滤：检查该目录下是否真的有 CMakeLists.txt 文件
    if [ ! -f "$lab_dir/CMakeLists.txt" ]; then
        echo -e "\e[90m跳过: $lab_dir (找不到 CMakeLists.txt，可能不是实验代码目录)\e[0m"
        continue
    fi

    echo -e "\e[36m========================================\e[0m"
    echo -e "\e[33m正在配置并编译: $lab_dir ...\e[0m"
    
    # 使用 CMake 和 Ninja 配置项目
    cmake -B "$lab_dir/build" -S "$lab_dir" -G Ninja
    
    if [ $? -eq 0 ]; then
        ninja -C "$lab_dir/build"
        
        if [ $? -ne 0 ]; then
            echo -e "\e[31m[错误] $lab_dir 编译失败！\e[0m"
        fi
    else
        echo -e "\e[31m[错误] $lab_dir 的 CMake 配置失败！\e[0m"
    fi
done

echo -e "\e[36m========================================\e[0m"
echo -e "\e[32m所有实验构建处理完毕！\e[0m"