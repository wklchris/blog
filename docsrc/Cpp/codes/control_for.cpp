#include <iostream>
using std::cout;
using std::endl;

int main() {
    int s = 0;
    for (int k = 0; k < 4; ++k) {
        s += k;
    }
    cout << "Sum = " << s << endl;
    return 0;   
}
/*
* 输出：6
*/