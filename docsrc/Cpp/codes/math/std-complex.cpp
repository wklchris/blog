#include <complex>
#include <cstdlib>  // 提供 std::abs
#include <iostream>

void print_complex(std::complex<double> z) {
    // 用 std::abs 求复数的模
    std::cout << "Complex number (" << z.real() << " + " << z.imag() << "i) "
              << "has norm: " << std::abs(z) << std::endl;
}

int main() {
    std::complex<double> z1 {3.0, 4.0};  // 3 + 4i
    print_complex(z1);
    
    // 引入命名空间来支持 i 虚数后缀
    using namespace std::complex_literals;
    std::complex<double> z2 = 2.0 + 8i;
    print_complex(z1 + z2);
}