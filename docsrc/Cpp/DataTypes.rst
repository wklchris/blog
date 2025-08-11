常用数据类型
==============

本节介绍 C++ 的常见数据类型，包括：

* 基础数据类型：
  
  * 布尔型 `bool`\ ：参考 :ref:`bool-type` 一节
  * 整型（如 `int` 与 `char`）\ ：参考 :ref:`integral-type` 一节
  * 双精度浮点数 `double`\ ：参考 :ref:`floating-number` 一节

* 高级数据类型：
  
  * 基础数组 `[]`
  * std 字符串 `std::string`
  * std 数据类型，例如向量 `std::vector`\ 、映射 `std::map`\ 、数组 `std::array` 等，将在独立章节（:doc:`StdTypes`）中介绍

* 其他：
  
  * 空类型 `void`
  * 空指针类型 `nullptr`

.. hint::

    严格意义上说，以上并不全是“数据类型”。但本文在这一概念上不作纠缠。


.. _integral-type:

整型：整数与字符
-------------------------

在 C++ 中，整数与字符型可以统称为整型（Integral type）。而在狭义上，我们用整型来称呼整数类型（Integer type）。

.. csv-table:: C++ 的常用基础整型数据类型
   :header: "关键字", "类型", "最小位数"
   :widths: 40, 30, 20
   :width: 75%
   :align: center
   
   char,字符,8
   signed char,有符号字符,8
   unsigned char,无符号字符,8
   (signed) short,有符号短整数,16
   unsigned short,无符号短整数,16
   int/signed/signed int,有符号整数,16
   (signed) long,有符号长整数,32
   unsigned long,无符号长整数,32
   (signed) long long |cpp11|,有符号长长整数,64
   unsigned long long |cpp11|,无符号长长整数,64

.. admonition:: char 的特殊性
   :class: warning

   在 C++ 中，`char` 是一种特殊的类型，因为它的无符号或者有符号取决于编译器的具体实现。`char` 并不是 `unsigned char` 或者 `signed char` 其中某一个的别名，它们三个是\ **三种不同的类型**\ 。在现代 C++ 中，`char` 类型至少会覆盖 ASCII 字符。


size_t 类型
^^^^^^^^^^^^^^^^^^^^^^^^^^

现代 C++ 还定义了一种 ``std::size_t`` |cpp11| 类型（可以由头文件 ``<cstddef>`` 引入），它表示程序中最大允许的对象尺寸。如果某种对象的尺寸超过了 size_t 的上限值，那么这个程序是错误的。size_t 被规定为无符号整数，且至少应该有 16 位。

size_t 常常被用作循环变量类型。不过由于它是无符号的，因此在反向循环时的写法与传统的 int 反向循环的写法不同，具体请参考 :ref:`reverse-loop` 一节。


整型的操作符
^^^^^^^^^^^^^^^^^


整型字面值
^^^^^^^^^^^^^^^^^


关于宽字符与汉字*
^^^^^^^^^^^^^^^^^^

对于最常见的 UTF-8 编码，我们可以直接用字符型 ``char`` 来表示其数据。虽然每个 ``char`` 是单字节的，但是 ``std::string`` 类型（参见 :ref:`std-string` 一节）被设计为能够存储一系列 ``char`` 组成的多字节字符串。因此，我们可以直接使用 std::string 来存储汉字。


.. _bool-type:

布尔型
------------

布尔型 `bool` 可能是最简单的类型，它只允许真 ``true`` 或者假 ``false`` 两种值。例如：

.. code-block:: cpp
    :linenos:

    bool has_cat = false;
    unsigned int cats = 0;
    
    ++cats;
    has_cat = true;

布尔型对象可以使用与 ``&&``、或 ``||``、非 ``!`` 运算，并也能像数字运算那样用圆括号来分配优先级。

.. code-block:: cpp
    :linenos:

    bool x = false;
    bool y = true;

    bool r1 = x && y;  // false
    bool r2 = x || y;  // true
    bool r3 = !x;      // true

C++ 的逻辑运算是短路的。如果当前的逻辑运算结果已经能确定表达式的值，那么就不会计算后续的表达式。例如， ``x && y && r1 && r2`` 会在检查到 `x` 为 `false` 时就立刻停止。利用这一特性，我们可以“防御”一些非法语句被执行。下面是一个利用逻辑短路而不会在除数为 0 时进行计算的例子：

.. code-block:: cpp
    :linenos:

    int x = 2;
    int y = 0;

    bool r = (y != 0) && (x / y > 0);


.. _floating-number:

浮点数
-------------



.. _string:

字符串
-------------


.. _std-string:

std 字符串
^^^^^^^^^^^^^^^^
