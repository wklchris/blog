数据类型进阶
===============

本节继续 :doc:`DataTypes` 一节的内容，介绍：

* const 常量限定符
* 类型别名：typedef 等用法
* 类型操作：auto 与 decltype

以及：

* 标准库支持的变量类型：例如字符串（\ ``std::string``\ ）。
* 标准库支持的模板类型：例如向量（\ ``std::vector``\ ）。

关于指针与引用，请参考 :doc:`PointerAndRef` 一节的内容。


.. _const:

常量：const
----------------

关于引用与常量、指针与常量，分别参考 :ref:`const-reference` 与 :ref:`pointer-and-const` 章节。

当我们想定义一个不能被改变的值时，使用 const 限定符在变量定义时进行修饰。

* 常量在定义时 **必须显式初始化**\ 。
* 常量一经创建，就不能再改变其值。
* 常量可以用同基础类型的变量初始化；反之，变量也可以用同类型的常量初始化或赋值。

.. code-block:: c++

    const double e_base = 2.71828;

    long double pi_value = 3.14159265;
    const long double pi = pi_value;

    const int capacity;     // 错误：未初始化
    e_base = 2.718;         // 错误：不能更改常量的值   

.. admonition:: 常量一般只在当前文件有效
    :class: tip

    值得注意的是，const 常量只在当前文件内有效。要在多个文件之间共享某个常量，需要在定义与声明中均使用 ``extern`` 修饰：

    .. code-block:: c++

        // 在 lib.h 头文件中声明常量，令包含该头文件的文件共享该常量
        extern const int maxflow;
        // 在 lib.cpp 文件中定义常量
        extern const int maxflow = 1800;


.. _constexpr:

常量表达式：constexpr
------------------------

常量表达式 constexpr |cpp11| 是指值不变且在编译时就能得到结果的表达式，或者用这种表达式初始化的常量对象。

* 常量表达式类型必须是字面值类型，比如浮点数、任意整型。指针也属于字面值类型，但是定义为常量表达式时，初始值必须为 nullptr 或 0，或者固定地址对象的地址。

.. code-block:: c++

    constexpr double half_pi = 3.14159 / 2;


.. _type-alias:

类型别名、decltype 与 auto
------------------------------

typedef
^^^^^^^^^^^^^

使用类型别名可以简化输入、让人迅速理解使用类型的目的。C++ 使用 ``typedef`` 或者 ``using =`` 定义类型别名：

.. code-block:: c++

    typedef int ages;       // 将 ages 定义为 int 的别名
    ages person_age = 21;

    using grades = double;  // 将 grades 定义为 double 的别名
    grades midterm = 95, final_exam = 90;

需要特别注意对于复杂类型（例如指针）的类型别名使用。请注意下例中 ``p1`` 与 ``p2`` 的不同。

.. code-block:: c++

    typedef int *intp;      // 定义了 intp 类型，即指向 int 的指针
    const intp p1 = 0;      // 指向 int 的常量指针

    const int *p2 = 0;      // 指向 const int 的指针

在上例中，p1 定义中的 const 修饰 intp 类型，表示 p1 是一个 intp 类型的常量，即指向 int 的常量指针。p2 定义中的 const 则只修饰 int，而 \*p2 作为标识符。这表示 p2 是一个指针，这个指针指向 const int 类型。 


decltype 
^^^^^^^^^^^^^

decltype 推断类型（而不计算结果），并用推断类型定义对象：

* 在对变量进行类型推断时，decltype 保留：（1）引用，以及；（2）顶层常量属性。
* 在对表达式（非变量）进行类型推断时，decltype 返回表达式结果的类型

.. code-block:: c++

    const int m = 12, &r = m;
    decltype(n) n1 = 0;     // 推断为 const int
    decltype(r) r1 = m;     // 推断为 const int& 引用
    
    int n = 37, *p = &n;
    decltype(*p) r2 = n;    // 解引用后，推断为 int& 引用


auto 类型
^^^^^^^^^^^^^^

auto |cpp11| 类型允许编译器推断类型，其在定义时必须初始化：

.. code-block:: c++

    double x = 1.23;
    int n = 1;
    auto y = n + x;  // y 推断为 double 类型

* 将引用用于 auto 对象的初始化，auto 将被推断为被引对象的类型，而不是引用类型。
* auto 一般忽略顶层常量；如果需要顶层常量，显式地使用 ``const auto``\ ：
  
  .. code-block:: c++

     const double pi = 3.14;
     auto a = pi;           // a 推断为 double 类型
     const auto b = pi;     // b 推断为 const double 类型
     const auto &r = pi;    // 推断引用 r 为常量引用



.. _string:

字符串
-------------

.. _std-string:

std::string
^^^^^^^^^^^^^^^^^^^^^^^

.. _std-vector:

向量（std::vector）
-----------------------
