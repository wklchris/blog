#include <iostream>

// 全局变量 pi 与函数 circle_area
constexpr double pi = 3.14159;
constexpr double circle_area(double r) {
    // 函数内部的作用域。在内层作用域中可以使用外层变量 pi
    // 当前作用域内的变量 area
    double area = pi * r * r;
    return area;
}

int main() {
    // 另一个作用域内的变量 area
    int area = 1;
    std::cout << "main() scope: area = " << area << std::endl;
    {
        // 一个简单的花括号作用域
        double area = 1.23;
        std::cout << "inner scope : area = " << area << std::endl;
    }
}
