#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v {0, 1, -2, -3, 4, -5};

    // 计算负数的数量
    int count = std::count_if(v.begin(), v.end(), [](int n){ return n < 0;});
    std::cout << "Count of negative numbers: " << count << std::endl;

    // 计算负数之和，需要捕获 sum 变量
    int sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int n){
        if (n < 0) sum += n;
    });
    std::cout << "Sum of negative numbers: " << sum << std::endl;
}