#include <iostream>
#include <string>
using std::cout;
using std::endl;

int main() {
    double x = 1.23;
    double *p = &x;
    cout << "*p = " << *p
         << "\np = " << p << endl;

    *p = 0.3;
    cout << "\n*p = " << *p
         << "\nx = " << x << endl;
    return 0;
}
/*
  输出（p 的地址每次运行都会不同）：
  *p = 1.23
  p = 0xac89bffc70

  *p = 0.3
  x = 0.3
*/