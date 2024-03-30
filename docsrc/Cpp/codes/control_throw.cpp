#include <iostream>
#include <stdexcept>
using std::cout;
using std::cerr;
using std::endl;

int main() {
    int x = 7, y = 0;
    int result = 0;
    if (y == 0) {
        throw std::runtime_error("Division by zero.");
    }
    // 如果抛出了异常，以下内容将不会被执行
    cout << "x // y = " << x / y << endl;
    return 0;
}
/*
    输出：
    terminate called after throwing an instance of 'std::runtime_error'
      what():  Division by zero.
*/