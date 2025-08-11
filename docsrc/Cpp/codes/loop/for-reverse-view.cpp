#include <array>
#include <iostream>
#include <ranges>

int main() {
    std::array<int, 3> arr {1, 2, 3};

    for (int x : arr | std::views::reverse) {
        std::cout << x << ' ';
    }
}