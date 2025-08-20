#include <iostream>
#include <string>

enum class TrafficLight {
    green, yellow, red
};

// 按照绿-黄-红的顺序切换信号灯
TrafficLight& operator++(TrafficLight& light) {
    using enum TrafficLight;
    switch(light) {
        case green:
            return light = yellow;
        case yellow:
            return light = red;
        case red:
            return light = green;
        default:
            return light;
    }
}

// 定义一个打印名称的辅助函数
std::string traffic_light_name(TrafficLight light) {
    using enum TrafficLight;
    switch(light) {
        case green: return "green";
        case yellow: return "yellow";
        case red: return "red";
        default: return "";
    }
}

int main() {
    TrafficLight light = TrafficLight::green;
    std::cout << "Light is " << traffic_light_name(light) << '\n';

    ++light;
    std::cout << "Now light is " << traffic_light_name(light) << std::endl;
}