#pragma once
#include "fraction.h"
#include <sstream>
#include <stdexcept>
#include <gmpxx.h>
#include <cmath>
#include <stack>
#include <regex>

class Calculator {
public:
    mpq_class calculate(const std::string& input);

private:
    static int precedence(char operation);
    static bool isOperator(char c);
    static void processOperator(std::stack<mpq_class>& values, std::stack<char>& operators);
};