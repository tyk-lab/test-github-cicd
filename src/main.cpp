#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    
    std::cout << "=== C++ 计算器演示程序 ===" << std::endl;
    std::cout << std::endl;
    
    // 演示各种运算
    double a = 10.0;
    double b = 5.0;
    
    std::cout << "操作数: a = " << a << ", b = " << b << std::endl;
    std::cout << std::endl;
    
    std::cout << "加法: " << a << " + " << b << " = " << calc.add(a, b) << std::endl;
    std::cout << "减法: " << a << " - " << b << " = " << calc.subtract(a, b) << std::endl;
    std::cout << "乘法: " << a << " * " << b << " = " << calc.multiply(a, b) << std::endl;
    std::cout << "除法: " << a << " / " << b << " = " << calc.divide(a, b) << std::endl;
    std::cout << "平方: " << a << " ^ 2 = " << calc.square(a) << std::endl;
    
    std::cout << std::endl;
    
    // 演示异常处理
    std::cout << "测试异常处理 (除以零):" << std::endl;
    try {
        calc.divide(a, 0);
    } catch (const std::invalid_argument& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "程序运行完成！" << std::endl;
    
    return 0;
}
