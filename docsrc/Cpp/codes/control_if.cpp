#include <iostream>
int main() {
    /*
    * 输入：100
    * 输出：Sign of 100 is +
    */
    int val;
    std::cin >> val;  // 读取用户输入
    char sign;
    if (val > 0) {
        sign = '+';
    } else if (val < 0) {
        sign = '-';
    } else {
        sign = '0';
    }
    std::cout << "Sign of " << val << " is " << sign << std::endl;
    return 0;
}