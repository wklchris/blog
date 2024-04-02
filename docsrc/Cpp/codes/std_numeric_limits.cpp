#include <iostream>
#include <limits>
using std::cout;
using std::endl;

int main() {
    cout << "Following results can be environment-dependent:" << endl;
    // 输出使用无符号类型的位数，因为带符号类型的值位数要少一位（符号位）
    cout << "int (" << std::numeric_limits<unsigned>::digits << " bits):\t\t"
         << std::numeric_limits<int>::lowest() << ", "
         << std::numeric_limits<int>::max() << endl;
    cout << "short (" << std::numeric_limits<unsigned short>::digits << " bits):\t"
         << std::numeric_limits<short>::lowest() << ", "
         << std::numeric_limits<short>::max() << endl;
    cout << "long long (" << std::numeric_limits<unsigned long long>::digits << " bits):\t"
         << std::numeric_limits<long long>::lowest() << ", "
         << std::numeric_limits<long long>::max() << endl;
    return 0;
}
/*
    输出：
    Following results can be environment-dependent:
    int (32 bits):          -2147483648, 2147483647
    short (16 bits):        -32768, 32767
    long long (64 bits):    -9223372036854775808, 9223372036854775807
*/