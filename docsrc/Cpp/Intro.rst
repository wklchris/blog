概述
============

本节学习 C++ 的基础语法。

个人的开发配置
---------------

.. note::

    如无特殊说明，本文的 C++ 代码均在 Windows 上使用 g++ 进行编译（使用了不低于 8.1.0 的 g++ 版本），并以 cpp 作为文件扩展名。如果使用了较新的 C++ 版本特性，我会在文中注明。

我使用 g++ 作为编译器来学习，以便在 Win/Linux/Mac 之间切换时有较小的编译器学习成本。

1. 使用 64 位设备的 Windows 用户可以前往 `MinGW64 Release <https://sourceforge.net/projects/mingw-w64/files/>`_ 下载安装 ``MinGW-W64 GCC`` 中的 ``x86_64-posix-seh`` 版本。
2. 解压后将其子文件夹 ``bin`` 添加到环境变量 ``PATH`` 即可。
3. 尝试在命令行中使用 ``g++ -v`` 命令来检查安装情况。

其他信息：

- 我个人使用的是 VS Code，其关于 g++ 的配置可以参考：\ `VSCode - Using GCC with MinGW <https://code.visualstudio.com/docs/cpp/config-mingw>`_ 这篇官方向导。
- 有一些网站可以在线运行 C++ 17 代码片段，比如 `Wandbox <https://wandbox.org/>`_。它们也是练习 C++ 的有效工具。


Hello world
-----------------

一个简短的 Hello world 代码（稍后解释每一行的含义），通过以下步骤编译成为可执行文件：

1. 将代码输入到 ``Hello-world.cpp`` 文件中。
2. 通过 Powershell 命令行，使用 ``g++`` 进行编译：\ :code:`g++ Hello-world.cpp`\ ，得到可执行文件。
3. 执行可执行文件 ``Hello-world.exe``。

.. literalinclude:: code/Hello-world.cpp
    :language: c++
    :linenos:

上述文件包含了 C++ 中最小的语法集合：

* **预处理器编译指令**\ ：\ ``#include`` 语句，后接需要包括文件的名称（放在尖括号内）

  * 本例中包括了 ``iostream``\ ，在需要打印文字到屏幕时它是必需的。

* 编译指令 ``using namespace``\ （后文介绍）
* **主函数**\ ：固定为 ``int main()``\ ，函数的主体写在一对花括号内。

  * 上例中的主函数内部有 3 条语句——语句以分号分割为准，而不是换行符。
  * 首先，使用 cout 将文字打印到屏幕；
  * 然后，让程序挂起，等待键盘输入（否则程序会在上一步之后立刻关闭）；
  * 最后，在程序收到上一步的键盘输入后，将 0 通过 return 返回，主函数与程序终止。

* 注释：每一行末尾的双斜线 ``//`` 之后的内容不会被编译。

  * 如有需要，使用 ``/* 多行注释 */`` 的形式可以注释多行内容。

上述文件在编译后，执行结果是在控制台中打印“Hello world”这一行文字，并挂起等候键盘输入。在用户敲击回车后，整个程序随即正常地终止了。
