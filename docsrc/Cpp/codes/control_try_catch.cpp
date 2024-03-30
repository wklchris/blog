#include <iostream>
#include <string>
#include <stdexcept>
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main() {
    string s = "exp=2.718";
    double x = 0;
    try {
        x = std::stod(s);  // string 到 double 转换函数
    } catch (std::invalid_argument err) {
        cerr << "Invalid arg: " << err.what()
             << "(\"" << s <<"\")" << endl;
    }
    cout << "x = " << x << endl;
    return 0;
}
/*
    输出：
    Invalid arg: stod("exp=2.718")
    x = 0
*/