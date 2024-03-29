#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
    int val;
    cin >> val;  // 读取用户输入
    char sign;
    if (val > 0) {
        sign = '+';
    } else if (val < 0) {
        sign = '-';
    } else {
        sign = '0';
    }
    cout << "Sign of " << val << " is " << sign << endl;
    return 0;
}
/*
* 输入：100
* 输出：Sign of 100 is +
*/