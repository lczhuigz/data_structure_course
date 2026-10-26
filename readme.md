# 数据结构课程实验

本仓库包含《数据结构》课程的实验代码，使用 C / C++ 编写，基于 CMake 构建。

## 目录结构

```
data_structure_course/
├── README.md
├── license
├── .gitignore
├── labs/
    ├── lab01/              # 实验1：链表实现的学生信息管理系统（C）
    │   ├── CMakeLists.txt
    │   └── main.c
    ├── lab02/              # 实验2：链式栈的构建与操作（C++）
    │   ├── CMakeLists.txt
    │   └── main.cpp
    └── lab_report/         # 实验报告
        ├── finished_report/  # 已完成的实验报告
        └── src_report/       # 实验报告模板
```

## 实验简介

### 实验1：学生信息管理系统（单链表）

使用单链表实现一个学生信息管理系统，支持以下功能：

- 显示所有学生信息
- 按位置插入学生
- 删除指定位置的学生
- 修改指定位置的学生信息
- 按姓名查找学生
- 按位置查找学生
- 统计学生人数

**涉及知识点**：单链表的初始化、插入、删除、查找、遍历、销毁等基础操作。

### 实验2：链式栈

使用链式结构（链表）实现栈，演示栈的创建与基本操作：

- 初始化栈
- 入栈（push）
- 出栈（pop）
- 求栈长度（length）
- 打印栈内容（bottom → top）
- 释放栈（destroy）

**涉及知识点**：栈的链式存储、后进先出（LIFO）特性、指针操作与内存管理。

## 构建与运行

每个实验目录独立构建。以 `lab01` 为例：

```bash
cd labs/lab01
mkdir build && cd build
cmake ..
make
./lab01
```

`lab02` 同理：

```bash
cd labs/lab02
mkdir build && cd build
cmake ..
make
./lab02
```

> 推荐 CMake 版本 ≥ 3.12；C++ 标准：C++11。

## 实验报告

`labs/lab_report/` 目录下存放实验报告：

- `src_report/`：报告模板（`姓名-班级-学号-数据结构实验X.docx`）
- `finished_report/`：已完成的报告

## 环境要求

| 工具 | 最低版本 |
| --- | --- |
| CMake | 3.12 |
| GCC / Clang / MSVC | 任一支持 C11 / C++11 的编译器 |

## License

详见 [license](./license) 文件。