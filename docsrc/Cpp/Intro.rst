C++ 简介
===============

本章介绍 C++ 的基础使用，包括编译与语法介绍。

C++ 基础语法速查
-------------------

.. hint::

   本小节是本章的总结，适用于有其他编程语言经验的读者快速熟悉 C++ 语法。

C++ 基础语法包括：

* 语句以分号 ``;`` 结束。
* 注释：
  
  * 行内注释： ``//`` 将其同一行内右侧的内容标记为注释。
  * 多行注释： 包含在 ``/*`` 与 ``*/`` 内部的内容标记为注释。
  * 多行注释不支持嵌套，因此在调试中注释掉多行代码时，推荐用行内注释的方式注释每一行。 

* 控制语句：
  
  * if 语句：支持 ``else if`` 分支语句块。

* 变量类型
  
  * 字符（char）使用单引号，字符串（string）使用双引号。不可混用。


编译：Hello world
---------------------

.. admonition:: 安装编译器
    :class: tip

    C++ 有众多的编译器可以选用，我个人习惯使用 gcc/g++ 编译器。

    * `MinGW <https://www.mingw-w64.org/downloads/>`_ 页面提供了一系列可用的编译件。我安装其中的 `mingw-builds <https://github.com/niXman/mingw-builds-binaries/releases>`_ 来使用 g++：
      
      * 使用 posix 线程库编译的版本以获得最佳的跨平台兼容性（而不是用 win32 线程库编译的版本）
      * 使用 ucrt 运行时库版本以获得更好的支持。除非在 Windows 10 之前的操作系统上运行，否则不建议使用较旧的 msvcrt 编译版本。
    
    一些其他编译器：

    * `LLVM/Clang <https://releases.llvm.org/download.html>`_
    * Visual Studio/MSVC
    * Intel C++

C++ 是一门编译型语言，需要将写有 C++ 代码的源文件通过编译器编译为可执行文件，然后才能执行。这与用诸如 ``python hello_world.py`` 通过解释器来执行代码的 Python 等解释性语言不同，对初学者而言可能繁琐一些。

C++ 的源文件一般以 ``.cpp`` 或者 ``.cc`` 为扩展名。下面实现了一个基础的 Hello world 程序：

.. literalinclude:: codes/hello_world.cpp
    :linenos:
    :language: c++

* 头文件：C++ 用 ``#include`` 指令来包含头文件。上例中的 ``<iostream>`` 表示调用 C++ 标准库中的 iostream 库。包含头文件的指令通常在源文件的开头。
* 主函数：C++ 中必须要有一个名为 ``main`` 的主函数，该主函数必须为 ``int`` 类型。
  
  * 主函数可以不包含任何形参，比如上例中的 ``main()`` 。
  * 主函数一般以返回 0 （例中 ``return 0`` ）表示程序运行正常、返回非零值表示程序运行异常。

* 输出： ``std::cout`` 表示调用命名空间 ``std`` 中的 ``cout`` 对象，它代表标准输出； ``std::endl`` 表示行末。
  
  * 输出运算符 ``<<`` 作用是将右侧的值写入到左侧的 ostream 对象，并返回左侧的对象；因此，输出运算符可以如上例一样连用。

将上述代码保存为 ``hello_world.cpp`` 文件，并用编译器编译它。这里以 g++ 为例：

.. code-block:: powershell

    g++ hello_world.cpp

该命令会将 C++ 代码文件编译为同名的可执行文件。在 Windows 上，即为 ``hello_world.exe`` 。用户可以从命令行运行该文件：

.. code-block:: powershell

    ./hello_world.exe

在命令行输出中，我们可以看到： ``Hello world`` ，这表示我们的程序如预期地成功运行了。


控制：for, while 与 if
-------------------------

下例输出从 0 累加到 3 的结果，编译并运行后得到 ``Sum = 6`` 的输出。for 循环：

* for 循环的循环头包含三个部分：初始化语句、循环条件，以及表达式。
* 初始化语句中的对象 **在离开 for 循环之后不可使用** 。

.. literalinclude:: codes/control_for.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 4-6

用 while 循环实现同上例一样的功能：

.. literalinclude:: codes/control_while.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 4-7

下例的 if 条件语句能够根据用户输入的整数，判断其正负号：

* C++ 支持 ``else if`` 语法块。

.. literalinclude:: codes/control_if.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 10-16
