#include <iostream>

int main() {
    int x = 5;
    int y = 3;
    
    int result_int = x / y;
    std::cout << "Int = " << result_int << std::endl;

    double result_double = static_cast<double>(x) / y;
    std::cout << "Double / Int = " << result_double << std::endl;

    double y_double = 3.0;
    std::cout << "Int / Double = " << (x / y_double) << std::endl;
}