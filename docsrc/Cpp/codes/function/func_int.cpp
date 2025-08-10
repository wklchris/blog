#include <iostream>

int square_area(int square_size) {
    return square_size * square_size;
}

int main() {
    int x = 3;
    int area = square_area(x);
    std::cout << "Area = " << area << std::endl;
}