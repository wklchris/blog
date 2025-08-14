#include <iostream>

int main() {
    int i = 0;
    std::cout << "i = " << i << std::endl;

    int a = ++i;  // i 先递增，后被赋值给 a
    std::cout << "a = " << a << std::endl;
    std::cout << "i = " << i << std::endl;

    int b = i++;  // i 先被赋值给 a，后递增
    std::cout << "b = " << b << std::endl;
    std::cout << "i = " << i << std::endl;
}