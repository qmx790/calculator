#include "fraction.h"

// 构造函数
Fraction::Fraction(const mpq_class& value) : fraction(value) {
    // 检查分母是否为零
    if (fraction.get_den() == 0) {
        throw std::invalid_argument("分母不能为零");
    }
}

mpq_class Fraction::simplify(const mpq_class &frac) const {
    mpq_class simplified = frac;
    simplified.canonicalize(); // 规范化分数
    return simplified;
}

// 将假分数转换为带分数形式
std::string Fraction::improperToProper() const {
    mpq_class simplified = fraction;
    simplified.canonicalize(); // 确保分数为最简分数
    mpq_class whole = simplified.get_num() / simplified.get_den(); // 整数部分
    mpq_class numerator = simplified.get_num() % simplified.get_den(); // 余数部分

    std::string wholeStr = whole.get_num().get_str();
    std::string numeratorStr = numerator.get_num().get_str();
    std::string denominatorStr = simplified.get_den().get_str();

    if (numerator == 0) {
        return wholeStr; // 没有余数，返回整数部分
    }
    return wholeStr + " and " + numeratorStr + "/" + denominatorStr; // 返回带分数
}


// 格式化输出带分数
std::string Fraction::toMixedFraction() const {
    return improperToProper();
}

// 设置分数的输出位数
void Fraction::setPrecision(int precision) {
    if (precision < 1 || precision > 50) {
        throw std::invalid_argument("分数位数必须在 1 到 50 之间");
    }
}

// 辅助函数：将 mpq_class 转换为字符串
std::string Fraction::mpqToString(const mpq_class& fraction) const {
    std::string numerator = fraction.get_num().get_str(); // 获取分子
    std::string denominator = fraction.get_den().get_str(); // 获取分母
    return numerator + "/" + denominator;
}

// 实现输入操作符
std::istream& operator>>(std::istream& in, Fraction& fraction) {
    std::string input;
    in >> input; // 从流读取为字符串
    fraction.fraction = mpq_class(input); // 将字符串转换成 mpq_class
    return in; // 返回流
}

// 实现输出操作符
std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
    // 使用 gmpxx 的 mpq_class 的输入输出格式
    out << fraction.fraction.get_num() << "/" << fraction.fraction.get_den(); // 输出分子和分母
    return out; // 返回流
}
