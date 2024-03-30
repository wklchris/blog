#include <iostream>
#include <stdexcept>
using std::cout;
using std::cerr;
using std::endl;

int int_div(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Error: Division by zero.");
    }
    return numerator / denominator;
}

int main() {
    int x = 7, y = 0;
    int result = 0;
    try {
        result = int_div(x, y);
    } catch (std::runtime_error err) {
        cerr << err.what() << endl;
        cout << "result = N/A" << endl;
    }
    // 如果异常被成功捕获，那么以下内容会被正常执行
    cout << "~ A message after division." << endl;
    return 0;
}
/*
    输出：
    Error: Division by zero.
    result = N/A
    ~ A message after division.
*/