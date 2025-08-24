#include <iostream>
#include <cctype>  // 提供 std::toupper
#include <string>

std::string uppercase_str(std::string s) {
    for (char& c : s) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return s;  
}

int main() {
    std::string s = "hello world";
    std::cout << uppercase_str(s) << std::endl;
}