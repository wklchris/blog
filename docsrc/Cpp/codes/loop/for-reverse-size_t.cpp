#include <array>
#include <cstddef>
#include <iostream>

int main() {
    std::array<int, 3> arr {1, 2, 3};
    // 不能使用 for (size_t i = a.size()-1; i >= 0; --i)
    // 因为 size_t 是无符号的
    for (size_t i = arr.size(); i--; ) {
        std::cout << arr[i] << ' ';
    }
}