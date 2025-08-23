// PointModule.cpp 模块文件
export module PointModule;
import std;

export class Point {
private:
    double px;
    double py;

public:
    Point(double x = 0.0, double y = 0.0) : px(x), py(y) {}

    double x() const { return px; }
    double y() const { return py; }

    void xshift(double dx) { px += dx; }
    void yshift(double dy) { py += dy; }

    Point& operator+=(const Point& other) {
        px += other.px;
        py += other.py;
        return *this;
    }

    Point& operator*=(double scalar) {
        px *= scalar;
        py *= scalar;
        return *this;
    }
};

export Point operator+(Point lhs, const Point& rhs) {
    lhs += rhs;
    return lhs;
}

export Point operator*(Point point, double scalar) {
    point *= scalar;
    return point;
}

export Point operator*(double scalar, Point point) {
    return point * scalar;
}

export std::ostream& operator<<(std::ostream& os, const Point& point) {
    return os << "(" << point.x() << "," << point.y() << ")";
}