#include <iostream>

int main() {
    int x = -4;
    int x_abs = x > 0 ? x : -x;
    std::cout << "When x = " << x << ", abs(x) = "
              << x_abs << std::endl;
}