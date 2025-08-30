函数与分离代码
===================

在详细介绍函数（以及之后的 :doc:`Class` 章节）之前，我们需要先对分离代码有所了解。在大型项目中，拆分代码并合理地组织它们是至关重要的。尽管代码拆分通常在类级别而不是在函数级别进行，但理解这种思想有助于我们组织函数（以及任何代码）。

本节会先介绍 C++ 的代码分离的内容（包括作用域与命名空间），然后再讨论函数。

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

内部作用域中的对象对于外部作用域而言是临时的。在一个作用域结束时，其内部的对象的生命周期（Lifetime）也就终止了；它们会（通过析构函数）被销毁，以释放所占用的内存。C++ 在初始化时为对象申请内存资源，在离开该对象的作用域时销毁它，这一管理逻辑被称为资源获取即初始化（Resource Acquisition Is Initialization, RAII）。


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

.. _header-file:

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

   此外，由于 C++ 20 中无法使用 import std，只能混用模块加载与头文件引入。因此，个人建议在 C++ 20 及之前的版本只使用头文件，从 C++ 23 开始再考虑使用模块。

为了在代码中使用 ``import std;`` 来加载标准库模块，我们需要先编译一次标准库文件 `std.cc`\ ；编译后的模块文件会生成在当前目录的 `gcm.cache` 文件夹中。

.. code-block:: console

   g++ -std=c++23 -fmodules -fsearch-include-path -c bits/std.cc


要编译上述 :ref:`C++ 模块示例：Point <code-example-module>` 的代码，以下第一条命令会编译 PointModule.cpp 模块文件生成 PointModule.o 文件，然后第二天命令将 module.cpp 编译并链接到 PointModule 模块，生成名为 module 的可执行文件。

.. code-block:: cpp
   
   g++ -std=c++23 -fmodules -c PointModule.cpp
   g++ -std=c++23 -fmodules module.cpp PointModule.o -o module


函数的参数传递与返回值
--------------------------

我们在 :ref:`function-basics` 一节中已简要地介绍了函数。在向函数传递参数时，最简单的方式是\ **传值**\ （Pass by value），即传递实际参数的拷贝：

.. code-block:: cpp
   
   // 参数 x 被复制一份，在函数内使用
   double square_area(double x) { return x * x; }

对于大型的对象，例如 `std::vector` 或 `std::string` 对象，进行复制是低效的。这时，我们添加 ``&`` 以\ **传引用**\ （Pass by reference）。当传入的参数在函数内不会被修改时，我们用 ``const`` 修饰来传递常量引用（参考 :ref:`const-and-constexpr` 一节）：

.. code-block:: cpp
   :linenos:

   int sum_vector(const std::vector<int>& v) {
       int result = 0;
       for (const int x : v) { result += x; }
       return result;
   }

在传值与传引用之外，有时候我们也传递指针（或其引用）；因为指针只存放了所指向对象的地址，它本身是小型的。不过传递与使用指针时，要特别注意所指对象的生命周期（尤其是 `unique_ptr` 指针）。此外，我们也可能传递一些 C++ “视图”型对象，例如 `std::string_view` 或 `std::span`\ ；它们也是小型的。例如：

.. code-block:: cpp
   :linenos:
   
   void modify(std::shared_ptr<Data>& ptr);
   void print_in_uppercase(std::string_view sv);
   int sum_span(std::span<const int> sp);

除了参数，函数还能利用所在作用域的对象，也即环境变量或状态变量。一个常见的例子是，类的成员函数可以访问该类的成员变量和其他成员函数，而无需以参数的形式传递它们。另一个例子是利用定义在代码的最外层作用域中的变量，即全局变量（Global variable）；但全局变量十分不利于代码组织与错误排查，不建议使用它。

上例中返回值的类型是小型的，直接返回也十分高效。但在返回大型对象时，事情稍微变得复杂了。需要说明的是，我们只在很少数的情况下才返回引用或指针，因为（手动管理它们）较容易带来生命周期问题。好在 C++ 除了复制对象外，还支持一种移动对象操作。C++ 编译器会自动优化代码，在返回大型的、可移动的临时对象时使用移动而不是复制。下例是一个将字符串中的字母全转为大写的例子：

.. literalinclude:: codes/function/func_arg_string.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 5-10

.. tip::

   程序在执行时的实际性能，还涉及到一些其他的 C++ 编译器优化，比如返回值优化（参考 :ref:`RVO` 一节）。正确地传递参数和返回值，才能让 C++ 编译器应用一些特定的优化手段。

最后，C++ 也允许使用 ``auto`` 作为返回值类型，让编译器进行推断，例如 ``auto plus(int x, char c);`` 。不过我建议尽量不使用这种语法：在定义函数时清晰地写出返回类型有助于整理思路，增强代码的可读性。此外，函数还支持一种箭头式的后缀返回值类型语法，这时的 `auto` 仅仅作为占位符使用：

