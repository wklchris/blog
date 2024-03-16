#include <iostream>
int main() {
    int s = 0;
    for (int k = 0; k < 4; ++k) {
        s += k;
    }
    std::cout << "Sum = " << s << std::endl;
    return 0;   
}