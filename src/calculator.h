#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * @brief 简单的计算器类
 * 
 * 提供基本的数学运算功能，用于演示C++项目和CI/CD流程
 */
class Calculator {
public:
    /**
     * @brief 加法运算
     * @param a 第一个操作数
     * @param b 第二个操作数
     * @return 两数之和
     */
    double add(double a, double b);
    
    /**
     * @brief 减法运算
     * @param a 被减数
     * @param b 减数
     * @return 差值
     */
    double subtract(double a, double b);
    
    /**
     * @brief 乘法运算
     * @param a 第一个乘数
     * @param b 第二个乘数
     * @return 乘积
     */
    double multiply(double a, double b);
    
    /**
     * @brief 除法运算
     * @param a 被除数
     * @param b 除数
     * @return 商
     * @throw std::invalid_argument 当除数为0时抛出异常
     */
    double divide(double a, double b);
    
    /**
     * @brief 计算平方
     * @param a 底数
     * @return 平方值
     */
    double square(double a);
};

#endif // CALCULATOR_H
