#include <iostream>
#include <string>

int main() {
    std::string s = "Hello";
    // 传统 for 循环（使用下标作为循环变量）
    for (size_t i = 0; i < s.length(); ++i) {
        std::cout << s[i] << " ";
    }
    std::cout << "\n";
    // 传统 for 循环（使用迭代器）
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    // 范围 for 循环
    for (auto c : s) {
        std::cout << c << " ";
    }
}