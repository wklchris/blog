#include <iostream>
#include <memory>

void wp_check(std::weak_ptr<int> p_weak) {
    if (std::shared_ptr<int> p = p_weak.lock()) {
        // p_weak 指向的对象有效
        std::cout << "Valid: " << *p << std::endl;
    } else {
        std::cout << "Invalid weak pointer.";
    }
}

int main() {
    // 用共享指针 sp 初始化弱指针 wp
    auto sp = std::make_shared<int>(7);
    auto wp = std::weak_ptr(sp);
    wp_check(wp);

    // 将 sp 置空，其指向对象被释放
    sp.reset();  
    wp_check(wp);

    // 将 wp 置空
    wp.reset();  
    return 0;
}
/*
  输出：
  Valid: 7
  Invalid weak pointer.
*/