#include <iostream>

namespace Circle {
    constexpr double pi = 3.14159;
    void main(double r) {
        double area = pi * r * r;
        std::cout << "Area of circle of radius " << r << " = " << area;
    }
}

int main() {
    std::cout << "pi = " << Circle::pi << std::endl;
    
    double r = 2;
    Circle::main(r);
}