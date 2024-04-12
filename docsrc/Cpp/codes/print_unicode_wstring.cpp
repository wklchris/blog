#include <iostream>
#include <string>
#include <windows.h>
using std::cout;
using std::endl;

void print_wstring(std::wstring &ws, HANDLE &handle);

int main() {
    SetConsoleOutputCP(CP_UTF8);  // 用于 Windows

    std::wstring greek_abc = L"\u03B1\u03B2\u03B3";
    cout << "wstring size: " << greek_abc.size() << endl;

    // 一种 hack 式的 wstring 打印方式
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    print_wstring(greek_abc, handle);
    return 0;
}
/* 输出：
   wstring size: 3
   αβγ
*/

void print_wstring(std::wstring &ws, HANDLE &handle) {
    DWORD c;
    if (!WriteConsoleW(handle, ws.c_str(), ws.size(), &c, nullptr)) {
        std::cerr << "Error in wstring writing" << endl;
    }
}