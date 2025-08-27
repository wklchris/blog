#include <iostream>

int main() {
    int n = 2;
    while(n > 0) {
        std::cout << "n = " << n << "\n";
        --n;
    }
    std::cout << "Ending: n = " << n << std::endl;
    
    int m = 0;
    do {
        std::cout << "m = " << m << "\n";
        ++m;
    } while (n < 0);
    std::cout << "Ending: m = " << m << std::endl;
}