#pragma once
#include "fraction.h"

class Calculator {
public:
    mpq_class calculate(const std::string& input);
};