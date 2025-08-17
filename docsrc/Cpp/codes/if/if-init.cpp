#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

int main() {
    std::array<int, 5> arr = {10, 20, 50, 20, 30};
    int target = 20;

    if (auto it = std::find(arr.begin(), arr.end(), target); it != arr.end()) {
        std::cout << "Target value " << *it << " found at index "
                  << std::distance(arr.begin(), it) << std::endl;
    } else {
        std::cout << "Target value " << target << " not found" << std::endl;
    }
}