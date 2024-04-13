#include <iostream>
#include <string>
using std::cout;
using std::endl;

int main() {
    int n = 10;

    int *p = nullptr;
    if (!p) { cout << "p: false" << endl; }

    int *p1 = &n, *p2 = p1;
    if (p1 == p2) { cout << "p1 == p2" << endl; }
    int *q = nullptr;
    if (p == q) { cout << "p == q" << endl; }
    return 0;
}
/*
  输出：
  p: false
  p1 == p2
  p == q
*/