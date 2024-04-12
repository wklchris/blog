#include <iostream>
#include <string>
#include <windows.h>
using std::cout;
using std::endl;

int main() {
    SetConsoleOutputCP(CP_UTF8);  // 用于 Windows
    
    // 使用 Unicode 码
    std::string greek_alpha = "\u03B1";   // U+03B1
    cout << "Alpha: " << greek_alpha << endl;

    std::string mathcal_A = "Letter \U0001d49c"; // U+1D49C
    cout << "Mathcal A: " << mathcal_A << endl;

    std::string meow = "\u15E2\u1561\u14D7";
    cout << "Meow (string): " << meow << endl;
    if (meow.size() > 3) {
        cout << "* unexpected size: " << meow.size() << endl;
    }
    return 0;
}
/*
  输出：
  Alpha: α
  Mathcal A: 𝒜
  Meow (String): ᗢᕡᓗ
  * unexpected size: 9
*/