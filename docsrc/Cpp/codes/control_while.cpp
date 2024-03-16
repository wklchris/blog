#include <iostream>
int main() {
    int s = 0, k = 0;
    while (k < 4) {
        s += k;
        ++k;
    }
    std::cout << "Sum = " << s << std::endl;
    return 0;   
}