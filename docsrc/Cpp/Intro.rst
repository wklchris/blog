C++ 简介
===============

本章介绍 C++ 的基础使用，包括编译与语法介绍。


编译：Hello world
---------------------

.. admonition:: 安装编译器
    :class: tip

    C++ 有众多的编译器可以选用，我个人习惯使用 gcc/g++ 编译器。

    * `MinGW <https://www.mingw-w64.org/downloads/>`_ 页面提供了一系列可用的编译件。我安装其中的 `mingw-builds <https://github.com/niXman/mingw-builds-binaries/releases>`_ 来使用 g++：
      
      * 使用 posix 线程库编译的版本以获得最佳的跨平台兼容性（而不是用 win32 线程库编译的版本）
      * 使用 ucrt 运行时库版本以获得更好的支持。除非在 Windows 10 之前的操作系统上运行，否则不建议使用较旧的 msvcrt 编译版本。

      按照以上特性，我一般选择安装 ``x86_64-release-posix-seh-ucrt`` 编译版本。
    
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

.. code-block:: console

    g++ hello_world.cpp

该命令会将 C++ 代码文件编译为同名的可执行文件。在 Windows 上，即为 ``hello_world.exe`` 。用户可以从命令行运行该文件：

.. code-block:: console

    ./hello_world.exe

在命令行输出中，我们可以看到： ``Hello world`` ，这表示我们的程序如预期地成功运行了。


输入输出（IO）流
-----------------

iostream 库包含输入流 ``istream`` 与输出流 ``ostream`` 两种类型。标准库在此基础上定义：

* 输入流对象：与输入运算符 ``>>`` 结合使用。运算符左侧是 istream 对象，右侧为值。

  * **标准输入** ``std::cin``

* 输出流对象：与输出运算符 ``<<`` 结合使用。运算符左侧是 ostream 对象，右侧为值。

  * **标准输出** ``std::cout``
  * **标准错误** ``std::cerr``
  * **其他输出信息** ``std::clog`` 

* **操纵符** ``std::endl``\ ：刷新缓冲区。即结束当前行，并将缓冲区内容写入到输出。


.. admonition:: 输入、输出运算符均是左结合的
   :class: tip
   
   尽管输入、输出运算符看起来指向不同的方向，但实际上它们都是左结合的，这保证了连续运算的合法性。例如：

   * ``std::cin >> x >> y;`` 表示先读取输入流到 x，并返回 istream 对象；然后对返回的对象执行第二个操作，即读取输入流到 y。它等价于 ``(cin >> x) >> y;``\ 。
   * ``std::cout << 'a' << std::endl;`` 表示先将字符 ``'a'`` 写到输出流，并返回一个 ostream 对象；然后再将 ``std::endl`` 写入到该对象上。

   请仔细体会运算符的特性。


using 声明
---------------

C++ 标准库（命名空间为 ``std``\ ）中定义了许多实用的库函数，比如输出函数 ``std::cout``\ 。使用 using 声明，我们可以免于在每次使用库函数时添加 ``std::`` 前缀。例如：

.. literalinclude:: codes/hello_world_using.cpp
    :linenos:
    :language: c++

.. admonition:: 不推荐的写法：using name std;
   :class: warning

   有的地方也会提到 ``using namespace std;`` 这种写法。但一般来说，这不是一个好的实践方式。因为这种操作是盲目的，除非你了解 std 中的所有库函数名称。这种贪心的行为就好比在 Python 中使用 ``from lib import *``\ 。

为了方便起见，下文中大多会采用 using 声明，而不是在每次使用时添加命名空间前缀。在给出代码片段时，有时为了简洁，using 声明可能会在展示中被省略。


.. _undefined:

未定义行为（UB）
--------------------

C++ 中的未定义行为（undefined behavior, UB）会导致不可预知的后果。程序可能继续工作，可能异常终止，也可能得到垃圾数据。例如，除数为 0 、索引超界都是未定义行为。

下例给出一个索引超界的未定义行为例子：

.. literalinclude:: codes/undefined_behavior.cpp
    :linenos:
    :language: c++

由于未定义行为在不同环境中编译、运行可能产生不同结果，你的结果可能与我不同。
