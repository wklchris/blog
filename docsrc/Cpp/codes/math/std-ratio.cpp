#include <iostream>
#include <ratio>

int main() {
    using Half = std::ratio<1, 2>;
    std::cout << "Half: " << Half::num << "/" << Half::den << std::endl;
    
    using ThreeThousandth = std::ratio<3, std::kilo::num>;
    using Result = std::ratio_add<Half, ThreeThousandth>;
    std::cout << "Result: " << Result::num << "/" << Result::den 
              << " = " << (Result::num * 1.0 / Result::den) << std::endl;
}