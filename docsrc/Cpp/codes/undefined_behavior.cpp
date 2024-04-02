#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main() {
    string s = "abc";
    cout << "s.size() = " << s.size() << endl;
    // 未定义行为，因为 s 的合法索引是从 0 到 2
    // 字符串 s 合法索引 i 应满足 0 <= i < s.size()
    cout << "s[3] = " << s[3] << endl;
    return 0;
}
/* （以上未定义行为在我测试时的）输出：
   s.size() = 3
   s[3] = 
*/