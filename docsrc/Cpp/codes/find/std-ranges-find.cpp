#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

struct Student {
    int id;
    double grade;
};

int main() {
    std::vector<Student> v { Student{1, 90}, Student{2, 75}, Student{3, 80} };
    int target_id = 2;
    
    // 利用 std::ranges::find 与成员指针 &Student::id
    if (auto it = std::ranges::find(v, target_id, &Student::id); it != v.end()) {
        std::cout << "[std::ranges::find] Found student with id=" << target_id
                  << " at index " << std::distance(v.begin(), it) 
                  << ", whose grade is " << it->grade << std::endl;
    } else { std::cout << "Student not found" << std::endl; }

    // 传入两个迭代器以选定检索范围：[2, 3)，下标从 0 开始
    int offset_start = 2, offset_end = 3;
    if (
        auto it = std::ranges::find(
            v.begin() + offset_start,
            v.begin() + offset_end,
            target_id, &Student::id
        ); it != v.end()
    ) {
        std::cout << "[std::ranges::find] Found student with id=" << target_id
                  << " at index " << std::distance(v.begin(), it) 
                  << ", whose grade is " << it->grade << std::endl;
    } else {
        std::cout << "Student not found within index range ["
                   << offset_start << ", " << offset_end << ")" << std::endl;
    }
}