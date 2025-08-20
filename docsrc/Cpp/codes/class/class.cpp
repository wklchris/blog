#include <iostream>
#include <cmath>

class Point {
public:
    // 定义类的构造函数
    Point(double px, double py): x(px), y(py) {}
    // 定义其他公有成员函数
    double getX() { return x; }
    double getY() { return y; }
    double length() { return sqrt(x * x + y * y); }

private:
    // 将数据成员设为私有，阻止从外部直接修改
    double x;
    double y;
};

int main() {
    Point p {1, 1};
    // 注意：不能直接用 p.x 或 p.y 访问私有成员
    std::cout << "p = (" << p.getX() << ", " << p.getY() << ")\n"
              << "length = " << p.length() << std::endl;
}