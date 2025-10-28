#include <iostream>
#include <cassert>
#include <cmath>
#include "../src/calculator.h"

// 简单的测试框架
int test_count = 0;
int passed_count = 0;

void test_assert(bool condition, const char* test_name) {
    test_count++;
    if (condition) {
        passed_count++;
        std::cout << "✓ PASS: " << test_name << std::endl;
    } else {
        std::cout << "✗ FAIL: " << test_name << std::endl;
    }
}

void test_add() {
    Calculator calc;
    test_assert(calc.add(2, 3) == 5, "加法: 2 + 3 = 5");
    test_assert(calc.add(-1, 1) == 0, "加法: -1 + 1 = 0");
    test_assert(calc.add(0, 0) == 0, "加法: 0 + 0 = 0");
    test_assert(std::abs(calc.add(0.1, 0.2) - 0.3) < 0.0001, "加法: 0.1 + 0.2 ≈ 0.3");
}

void test_subtract() {
    Calculator calc;
    test_assert(calc.subtract(5, 3) == 2, "减法: 5 - 3 = 2");
    test_assert(calc.subtract(0, 5) == -5, "减法: 0 - 5 = -5");
    test_assert(calc.subtract(10, 10) == 0, "减法: 10 - 10 = 0");
}

void test_multiply() {
    Calculator calc;
    test_assert(calc.multiply(3, 4) == 12, "乘法: 3 * 4 = 12");
    test_assert(calc.multiply(-2, 5) == -10, "乘法: -2 * 5 = -10");
    test_assert(calc.multiply(0, 100) == 0, "乘法: 0 * 100 = 0");
}

void test_divide() {
    Calculator calc;
    test_assert(calc.divide(10, 2) == 5, "除法: 10 / 2 = 5");
    test_assert(calc.divide(7, 2) == 3.5, "除法: 7 / 2 = 3.5");
    test_assert(calc.divide(-10, 2) == -5, "除法: -10 / 2 = -5");
    
    // 测试除以零异常
    bool exception_caught = false;
    try {
        calc.divide(10, 0);
    } catch (const std::invalid_argument&) {
        exception_caught = true;
    }
    test_assert(exception_caught, "除法: 除以零应抛出异常");
}

void test_square() {
    Calculator calc;
    test_assert(calc.square(4) == 16, "平方: 4^2 = 16");
    test_assert(calc.square(-3) == 9, "平方: (-3)^2 = 9");
    test_assert(calc.square(0) == 0, "平方: 0^2 = 0");
}

int main() {
    std::cout << "=== 运行计算器单元测试 ===" << std::endl;
    std::cout << std::endl;
    
    test_add();
    test_subtract();
    test_multiply();
    test_divide();
    //test_square();
    
    std::cout << std::en8dl;
    std::cout << "测试结果: " << passed_count << "/" << test_count << " 通过" << std::endl;
    
    if (passed_count == test_count) {
        std::cout << "🎉 所有测试通过！" << std::endl;
        return 0;
    } else {
        std::cout << "❌ 有测试失败！" << std::endl;
        return 1;
    }
}
