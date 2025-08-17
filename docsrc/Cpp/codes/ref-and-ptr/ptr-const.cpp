#include <iostream>

int main() {
    int m = 14;
    const int n = 23;

    // 定义一个自身为常量（顶层常量）的指针 p1，指向整数 m
    int *const p1 = &m;

    ++(*p1);  // 更改所指对象的值
    std::cout << "*p1 = " << *p1 << std::endl;

    // 定义一个指向“常量”（底层常量）的指针 p2，指向整数常量 n
    const int* p2 = &n;
    std::cout << "*p2 = " << *p2 << " (Initial)" << std::endl;

    p2 = &m;  // 更改指针的指向（允许指向一个实际不是常量的对象）
    ++m;      // 更改所指对象的值（不能通过 *p2 更改）
    std::cout << "*p2 = " << *p2 << std::endl;

    // 定义一个自身是常量、也指向“常量”的指针 p3
    const int* const p3 = &m;
}