函数与分离代码
===================

在详细介绍函数（以及之后的 :doc:`Class` 章节）之前，我们需要先对分离代码有所了解。在大型项目中，拆分代码并合理地组织它们是至关重要的。尽管代码拆分通常在类级别而不是在函数级别进行，但理解这种思想有助于我们组织函数（以及任何代码）。

本节会先介绍 C++ 的代码分离的内容，然后讨论函数。

作用域
------------

C++ 中的作用域概念很好理解。最常见的作用域分隔符是花括号，例如函数、类、if 语句等内部。下面的代码展示了一些作用域的例子：

.. literalinclude:: codes/scope/scope.cpp
   :linenos:
   :language: cpp

输出：

.. code-block::

   main() scope: area = 1
   inner scope : area = 1.23


命名空间
--------------

C++ 中的\ **命名空间**\ （Namespace）提供了一种规避名字冲突的方案。例如，我们熟知的 ``std::cout`` 就是一种命名空间的写法，表示 std 命名空间下的 cout 对象。

下例中定义了一个 Circle 命名空间，我们通过 ``Circle::pi`` 与 ``Circle::main()`` 访问它的成员变量与成员函数：

.. literalinclude:: codes/scope/namespace.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 12, 15

输出：

.. code-block::

   pi = 3.14159
   Area of circle of radius 2 = 12.5664

在名字不冲突的情况下，有两种方法可以省略命名空间前缀：

1. **using 声明**\ ：在使用 ``using std::cout;``\ 之后，在当前作用域的后续行中可以直接使用 ``cout`` 代替 ``std::cout``\ 。
   
   .. code-block:: cpp

      void my_print(std::string s) {
          using std::cout;
          using std::endl;
          cout << s << endl;
      }

2. **using 指令**\ （不推荐）：在使用 ``using namespace std;``\ 之后，在当前作用域的后续行中可以直接使用 `std` 命名空间下的任意名字，例如 ``cout`` , ``endl``, ``string`` 等。 
  
   .. code-block:: cpp

      void my_print(std:string s) {
          using namespace std;
          cout << s << endl;
      }

.. admonition:: 谨慎使用 using namespace
   :class: warning
   
   使用 ``using namespace`` 指令意味着将该命名空间内的所有名字都引入到当前的作用域。因此，需要特别注意在当前作用域中不额外声明与该命名空间中的名字相同的对象。

   我个人建议尽量避免在任何情况下使用 using 指令，而总是尝试用 using 声明来代替。尤其是在一个较大的作用域中，或者是using 的命名空间是类似 std 这样大型且并非由自己撰写的——因为你根本不了解它内部的名字。在一个类的成员函数内部使用 using 指令时，你可能没有意识到该类的某个成员的名字可能与该命名空间内的名字相同。典型的例子是 std 命名空间中的 `vector` 或 `map` 等常见的单词。


代码文件分离
--------------

* **头文件与源文件**\ ：传统的 C++ 文件分离方式。
* **模块**\ ：C++ 20 引入了一种新的文件分离概念，模块，并支持用 ``import`` 语法来调用。


头文件与源文件
^^^^^^^^^^^^^^^^^^^^

在 C++ 中，我们可以直接定义一个变量、函数或者类。也可以先对它们进行声明、稍后再定义它们的内容，以实现声明与定义的分离；这个“稍后”甚至可以放在另一个代码文件中，也就形成了\ **头文件**\ （Header file）与\ **源文件**\ （Source file）的关系。

* 头文件：通常使用 `.hpp` 扩展名或者（兼容 C 语言的） `.h` 扩展名，用于存放声明。
* 源文件：通常使用 `.cpp` 或者 `.cc` 扩展名，用于存放定义。我们习惯于用同名的头文件与源文件来实现一个模块。

要使用一份头文件中的声明，我们需要使用预处理指令 ``#include`` 。在使用 C++ 标准库（或者其他已安装的库）的头文件时，我们使用尖括号 ``<>`` 来包围头文件名；在使用当前文件夹下的头文件时，我们使用双引号 ``""`` 来包围头文件名。例如：

.. code-block:: cpp

   #include <iostream>     // 引入标准库头文件 iostream
   #include "MyClass.hpp"  // 引入当前路径下的头文件 MyClass.hpp

