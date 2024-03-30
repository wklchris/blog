#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    string s = "abaccbba13caabbbcc539207aacb";
    vector<string> targets {"other", "a", "b", "c"};
    vector<int> counts(targets.size() + 1, 0);
    int total = 0;
    for (char c: s) {
        switch (c) {
            case 'a':
                ++counts[1];
                break;
            case 'b':
                ++counts[2];
                break;
            case 'c':
                ++counts[3];
                break;
            default:  // 其他情形
                ++counts[0];
                break;
        }
    }
    for (int i = 0; i < targets.size(); ++i) {
        cout << "Count of '" << targets[i] << "': "
             << counts[i] << endl;
    }
    return 0;
}
/*
    输出：
    Count of 'other': 8
    Count of 'a': 7
    Count of 'b': 7
    Count of 'c': 6
*/