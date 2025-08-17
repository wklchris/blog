#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people { {"Tom", 43}, {"Jane", 26}, {"Bob", 33} };

    char target = 'B';
    if (auto it = std::find_if(people.begin(), people.end(),
        [target](const Person& p) {
            if (p.name.empty()) { return false; }
            return p.name[0] == target;
        }); it != people.end()
    ) {
        const auto& [name, age] = *it;
        std::cout << "Found person with name initial letter '" << target
                  << "': " << name << ", age " << age << std::endl;
    } else {
        std::cout << "Person with name initial letter '" << target
                  << "' not found" << std::endl;
    }
}