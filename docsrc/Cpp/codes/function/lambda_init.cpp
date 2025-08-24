#include <iostream>
#include <string>
#include <map>

int main() {
    const std::string s = "Hello cpp";
    // 使用捕获列表，统计字符串 s 中非空格字符的出现次数
    const std::map<char, int> char_counts = [&s](){
        std::map<char, int> counts;
        for (char c : s) {
            if (c != ' ') {
                counts[c]++;
            }
        }
        return counts;
    }();  // 通过 () 立刻调用该匿名函数
    
    for (const auto& [character, count] : char_counts) {
        std::cout << character << ": " << count << std::endl;
    }
}