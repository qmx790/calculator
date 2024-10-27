#include "calculator.h"

// 判断操作符优先级
int Calculator::precedence(char operation) {
    if (operation == '+' || operation == '-') {
        return 1;
    }
    if (operation == '*' || operation == '/') {
        return 2;
    }
    return 0; // 如果不是有效操作符，返回 0
}

// 判断字符是否是操作符
bool Calculator::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 处理运算符
void Calculator::processOperator(std::stack<mpq_class> &values, std::stack<char> &operators) {
    mpq_class right = values.top(); values.pop();
    mpq_class left = values.top(); values.pop();
    char operation = operators.top(); operators.pop();

    switch (operation) {
        case '+':
            values.emplace(left + right);
            break;
        case '-':
            values.emplace(left - right);
            break;
        case '*':
            values.emplace(left * right);
            break;
        case '/':
            if (right == 0) {
                throw std::invalid_argument("除数不能为零");
            }
            values.emplace(left / right);
            break;
    }
}

// 将小数转换为分数的功能
mpq_class decimalToFraction(const std::string &decimal) {
    size_t decimalPoint = decimal.find('.');
    if (decimalPoint == std::string::npos) {
        return mpq_class(decimal); // 如果没有小数点，直接返回 mpq_class
    }

    // 整数部分
    std::string wholePart = decimal.substr(0, decimalPoint); // 整数部分
    // 小数部分
    std::string fractionalPart = decimal.substr(decimalPoint + 1); // 小数部分

    // 计算分母
    mpq_class denominator = mpq_class(1) * pow(10, fractionalPart.size());
    // 组装分子
    std::string numeratorString = wholePart + fractionalPart; // 整数和小数部分合并
    mpq_class numerator = mpq_class(numeratorString);

    return numerator / denominator; // 返回分数形式
}

// 计算表达式
mpq_class Calculator::calculate(const std::string &input) {
    // 移除空格并格式化操作符
    std::string processedInput = std::regex_replace(input, std::regex("\\s+"), ""); // 移除所有空格
    processedInput = std::regex_replace(processedInput, std::regex("([+\\-*/])"), " $1 "); // 添加空格于操作符前后

    std::istringstream stream(processedInput);
    std::stack<mpq_class> values; // 存储操作数
    std::stack<char> operators;    // 存储操作符

    std::string token;
    while (stream >> token) {
        // 处理小数和分数
        if (token.find('.') != std::string::npos || isdigit(token[0])) {
            // 尝试解析为 mpq_class
            values.push(decimalToFraction(token));
        } else if (isOperator(token[0])) {
            // 处理当前操作符
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                processOperator(values, operators);
            }
            operators.push(token[0]);
        }
    }

    // 处理剩余的操作符
    while (!operators.empty()) {
        processOperator(values, operators);
    }

    // 返回结果
    if (values.size() == 1) {
        return values.top();
    } else {
        throw std::invalid_argument("错误的数学表达式，未能解析出单一结果.");
    }
}
