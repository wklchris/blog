速查：C++ 语法
====================

.. hint::

   本章是 C++ 基础语法的总结，适用于有其他编程语言经验的读者快速熟悉 C++ 语法。

C++ 基础语法包括：

* 语句以分号 ``;`` 结束。
* 语句块以一对花括号 ``{...}`` 标识范围。缩进与换行并不重要。
* 注释：
  
  * 行内注释： ``//`` 将其同一行内右侧的内容标记为注释。
  * 多行注释： 包含在 ``/*`` 与 ``*/`` 内部的内容标记为注释。
    
    * 多行注释\ **不支持嵌套**\ ，因此在调试中注释掉多行代码时，推荐用行内注释的方式注释每一行。 

* 变量类型
  
  * 字符（char）与字符串（std::string）：
    
    * 字符使用单引号（如 ``'a'``\ ），字符串使用双引号（如 ``"abc"``\ ）。不可混用。
    * C++ 字符串的 **实际长度为实际长度加 1**\ ，因为它总包含一个末尾的 ``\0`` 字符。
    * 我们常提到 C 风格字符串，它的类型是 ``const char*``\ ，即常量字符指针。
    * 由于兼容 C，在 C++ 的 **字符串字面值并不属于 std::string 类型**\ 。

* 控制语句：
  
  * for 循环：循环变量在循环体结束后不可使用。
    
    * 范围 for 循环 |cpp11| 对可迭代对象进行迭代，无需循环变量 
  
  * if 条件：支持 ``else if`` 分支语句块。
  * switch 条件：
    
    * case 标签必须是\ **整型常量表达式**\ 。
    * 每个 case 标签内部一般均用 ``break;`` 结尾。
    * 用 ``default:`` 处理未匹配任何 case 标签的情形。
  
  * try..catch 及 throw 语句：
    
    * 常使用 ``<stdexcept>`` 库中定义的异常。基础的为 ``std::runtime_error``\ 。
    * 使用 ``err.what()`` 来检查错误对象 err 中包含的异常信息。
    * throw 抛出的异常如果没有被捕获，程序将会终止。程序中任何之后的内容都不会再被执行。