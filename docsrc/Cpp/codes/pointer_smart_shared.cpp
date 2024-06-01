#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(12);
    // 使用 auto 简化书写
    auto sp2 = std::make_shared<int>(37);

    // swap: 交换两个智能指针的值
    sp2.swap(sp);
    std::cout << "sp: " << *sp << ", sp2: " << *sp2 << std::endl;

    // 令 sp 指向 sp2 指向的对象
    // 当 sp 原指向的对象没有任何智能指针引用时，其会被销毁
    sp = sp2;

    // 拷贝智能指针，让 sp3 指向与 sp2 相同的对象
    auto sp3(sp2);

    // unique(): 检查 sp 是否是所指对象的唯一用户
    sp = std::make_shared<int>(127);
    std::cout << "sp unique? " << sp.unique() << std::endl;
    
    // reset: 让 sp 不再指向任何对象。如果无其他共享指针指向该对象，则释放其内存
    sp.reset();
}
/*
  输出：
  sp: 37, sp2: 12
  sp unique? 1
*/