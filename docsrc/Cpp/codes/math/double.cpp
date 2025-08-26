#include <iostream>
#include <numbers>  // 提供 pi 值
#include <iomanip>  // 提供 std::setprecision
#include <limits>   // 提供 std::numeric_limits
#include <format>   // 提供 std::format

int main() {
    std::cout << "PI = " << std::numbers::pi << std::endl;
    // 打印 2 位小数
    std::cout << std::fixed << std::setprecision(2) << "PI = " << std::numbers::pi << std::endl;
    // 打印全精度的有效数字
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10)
              << "PI = " << std::numbers::pi << std::endl;
    // std::format 会自动使用高精度
    std::cout << std::format("0.1 + 0.2 = {}", 0.1 + 0.2) << std::endl;
}