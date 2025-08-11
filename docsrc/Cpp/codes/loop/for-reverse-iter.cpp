#include <array>
#include <iostream>

int main() {
    std::array<int, 3> arr {1, 2, 3};

    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        std::cout << *it << ' ';
    }
}