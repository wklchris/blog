#include <iostream>

constexpr double pi = 3.14159265;
constexpr double circle_area(double radius) {
    return pi * radius * radius;
}

int main() {
    constexpr double r1 = 1.0;
    // 在编译时调用 circle_area 函数
    constexpr double area1 = circle_area(r1);
    std::cout << "Area 1 = " << area1 << std::endl;

    double r2 = 2 * r1;
    // 在运行时调用 circle_area 函数
    double area2 = circle_area(r2);
    std::cout << "Area 2 = " << area2 << std::endl;
}