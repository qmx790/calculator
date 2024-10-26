#ifndef FRACTION_H
#define FRACTION_H

#include "gmpxx.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>

class Fraction {
public:
    // 构造函数
    Fraction(const mpq_class& value);

    // 将假分数转换为带分数形式
    std::string improperToProper() const;

    // 格式化输出带分数
    std::string toMixedFraction() const;

    // 设置分数的输出位数
    void setPrecision(int precision);

    // 简化分数
    mpq_class simplify(const mpq_class& frac) const;

    // 重载输入操作符
    friend std::istream& operator>>(std::istream& in, Fraction& fraction);
    // 重载输出操作符
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);

private:
    mpq_class fraction; // 使用 GMP 提供的有理数类型
    std::string mpqToString(const mpq_class& fraction) const; // 辅助函数，使用常量引用
};

#endif // FRACTION_H
