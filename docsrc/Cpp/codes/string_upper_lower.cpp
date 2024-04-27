#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::string str = "Hello World!";

    for (size_t i = 0; i < str.size(); ++i) {
        str[i] = std::toupper(str[i]);
    }
    std::cout << "All uppercase: " << str << std::endl;
    
    // 也可以使用 range for 语法
    for (auto &c : str) { c = std::tolower(c); }
    std::cout << "All lowercase: " << str << std::endl;
    return 0;
}
/*
  输出：
  All uppercase: HELLO WORLD!
  All lowercase: hello world!
*/
