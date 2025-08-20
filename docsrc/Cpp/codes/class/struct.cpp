#include <iostream>

struct Point {
    double x;
    double y;
};

int main() {
    Point p {1, 2.3};
    std::cout << "p.x = " << p.x << '\n'
              << "p.y = " << p.y << std::endl;
    
    // 指针与 -> 符访问
    Point* ptr = &p;
    std::cout << "ptr->x = " << ptr->x << std::endl;
}