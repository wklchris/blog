#include <iostream>

int main() {
    double x = 1.23;
    double y = 7.89;
    
    // 定义一个 double 类型的指针 p，它指向变量 x 的地址
    double *p = &x;
    double *q = nullptr;   // 空指针

    std::cout << "*p = " << *p
              << ", p = " << p << std::endl;
    
    // 通过指针更改它指向的变量
    *p = 4.56;
    std::cout << "*p = " << *p
              << ", x = " << x << std::endl;
    
    // 让指针指向另一个变量
    p = &y;
    std::cout << "*p = " << *p << std::endl;
}