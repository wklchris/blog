#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main() {
    int count_o = 0, count_firstword = 0;
    string s = "Hello world";
    for (char c: s) {
        if (c == 'o') {
            count_o += 1;
            count_firstword += 1;
            continue;
        } else if (c == ' ') {
            break;
        } else {
            count_firstword += 1;
        }
    }
    cout << "Count of 'o' = " << count_o << endl;
    cout << "Length of first word = " << count_firstword << endl;
    return 0;   
}
/*
  输出：
  Count of 'o' = 1
  Length of first word = 5
*/