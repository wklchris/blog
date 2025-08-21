#include <iostream>
#include <cmath>    // 提供 sqrt
#include <variant>
#include <vector>

struct Triangle { double a, b, c; };
struct Rectangle { double a, b; };
struct Circle { double r; };

using Shape = std::variant<Triangle, Rectangle, Circle>;

// 固定的 overloaded 模板类的定义
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// 使用 std::visit 来访问每一种变体类型
double calcShapeArea(const Shape& shape) {
    return std::visit(overloaded{
        [](const Triangle& s) { 
            double p = (s.a + s.b + s.c) / 2;
            return sqrt(p * (p - s.a) * (p - s.b) * (p - s.c));
        },
        [](const Rectangle& s) { return s.a * s.b; },
        [](const Circle& s) { return 3.1415926 * s.r * s.r; }
    }, shape);
}

int main() {
    std::vector<Shape> shapes {
        Circle{1},
        Triangle{3, 4, 5},
        Rectangle{2, 3}
    };

    for (const auto s : shapes) {
        // 使用 std::holds_alternative 来检查变体类型，
        // 并用 std::get 来获取数据。这种写法较繁琐。
        std::cout << "Area of ";
        if (std::holds_alternative<Triangle>(s)) {
            auto triangle = std::get<Triangle>(s);
            std::cout << "triangle (" << triangle.a << ","
                      << triangle.b << "," << triangle.c << ") = ";
        } else if (std::holds_alternative<Rectangle>(s)) {
            auto rect = std::get<Rectangle>(s);
            std::cout << "rectangle (" << rect.a << "," << rect.b << ") = ";
        } else if (std::holds_alternative<Circle>(s)) {
            auto circle = std::get<Circle>(s);
            std::cout << "circle (" << circle.r << ") = ";
        }
        std::cout << calcShapeArea(s) << "\n";
    }
}