尽管头文件-源文件式的代码分离被沿用了许多年（从 C 语言算起，已超过半个世纪），但它存在一些显著的问题：

* 编译时间长：在大型项目中，一份头文件可能被许多源文件引入。预处理语句将会被执行许多次，使编译时间变长。
* 链式引入：当头文件需要使用一个被其他头文件声明的类、函数等内容时，它必须引入整个头文件，尽管可能只有一小部分代码是实际需要的。当这样的头文件间引入链式发生时，通常意味着引入了大量的冗余代码。
* 引入顺序：当不同头文件中存在同名声明时，引入还可能存在顺序的问题。 

为了解决这些问题，现代 C++ 提出了模块的概念，参考 :ref:`module` 一节。

.. _module:

模块
^^^^^^^^^^

**模块**\ （Module）作为头文件的继任者，在 C++ 20 被引入，并支持用 ``import`` |cpp20| 语法来调用。之后的 C++ 23 实现了对于标准库的模块化，允许使用 ``import std;`` |cpp23| 来加载标准库模块。

模块的一个优势在于，我们可以不再关心具体的标准库头文件名，而直接加载 std 模块。在之前，我们必须为每一个用的标准库头文件单独引入，例如我们要同时引入 ``<iostream>`` 与 ``<vector>`` 两个头文件：

.. code-block:: cpp
    
    #include <iostream>
    #include <vector>

尽管这两个头文件中的函数都在命名空间 ``std`` 中（例如 ``std::cout`` 与 ``std::vector``），但我们却需要使用两条指令引入。在 C++ 23 标准中，我们可以使用一条模块加载语句来替代：

.. code-block:: cpp
    
    import std;

下面是一个完整的模块示例（基于 C++ 23）。在 PointModule.cpp 文件中定义了一个 Point 类，然后在 module.cpp 文件中使用它。

.. _code-example-module:

.. literalinclude:: codes/scope/PointModule.cpp
   :linenos:
   :language: cpp

可以看到，我们在模块文件的开头使用 ``export module`` 来给出模块名，并告知编译器这是一个模块文件。接着，我们可以用 ``import`` 来加载其他模块文件，并用 ``export`` 来指定当前模块中的哪些内容是可以被加载到外部的。

随后，我们需要一个主文件来加载与使用上述模块：

.. literalinclude:: codes/scope/module.cpp
   :linenos:
   :language: cpp

其输出如下。关于如何编译以上模块代码文件，参考 :ref:`module-compile` 一节。

.. code-block::

   Point = (1,2)
   Point after shifting = (3,1)
   Point after scaling = (6,2)


.. _module-compile:

模块的编译命令
^^^^^^^^^^^^^^^^^^^

.. important::

   模块是一个比较新的 C++ 概念。截至本章节撰写时，编译器对其的编译命令支持仍在更新中。编译模块至少需要 GCC 15, Clang 18.1， 或者 Visual Studio 17.7 版本中的 MSVC。

   CMake 从 4.0 开始对 C++ 模块逐渐增大了支持，但仍是实验性的。它对 ``import std`` 的支持依赖于为 `CMAKE_EXPERIMENTAL_CXX_IMPORT_STD` 参数设定特定的 UUID 值（参考 `C++ import std support <https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst#c-import-std-support>`_ ），该值可能随 CMake 版本而变化。因此，暂时不推荐使用 CMake 来编译含 C++ 模块的项目。

   此外，由于 C++ 20 中无法使用 import std，只能混用模块加载与头文件引入。因此，个人建议在 C++ 20 之前的版本只使用头文件。

为了在代码中使用 ``import std;`` 来加载标准库模块，我们需要先编译一次标准库文件 `std.cc`\ ；编译后的模块文件会生成在当前目录的 `gcm.cache` 文件夹中。

.. code-block:: console

   g++ -std=c++23 -fmodules -fsearch-include-path -fmodule-only -c bits/std.cc


要编译上述 :ref:`C++ 模块示例：Point <code-example-module>` 的代码，以下第一条命令会编译 PointModule.cpp 模块文件生成 PointModule.o 文件，然后第二天命令将 module.cpp 编译并链接到 PointModule 模块，生成名为 module 的可执行文件。

.. code-block:: cpp
   
   g++ -std=c++23 -fmodules-ts -c PointModule.cpp
   g++ -std=c++23 -fmodules-ts module.cpp PointModule.o -o module

