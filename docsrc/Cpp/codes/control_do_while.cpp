#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
    int s = 0, k = 0;
    do {
        s += k;
    } while (cin >> k);  // 请勿忘记这个分号
    cout << "Sum = " << s << endl;
    return 0;   
}
/*
* 输入：1 4 7 2^D
* 输出：Sum = 14
*/