常用数据类型
===================

本节介绍 C++ 中的常用数据类型。它们包括：

* 内置字面值：空指针（nullptr）
* 内置变量类型：
  
  * 算术类型：整型（整数、字符型、布尔型）与浮点数。
  * 空类型（void）

* 标准库支持的变量类型：例如字符串（\ ``std::string``\ ）。
* 标准库支持的模板类型：例如向量（\ ``std::vector``\ ）。

关于指针与引用，请参考 :doc:`PointerAndRef` 一节的内容。


整型：布尔、字符、整数
------------------------

C++ 规定了多种类型的最小尺寸（同时允许编译器赋予更大的尺寸），详见下表：

* 布尔型：只允许 ``true`` 与 ``false`` 两种取值。
* 下例中的长整型或长长整型的后缀也可以使用小写字母 l 代替大写 L，但不推荐。

.. _integral_type_size:

.. csv-table:: C++ 整型尺寸
    :header: "关键字", "类型", "最小尺寸", "前后缀"
    :widths: 20, 30, 40, 20
    :width: 70%
    :align: center

    bool, 布尔型, /,
    **字符型**,,,
    char, 字符, 8 位, u8 前缀（仅字面）
    wchar_t, 宽字符, 16 位, L 前缀
    char16_t, Unicode 16 字符, 16 位, u 前缀
    char32_t, Unicode 32 字符, 32 位, U 前缀
    **整数**,,,
    short, 短整型, 16 位,
    int, 整型, 16 位（>= short）,
    long, 长整型, 32 位（>= int）,L 后缀
    long long |cpp11| , 长长整型, 64 位（>= long）,LL 后缀


无符号整型
^^^^^^^^^^^^^^

除了布尔与扩展字符之外的整型，可以划分为带符号（正、负或0）与无符号（不小于0）两种。

* 整数类型（short, int, long 与 long long）均是带符号的，在前加 ``unsigned`` 可以得到对应的无符号类型。
  
  * 无符号整数 ``unsigned int`` 可以直接简写为 ``unsigned``
  * 无符号整数后缀 ``u/U`` 可以与长整型后缀 ``L`` 或 ``LL`` 结合，例如 ``uL`` 表示无符号长整型。

* 字符型（char）分为 char, signed char 与 unsigned char 三种，但实际上只会表现为后两种。
  
  * char 类型会表现为带符号或无符号这两种中的一种，具体由编译器决定。


.. admonition:: C++ 的整型类型选择
    :class: tip

    * 数值非负时，选用 ``unsigned`` 类型
    * 如果整数超出了 ``int`` 范围，换用 ``long long`` 类型
    * **不要混用无符号与带符号类型进行算术计算**
      
      * 不要用 char 参与算术计算，因为 char 是无符号的还是带符号的取决于编译器


位数取值范围*
^^^^^^^^^^^^^^^^^^^^

各位数对应的取值范围：

.. csv-table:: 位数取值范围
    :header: "位数", "取值范围", "最小尺寸类型"
    :widths: 20, 40, 40
    :width: 60%
    :align: center

    16 位, -32768 ~ 32767（带符号）, short
         , 0 ~ 65535（无符号）, unsigned short
    32 位, ±2.147x10^9（带符号）, long
        , 0 ~ 4.294x10^9（无符号）, unsigned long
    64 位, ±9.223x10^18（带符号）, long long |cpp11|
         , 0~1.844x10^19（无符号）, unsigned long long

通过 ``<limits>`` 库的 ``numeric_limits<T>`` 模板及其成员，我们可以查看（在当前设备环境下的）数值类型的值占用位数、取值上限与取值下限：

* ``std::numeric_limits<T>::digits``\ ：类型 T 的值占用位数（带符号类型将减去符号位）
* ``std::numeric_limits<T>::lowest()``\ ：类型 T 的取值下限
* ``std::numeric_limits<T>::max()``\ ：类型 T 的取值上限

.. warning::

    请注意，以下取值范围只适用于编译该代码时的设备环境。以下结果仅表示，:uline:`在此时的编译环境下` int 类型是 32 位的。

.. literalinclude:: codes/std_numeric_limits.cpp
    :linenos:
    :language: c++


整型字面值
^^^^^^^^^^^^^^^

结合 :ref:`integral_type_size` 表中的前、后缀内容，我们给出一些整型字面值的例子：

.. code-block:: c++

    u8"abc"     // UTF-8 字符型字符串 "abc"
    u'x'        // Unicode 16 字符 'x'
    -12L        // 长整型数 -12
    13579ULL    // 无符号长长整型数 13579


此外，八进制（前缀 0）或者十六进制（前缀 0x）的数也可以用前缀标识：

.. code-block:: c++

    20      // 普通十进制数
    012     // 八进制数，前缀 0
    0x2f    // 十六进制数，前缀 0x


浮点数
------------

我们\ **通常使用双精度浮点数（double）**\ 而不是 float，因为 float 精度通常不足而双精度的计算效率并不明显低（甚至有时候更快）。

* 浮点数同样有无符号类型，例如 ``unsigned double``

.. _float_type_size:

.. csv-table:: C++ 浮点数尺寸
    :header: "关键字", "类型", "最小尺寸", "前后缀"
    :widths: 20, 30, 40, 20
    :width: 70%
    :align: center

    float, 单精度浮点数, 6 位有效数字, 后缀 f/F
    double, 双精度浮点数, 10 位有效数字,
    long double, 扩展精度浮点数, 10 位有效数字, 后缀 L


浮点数字面值
^^^^^^^^^^^^^^^

* 浮点数字面值允许科学记数法，使用字母 ``e`` 或 ``E``
* 如同整数一样，浮点数允许无符号后缀 ``u/U`` 

结合 :ref:`float_type_size` 表中的内容，例子：

.. code-block:: c++

    1.2e3f          // 单精度浮点数 1.2 x 10^3
    3.1415926L      // 扩展精度浮点数 3.1415926
    2.718uL         // 无符号扩展精度浮点数 2.718


.. _std-vector:

向量（std::vector）
-----------------------


