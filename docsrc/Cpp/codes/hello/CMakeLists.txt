# CMake 版本不得低于 3.10
cmake_minimum_required(VERSION 3.10)
project(hello)  # 为程序命名

# 使用 C++ 11 标准（第一版现代 C++）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

# 将源文件 hello.cpp 编译为可执行文件
# 输出可执行文件的文件名与上文的程序命名相同
add_executable(${PROJECT_NAME} hello.cpp)