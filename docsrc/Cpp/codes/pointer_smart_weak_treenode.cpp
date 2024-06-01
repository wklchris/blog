#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Node: public std::enable_shared_from_this<Node> {
public:
    Node(int v) : value(v) {};
    void addChild(std::shared_ptr<Node> child) {
        // 使用 shared_from_this 从对象内部创建其自身的共享指针
        child->parent = shared_from_this();
        children.push_back(child);
    }
    void removeChild(std::shared_ptr<Node>& child) { // 传引用，以更改外部 child
        auto it = std::find_if(children.begin(), children.end(),
                               [&child](const auto& v) { return v == child; });
        // 将 child 从当前节点的子节点列表中移除，然后置空 child
        if (it != children.end()) {
            children.erase(it);
            child.reset();
        }
    }
    void printValues() const {
        std::cout << "Current: " << getValue() << " (parent value: ";
        // 先将弱指针强化为shared_ptr，再判断是否为空，非空则使用
        if (auto parent_ = getParent().lock()) {
            std::cout << parent_->getValue() << "; ";
        } else {
            std::cout << "None; ";
        }
        std::cout << "has " << getChildren().size() << " children)\n";
        for (auto sp : getChildren()) {
            std::cout << "* Child value: " << sp->getValue() << "\n";
        }
    }
    int getValue() const { return value; }
    std::weak_ptr<Node> getParent() const { return parent; }
    std::vector<std::shared_ptr<Node>> getChildren() const { return children; }

private:
    int value;
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
};

int main() {
    auto root = std::make_shared<Node>(1);
    auto child1 = std::make_shared<Node>(101);
    auto child1_wptr = std::weak_ptr<Node>(child1);  // 此处仅用于追踪引用计数
    auto child2 = std::make_shared<Node>(102);
    root->addChild(child1);
    root->addChild(child2);
    auto grandchild1 = std::make_shared<Node>(10101);
    child1->addChild(grandchild1);

    std::cout << "--- Root ---" << "\n";
    root->printValues();
    std::cout << "--- Child 1 ---" << "\n";
    child1->printValues();
    // 引用计数来自 child1 自身，以及 root 中的 children
    std::cout << "Use count: " << child1.use_count() << "\n";
    std::cout << "--- Grandchild 1 ---" << "\n";
    grandchild1->printValues();

    root->removeChild(child1);
    std::cout << "\n--- Root (After removal) ---" << "\n";
    root->printValues();
    std::cout << "--- Child 1 (After removal) ---" << "\n";
    std::cout << "Use count: " << child1_wptr.use_count() << "\n";
    std::cout << "--- Grandchild 1 (After removal) ---" << "\n";
    grandchild1->printValues();
    std::cout << "Use count: " << grandchild1.use_count();

    return 0;
}
/*
  输出：
  --- Root ---
  Current: 1 (parent value: None; has 2 children)
  * Child value: 101
  * Child value: 102
  --- Child 1 ---
  Current: 101 (parent value: 1; has 1 children)
  * Child value: 10101
  Use count (Node): 2
  Use count (Weak ptr): 2
  --- Grandchild 1 ---
  Current: 10101 (parent value: 101; has 0 children)
  
  --- Root (After removal) ---
  Current: 1 (parent value: None; has 1 children)
  * Child value: 102
  --- Child 1 (After removal) ---
  Use count: 0
  --- Grandchild 1 (After removal) ---
  Current: 10101 (parent value: None; has 0 children)
  Use count: 1
*/