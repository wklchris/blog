#include <iostream>
#include <iomanip>  // 提供 std::setbase 等
#include <format>

int main() {
    // 数字 63 在各种不同进制下的字面值写法。这些变量相等。
    int dec = 63;
    int hex = 0x3F;
    int oct = 077;
    int binary = 0b111111;
    
    // 打印不同进制的数
    std::cout << "Dec: " << dec << "\n"
              << "Hex: " << hex << "\n"
              << "Oct: " << oct << "\n"
              << "Binary: " << binary << std::endl;

    // 将数字在打印时转为其他进制
    std::cout << "std::hex: " << std::showbase << std::hex << dec << std::endl;
    std::cout << "setbase(16): " << std::setbase(16) << dec << std::endl;
    // 恢复十进制打印
    std::cout << std::dec << std::noshowbase;

    // 使用 std::format
    std::cout << "std::format {:#x}: " << std::format("{:#x}", dec) << "\n"
              << "std::format {:x}: " << std::format("{:x}", dec) << std::endl;
}