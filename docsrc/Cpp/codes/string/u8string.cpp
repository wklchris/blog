#include <iostream>
#include <string>

int main() {
    std::string s_zh = "std字串";
    std::string s_zh2 = "你好，世界！";
    
    std::u8string u8_zh = u8"u8字串";
    // 从 std::u8string 转为 std::string（由于 u8string 不能直接 cout）
    std::string u8_zh_converted(
        reinterpret_cast<const char*>(u8_zh.data()), 
        u8_zh.length()
    );

    std::cout << s_zh << ", string size: " << s_zh.length() << "\n"
              << s_zh2 << ", string size: " << s_zh2.length() << "\n"
              << u8_zh_converted << ", u8string size: " << u8_zh.length() << std::endl;
    
    size_t d_pos = s_zh.find('d');
    if (d_pos != std::string::npos && d_pos + 1 < s_zh.length()) {
          // 逐个打印，乱码
        for (char c : s_zh) { std::cout << "-" << c; }
        std::cout << '\n';
        // 连续打印（从字母 d 之后开始）：不建议这样尝试手动地逐字打印，此处仅作示例
        for (size_t i = d_pos+1; i+2 < s_zh.length(); i+=3) {
            std::cout << "-" << s_zh[i] << s_zh[i+1] << s_zh[i+2];
        }
    }
}