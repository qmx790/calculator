#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    std::string input;

    std::cout << "欢迎使用控制台计算器（支持分数和小数）" << std::endl;
    std::cout << "请输入表达式（例如：1/2 + 3/4）或输入\"exit\"以退出：" << std::endl;

    while (true) {
        std::cout << ">";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        try {
            mpq_class result = calc.calculate(input);
            Fraction frac(result);
            std::cout << "结果：" << frac.toMixedFraction() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "错误：" << e.what() << std::endl;
        }
    }
    return 0;
}