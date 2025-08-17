#include <iostream>

struct MyClass {
    int id;
    double value;
};

int main() {
    MyClass data {1, 0.618};
    
    double MyClass::* value_ptr = &MyClass::value;
    double data_value = data.*value_ptr;
    std::cout << "data.value = " << data_value << std::endl;
}