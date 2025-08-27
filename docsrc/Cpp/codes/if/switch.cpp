#include <iostream>

int main() {
    int day = 3;
    std::cout << "Day of the week:\n";
    switch (day) {
        case 6:
        case 7:
            std::cout << "Rest at weekends.\n";
            break;
        case 1:
        case 2:
        case 3:
            std::cout << "Meeting Mon-Fri morning\n";
            // 没有break，继续执行到下一个case
        case 4:
        case 5:
            std::cout << "Coding Thu & Fri afternoon\n";
            break;
        default:
            std::cout << "Invalid day of the week";
    }
}