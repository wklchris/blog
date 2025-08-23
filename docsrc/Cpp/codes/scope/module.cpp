// module.cpp 主文件
import std;
import PointModule;

int main() {
    Point p {1, 2};
    std::cout << "Point = " << p << std::endl;

    p.xshift(2);
    p.yshift(-1);
    std::cout << "Point after shifting = " << p << std::endl;

    p *= 2;
    std::cout << "Point after scaling = " << p << std::endl;
}