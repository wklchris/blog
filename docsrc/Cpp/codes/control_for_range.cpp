#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main() {
    vector<int> vec = {1, 3, 5, 7};
    int s = 0;
    for (int k: vec) {  // 遍历向量 vec 的每个元素
        s += k;
    }
    cout << "Sum = " << s << endl;
    return 0;
}
/*
* 输出：16
*/