.. code-block:: cpp
   
   auto plus(int x1, int x2) -> int { return x1 + x2; }

匿名函数在指定返回值类型时也涉及这种语法，参考 :ref:`lambda-function` 一节。


多值返回与结构化绑定
-----------------------

C++ 中的函数只能返回一个对象；要返回多个数值，传统的方法是定义一个 struct 结构体，将要返回的数值存储在结构体中：

.. code-block:: cpp
   :linenos:

   struct Person { int id; std::string name; unsigned int age; };

   Person getRecord(int id) {
      // ...
      return Person{p_id, p_name, p_age};
   }

   void print_person(int person_id) {
       Person p = getRecord(person_id);
       std::cout << p.id << " " << p.name << ": Age " << p.age << std::endl;
   }

结构化绑定 |cpp17| 提供了一种将返回值的成员解包到变量的方法，使用方括号配合对应数量的变量并配合 ``auto`` 类型关键字即可：

.. code-block:: cpp

   auto [p_id, p_name, p_age] = getRecord(person_id);
   std::cout << p_id << " " << p_name << ": Age " << p_age;

结构化绑定在遍历映射对象（如 `std::map` 与 `std::unordered_map`\ ）时十分常用。在遍历时，可以按需使用引用 ``auto&`` 或者常量引用 ``const auto&`` 形式。

.. code-block:: cpp

   std::map<int, std::string> person_map;
   for (auto& [id, name] : person_map) {
       std::cout << "Person ID=" << id << ", name: " << name << std::endl;
   }

内联函数
-------------

内联函数（Inline function）是一类 *建议* （而不是强制）编译器进行展开插入的函数。当一个函数被内联时，不是调用它，而是直接将它的代码插入到当前位置。这能够消除函数调用相关的开销（参数传递等），但代价是增大可执行文件的体积。

C++ 可以使用 ``inline`` 关键字在函数声明时将其标记为内联，编译器会决定是否在编译时将其作为内联函数。特别地：

* 内联函数不用遵守单次定义规则，可以在多处被定义。
* 类的函数默认是内联的，无需手动指明 `inline` 关键字。


.. _lambda-function:

匿名函数(Lambda函数)
-----------------------

匿名函数，或称 Lambda 函数、Lambda 表达式，是一种临时创建函数的方式。例如一个判断传入的 int 参数是否为负数的匿名函数：

.. code-block:: cpp

   [](int n) { return n < 0; }

* 方括号用来指定匿名函数的捕获列表，也即需要在函数内使用的外部变量。
  
  * 空方括号表示不捕获任何环境变量。
  * 若要以引用捕获外部变量 `x`\ ，使用 ``[&x]``；要以值复制变量 ``x``\ ，使用 ``[x]``
  * 若要捕获多个变量，使用逗号分隔。例如： ``[x, &y]`` 
  * 若要捕获所有外部变量，使用 ``[&]``\ （引用）或 ``[=]``\ （复制值）。
  * 特别地，在类中使用匿名函数时，通过 ``[this]``\ （引用）或 ``[*this]``\ （复制值）来捕获当前的类对象。

* 圆括号用来指定函数要接受的参数
* 花括号用来指定函数体

匿名函数的返回值类型是自动推断的。如果有必要显式地指定，使用箭头语法：

.. code-block:: cpp

   [](int n) -> bool { return n < 0; }

匿名函数用作函数的参数也是十分常见的，我们在 :ref:`std-variant` 一节中介绍 `std::visit` 时就提到过。下例展示了一个在 `std::cout_if` 与 `std::for_each` 中传递匿名函数作为参数的例子。由于 `std::for_each` 只能传入单参数的函数（用来填充迭代器范围内的每个元素），因此我们无法将 `sum` 作为参数传递给匿名函数，必须通过捕获 `sum` 的引用来更新累加结果。

.. literalinclude:: codes/function/lambda.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 9, 14

输出：

.. code-block::

   Count of negative numbers: 3
   Sum of negative numbers: -10

匿名函数被广泛用于需要将语句包装为函数、但又不希望为该函数命名的场合（往往因为该函数只被使用这一次）。除了作为参数，匿名函数还常常用于在复杂情况下初始化对象。下例使用匿名函数来初始化常量 `chars_counts`\ ，避免了为本次初始化创建额外对象（匿名函数内的 counts 对象在离开函数后销毁）：

.. literalinclude:: codes/function/lambda_init.cpp
   :linenos:
   :language: cpp

输出：

.. code-block::

   H: 1
   c: 1
   e: 1
   l: 2
   o: 1
   p: 2


函数对象*
-------------

函数对象 （Function object 或简称 Functor）是指使一个对象能作为函数使用，也即使用 ``()`` 的方式来调用它。这部分内容请阅读 :ref:`function-operator` 一节。
