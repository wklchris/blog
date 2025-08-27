#include<iostream>
#include <vector>

int main() {
    std::vector<int> v {1, 3, 4, 5};
    for (int x : v) {
        if (x % 2 == 1) {
            std::cout << x << " = 2 * " << x / 2 << " + 1" << std::endl;
            continue;
        }
        std::cout << x << " is not odd" << std::endl;
        break;
    }
}