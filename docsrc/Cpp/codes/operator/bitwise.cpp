#include <iostream>

int main() {
    short x = 9;  // 1001
    short y = 5;  // 0101
    std::cout << "x = " << x << ", y = " << y << std::endl;

    int result_and = x & y;  // 0..0001 -> 1
    std::cout << "Bitwise AND: x & y = " << result_and << std::endl;

    int result_or = x | y;  // 0..1101 -> 13
    std::cout << "Bitwise OR : x | y = " << result_or << std::endl;

    int result_xor = x ^ y;  // 0..1100 -> 12
    std::cout << "Bitwise XOR: x ^ y = " << result_xor << std::endl;

    int result_not = ~x;  // 1...0110 表负数, -(1001 + 1) -> -10
    std::cout << "Bitwise NOT: ~x = " << result_not << std::endl;

    int result_lshift = x << 1;  // 0..10010 -> 18
    std::cout << "Left-shift : x << 1 = " << result_lshift << std::endl;

    int result_rshift = x >> 2;  // 0..10 -> 2
    std::cout << "Right-shift: x >> 2 = " << result_rshift << std::endl;
}