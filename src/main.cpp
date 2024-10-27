#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    std::string input;

    std::cout << "欢迎使用控制台计算器（支持分数和小数）" << std::endl;
    std::cout << "请输入表达式（例如：1/2 + 3/4）或输入\"exit\"以退出：" << std::endl;

    std::freopen("test.in", "r", stdin);
    std::freopen("test.out", "w", stdout);

    while (true) {
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
        try {
            if (!input.empty()) { // 检查输入是否为空
                mpq_class result = calc.calculate(input);
                std::cout << input << " = " <<"结果：" << result << std::endl;
            } else {
                std::cerr << "错误：输入不能为空。" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << input << " 错误：" << e.what() << std::endl;
        }
    }

    return 0;
}
