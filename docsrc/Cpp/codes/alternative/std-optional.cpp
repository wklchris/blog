#include <iostream>
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

std::optional<std::string> findByInitial(const std::vector<std::string>& v, char c) {
    auto it = std::find_if(v.begin(), v.end(), [c](const std::string s){
        if (!s.empty() && s[0] == c) { return true; }
        return false; 
    });
    if (it != v.end()) { return *it; }
    return std::nullopt;  // 或者直接使用 return {};
}

void printFinding(const std::vector<std::string>& v, char c) {
    std::optional<std::string> fruit = findByInitial(v, c);
    std::cout << "Fruit with initial letter '" << c << "' is ";
    if (fruit.has_value()) {   // 或者直接使用 if (fruit)
        std::cout << "found: " << *fruit << std::endl;
    } else {
        std::cout << "NOT found" << std::endl;
    }
}

int main() {
    std::vector<std::string> data = { "apple", "orange", "peach" };
    printFinding(data, 'a');
    printFinding(data, 'c');

    auto fruit = findByInitial(data, 'p');
    if (fruit) {
        std::cout << "Found fruit: " << *fruit;
    }
}