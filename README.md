# C++ 控制台计算器项目
## 项目描述
该项目旨在实现一个功能完善的控制台计算器，支持基本的算术运算、高精度运算以及处理分数和小数。通过结合 gmp，确保计算的精度和效率。用户可以在命令行中输入表达式，并获得相应的计算结果。

## 功能列表
- 加法：计算两个数的和。
- 减法：计算两个数的差。
- 乘法：计算两个数的积。
- 除法：计算两个数的商，处理除数为零的情况。
- 分数运算：支持分数形式的输入和计算，能够简化结果。
- 小数运算：支持小数形式的输入和计算，输出分数。

## 技术实现
### 语言
- 使用 C++ 进行开发。
- 使用 gmp 库实现大数运算。

### 数据类型
- 使用 gmp 库提供的mpq_class类型来表示分数。

### 用户交互
- 提供简单的命令行界面，用户可以输入表达式并选择运算类型。
- 对输入进行验证，确保用户输入格式正确。

## 项目结构
```
├── CMakeLists.txt
├── README.md
├── lib
│   ├── libgmp.a       # gmp 库
│   └── libgmpxx.a     # gmpxx 库
└── src                # 源代码目录
    ├── calculator.cpp # 计算器类实现
    ├── calculator.h   # 计算器类定义
    ├── fraction.cpp   # 分数类实现
    ├── fraction.h     # 分数类定义
    ├── gmp.h          # gmp 头文件
    ├── gmpxx.h        # gmpxx 头文件
    └── main.cpp       # 主程序入口
```

## 编译与运行
### 编译
```
mkdir build
cd build
cmake ..
make
```

### 运行
```
./calculator
```

### 错误
- 若找不到 gmp 库，或其他与 gmp 库相关的错误，Windows 用户前往[大佬的博客](https://wdh.hk/docs/gmp-windows/)查看解决方案；macOS 与 Linux 用户使用 ```brew install gmp```安装
- 若出现未知错误，请提交 issue

## TODO
- 添加 Z3
- 指数运算
- 对数函数
- 三角函数
- ……
