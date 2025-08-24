#include <iostream>
#include <string>

class CountChar {
public:
    CountChar(char c): value(c) {}
    size_t operator()(const std::string s) const {
        size_t count = 0;
        for (const char c : s) {
            if(c == value) { ++count; }
        }
        return count;
    }

private:
    char value;
};

int main() {
    std::string s = "Hello world!";

    CountChar count_l {'l'};
    std::cout << "Count of 'l': " << count_l(s) << std::endl;

    CountChar count_a {'a'};
    std::cout << "Count of 'a': " << count_a(s) << std::endl;
}