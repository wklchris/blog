#include <iostream>

void myfunc(int& x, double y) {
    // 参数 x 以传引用的形式传入，修改 x 会反映在它引用的对象上
    // 参数 y 以传值的方式传入，它的值不会影响实际的外部对象
    x = -1;
    y = 1.4;
}

int main() {
    int a = 1234;
    double b = 5.6;
    
    myfunc(a, b);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}