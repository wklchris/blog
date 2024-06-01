#include <iostream>
#include <memory>

class DataClass {
private:
    int n;
    double x;
    double result;
public:
    DataClass(int n, double x): n(n), x(x) { result = x * n; };
    double getResult() { return result; };
};

int main() {
    std::unique_ptr<int> up1 = std::make_unique<int>(12);
    // 使用 auto 简化书写
    auto up2 = std::make_unique<int>(79);
    // 交换两个指针的值
    up2.swap(up1);
    std::cout << "up1: " << *up1 << ", up2: " << *up2 << std::endl;
    // 传入符合 DataClass 构造函数的参数
    auto up3 = std::make_unique<DataClass>(2, 3.14);
    std::cout << "Result: " << up3->getResult() << std::endl;
}
/*
  输出：
  up1: 79, up2: 12
  Result: 6.28
*/