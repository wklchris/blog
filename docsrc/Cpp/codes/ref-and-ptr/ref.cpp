#include <iostream>

int main() {
    char x = 'A';
    char &r = x;  // 定义一个名为 r 的引用
    std::cout << "x (&r) = " << r << std::endl;
    
    // 可以通过引用来更改被引用对象的值
    r = 'B';
    std::cout << "x = " << r << std::endl;

    // 更改原对象的值会反映在引用的使用中
    x = 'Z';
    std::cout << "x (&r) = " << r << std::endl;
}