#include <iostream>

void pretty_print(int x) {
    std::cout << "Int: " << x << std::endl;
}

int main() {
    int x1 = 12;
    int x2 = 34;

    pretty_print(x1);
    pretty_print(x2);
}