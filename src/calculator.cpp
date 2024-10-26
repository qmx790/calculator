#include "calculator.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "gmpxx.h"

// 将小数转换为分数的功能
mpq_class decimalToFraction(const std::string& decimal) {
    if (decimal.empty()) {
        throw std::invalid_argument("无效的输入");
    }

    size_t decimalPoint = decimal.find('.');
    if (decimalPoint == std::string::npos) {
        return mpq_class(decimal); // 如果没有小数点，直接返回 mpq_class
    }

    // 整数部分
    std::string wholePart = decimal.substr(0, decimalPoint);
    // 小数部分
    std::string fractionalPart = decimal.substr(decimalPoint + 1);

    // 计算分母
    mpq_class denominator = mpq_class(1) * pow(10, fractionalPart.size());
    // 组装分子
    std::string numeratorString = wholePart + fractionalPart;
    mpq_class numerator = mpq_class(numeratorString);

    return numerator / denominator; // 返回分数形式
}

// 计算表达式
mpq_class Calculator::calculate(const std::string& input) {
    std::istringstream stream(input);
    mpq_class left;
    char operation;

    // 尝试读取左侧的值
    std::string leftStr;
    if (!(stream >> leftStr)) {
        throw std::invalid_argument("无效的表达式");
    }

    // 解析左侧分数或小数
    try {
        if (leftStr.find('.') != std::string::npos) {
            left = decimalToFraction(leftStr); // 使用函数将小数转换为分数
        } else {
            left = mpq_class(leftStr); // 直接解析分数
        }
    } catch (...) {
        throw std::invalid_argument("无效的分数或小数格式");
    }

    // 尝试读取操作符
    if (stream >> operation) {
        mpq_class right; // 右侧数

        // 检查并读取右侧的值
        std::string rightStr;
        if (!(stream >> rightStr)) {
            throw std::invalid_argument("无效的表达式");
        }

        // 解析右侧
        try {
            if (rightStr.find('.') != std::string::npos) {
                right = decimalToFraction(rightStr); // 小数处理
            } else {
                right = mpq_class(rightStr); // 分数处理
            }
        } catch (...) {
            throw std::invalid_argument("无效的分数或小数格式");
        }

        // 根据操作符执行相应的运算
        switch (operation) {
            case '+':
                return left + right; // 加法
            case '-':
                return left - right; // 减法
            case '*':
                return left * right; // 乘法
            case '/':
                if (right == 0) {
                    throw std::invalid_argument("除数不能为零");
                }
                return left / right; // 除法
            default:
                throw std::invalid_argument("未知的操作符");
        }
    }

    // 如果没有操作符，直接返回左侧的结果
    return left;
}
