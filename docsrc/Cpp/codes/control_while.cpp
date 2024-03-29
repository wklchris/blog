#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
    int s = 0, k = 0;
    // 输入 Ctrl + Z 或 Ctrl + D 来标识输入流结束
    while (cin >> k) {
        s += k;
    }
    cout << "Sum = " << s << endl;
    return 0;   
}
/*
* 输入：1 3 7 5 9^D
* 输出：Sum = 25
*/