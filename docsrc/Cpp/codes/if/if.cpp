#include <iostream>
#include <string>
#include <vector>

int main() {
    int x = 1;
    if (x > 0) {
        std::cout << "x is positive." << std::endl;
    }

    std::vector<int> v {1, 2, 3};
    if (v.empty()) {
        std::cout << "v is empty." << std::endl;
    } else {
        std::cout << "v is not empty. It has " << v.size()
                  << " elements." << std::endl;
    }

    std::string s = "Hello";
    if (s.length() > 5) {
        std::cout << "s is longer than 5 characters." << std::endl;
    } else if (s.length() < 5){
        std::cout << "s is shorter than 5 characters." << std::endl;
    } else {
        std::cout << "s has exact 5 characters." << std::endl;
    }
}