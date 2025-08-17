#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

struct Student {
    int id;
    double grade;
    // 重载了等于（==）比较符
    bool operator==(int other_id) const { return id == other_id; }
};

int main() {
    std::vector<Student> v { Student{1, 90}, Student{2, 75}, Student{3, 80} };
    int target_id = 2;
    
    // 现代的 std::find 写法
    if (auto it = std::find(v.begin(), v.end(), target_id); it != v.end()) {
        std::cout << "[std::find] Found student with id=" << target_id
                  << " at index " << std::distance(v.begin(), it) 
                  << ", whose grade is " << it->grade << std::endl;
    }

    // 传统的 for 循环嵌套 if 的写法
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i].id == target_id) {
            std::cout << "[For-loop]  Found student with id=" << target_id
                      << " at index " << i
                      << ", whose grade is " << v[i].grade << std::endl;
        }
    }
}