#include <iostream>

int main() {
    int x = 3;
    // 常量引用可以被绑定到变量
    const int &rx = x;
    std::cout << "const &rx = " << rx << std::endl;
    
    // 当变量被修改时，通过引用获取的值也随之变化
    x += 1;
    std::cout << "x = " << rx << std::endl;
    std::cout << "const &rx = " << rx << std::endl;

    // 常量引用当然可以绑定到常量，
    const int y1 = 123;
    constexpr int y2 = 456;

    const int &ry1 = y1;
    const int &ry2 = y2;
    
    // 还可以绑定到字面量
    const int &rz = 12345;
}