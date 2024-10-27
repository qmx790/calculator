#include "calculator.h"
#include <sstream>
#include <stdexcept>
#include <gmpxx.h>
#include <regex>
#include <stack>

// 将小数转换为分数的功能
mpq_class decimalToFraction(const std::string &decimal) {
    if (decimal.empty()) {
        throw std::invalid_argument("无效的输入");
    }

    size_t decimalPoint = decimal.find('.');
    bool isNegative = (decimal[0] == '-'); // 检查负号的状态

    // 确保输入字符串有效
    for (size_t i = (isNegative ? 1 : 0); i < decimal.size(); ++i) {
        if (!isdigit(decimal[i]) && decimal[i] != '.') {
            throw std::invalid_argument("无效的数值格式");
        }
    }

    std::string wholePart = decimal.substr(0, decimalPoint); // 整数部分
    std::string fractionalPart = (decimalPoint != std::string::npos) ? decimal.substr(decimalPoint + 1) : ""; // 小数部分

    // 计算分母
    mpq_class denominator = (fractionalPart.empty()) ? mpq_class(1) : mpq_class(1) * pow(10, fractionalPart.size());

    // 创建分子
    std::string numeratorString = wholePart + fractionalPart;
    mpq_class numerator = mpq_class(numeratorString);

    // 返回带符号的分数
    mpq_class finalResult = numerator / denominator;
    if (isNegative) {
        return -finalResult; // 处理负号
    }
    return finalResult;
}

// 计算表达式
mpq_class Calculator::calculate(const std::string &input) {
    std::string processedInput = std::regex_replace(input, std::regex("\\s+"), ""); // 移除多余空格

    std::istringstream stream(processedInput);
    std::stack<mpq_class> values; // 存储操作数
    std::stack<char> operators; // 存储操作符

    std::string token;
    while (stream >> token) {
        if (token.find('.') != std::string::npos || isdigit(token[0]) || token[0] == '-') {
            values.push(decimalToFraction(token)); // 处理分数或小数
        } else if (isOperator(token[0])) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                processOperator(values, operators); // 进行运算操作
            }
            operators.push(token[0]); // 保存操作符
        }
    }

    // 处理剩余的操作符
    while (!operators.empty()) {
        processOperator(values, operators);
    }

    // 确保栈中只有一个计算结果
    if (values.size() == 1) {
        return values.top();
    } else {
        throw std::invalid_argument("无法解析出结果");
    }
}

// 判断字符是否是操作符
bool Calculator::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 处理运算符
void Calculator::processOperator(std::stack<mpq_class> &values, std::stack<char> &operators) {
    if (values.size() < 2) throw std::invalid_argument("操作数不足，无法计算。");

    mpq_class right = values.top(); values.pop();
    mpq_class left = values.top(); values.pop();
    char operation = operators.top(); operators.pop();

    switch (operation) {
        case '+':
            values.push(left + right);
            break;
        case '-':
            values.push(left - right);
            break;
        case '*':
            values.push(left * right);
            break;
        case '/':
            if (right == 0) {
                throw std::invalid_argument("除数不能为零");
            }
            values.push(left / right);
            break;
    }
}


// 判断操作符优先级
int Calculator::precedence(char operation) {
    if (operation == '+' || operation == '-') return 1;
    if (operation == '*' || operation == '/') return 2;
    return 0; // 如果不是有效操作符，返回0
}
