#include <iostream>

class Point {
public:
    // constexpr 构造函数
    constexpr Point(double x_, double y_)
        : x(x_), y(y_) {}
    // constexpr 常量成员函数
    constexpr double sum() const { return x + y; }
    // 常量成员函数（本例中 cout << 输出操作不能声明为 constexpr）
    void print() const {
        std::cout << "Point (" << x << ", " << y << "): sum = "
                  << sum() << std::endl;
    }
    // 普通成员函数
    void reset() { x = 0.0; y = 0.0; }

private:
    double x;
    double y;
};

int main() {
    Point p1 { 1.0, 2.0 };
    const Point p2 { 3.0, 4.0 };
    constexpr Point p3 { 5.0, 0.0 };

    // p1 可以定义为普通变量或 const 
    double p1_s = p1.sum();
    // p2 不是常量表达式，因此 p2_length 不能定义成 constexpr
    const double p2_s = p2.sum();
    // p3 可以被定义为普通、const 或者 constexpr
    constexpr double p3_s = p3.sum();

    p1.print();
    p2.print();
    p3.print();
    
    // p2 与 p3 是 const/constexpr 对象，不能调用非 const 成员函数
    p1.reset();
}