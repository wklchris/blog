#include <iostream>
#include <string>
#include <ranges>

int main() {
    std::string s = "World";
    for (auto&& [index, value] : s | std::views::enumerate) {
        std::cout << "s[" << index << "] = " << value << std::endl;
    }
}