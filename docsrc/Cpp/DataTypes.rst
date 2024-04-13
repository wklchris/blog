常用数据类型
===================

本节（以及 :doc:`DataTypesAdvance` ）介绍 C++ 中的常用数据类型。它们包括：

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


转义字符
^^^^^^^^^^^^^

含有特殊含义的字符无法直接使用，必须进行转义，例如换行符用 ``'\n'`` 表示。C++ 规定了以下转义字符：

.. csv-table:: C++ 转义字符
    :header: "转义字符", "含义", "转义字符", "含义", "转义字符", "含义"
    :widths: 20, 30, 20, 30, 20, 30
    :width: 75%
    :align: center

    \\n, 换行, \\t, 横向制表, \\v, 纵向制表
    \\b, 退格, \\r, 回车, \\f, 进纸
    \\', 单引号, \\", 双引号, \\?, 问号
    \\\ \\, 反斜线, \\a, 响铃

* 转义字符被视为单个字符。
* 广义转义字符：使用 ``\x`` 前缀加 16 进制数字，或者使用反斜线 ``\`` 加不超过 3 位的 8 进制数字组成：
  
  .. code-block:: c++

     '\101'    // 字符 A
     '\x41'    // 字符 A
     "\102\12" // 字符串 "B\n"


特殊字符与 Unicode*
^^^^^^^^^^^^^^^^^^^^^

.. note::

    C++ 的宽字符 ``wchar_t`` 类型与宽字符串 ``std::wstring`` 类型通用性并不强，或者在跨平台时需要复杂的打印技巧（比如专用的打印函数或者 C 风格的 ``printf``），因此我不推荐使用。如果只需要对字符串进行打印、而不涉及到截取等字符串操作，那么我推荐直接使用简单的 ``std::string``\ 。

    关于字符串的基础用法，参考 :ref:`string` 一节。

我们首先看一个不那么标准的、懒人的办法，即照常使用 ``std::string`` 来存储含特殊字符的字符串，并使用 Unicode 编码来代表字符。但是，这样的存储方式 **可能会使字符串的长度不等于预期**\ ，因为单个特殊字符需要的存储长度可能大于 char 类型的长度。

下面是一个 Windows 平台的示例，使用了 ``Windows.h`` 的 ``SetConsoleOutputCP()`` 来启用控制台编码支持，其中 ``CP_UTF8`` 实质上就是 65001：

* 如果 Unicode 字符的十六进制码不超过 4 位，使用 ``\u`` 转义前缀
* 如果 Unicode 字符的十六进制码超过 4 位，在其左侧补 0 直到 8 位，然后使用 ``\U`` 转义前缀，

.. literalinclude:: codes/print_unicode.cpp
    :linenos:
    :language: c++

.. admonition:: 不推荐直接在代码文件中粘贴特殊字符
    :class: warning

    在 C++ 中，最简单的使用特殊字符的方式是直接书写为字符串字面值（并建议指明 ``u8``），但是这种方法是不推荐的！

    .. code-block:: c++

        // 不推荐！
        std::string cc = u8"你好，世界！";
        std::cout << cc << std::endl;
    
    不推荐的原因是它不稳定：

    * 你的特殊符号被如何存储，取决于该代码文件的编码（甚至 BOM）。
    * 他人阅读代码时，其设备上可能没有配置能正确显示特殊符号的环境。

      * 即使能够正常显示，这种阅读也是不可靠的。因为许多符号看起来难以察觉到它们的不同，甚至同一显示符号可能对应不同的 Unicode 码。

    * 编译器有不能恰当地处理这种文件的风险。
    * 在不同环境（例如不同系统平台上）的编译结果可能不同。

一个从理论上来说更好的方法是使用 ``std::wstring``\ ，因为它可以正确地存储符号、不会显示错误的字符串长度；但它的打印方法在 Windows 上可能十分繁琐：

.. literalinclude:: codes/print_unicode_wstring.cpp
    :linenos:
    :language: c++

在某些环境下，也可以利用 ``<codecvt>`` 与 ``<locale>`` 标准库将 wstring（或者 u16string, u32string）转为 UTF-8 字符串然后打印。


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


空类型：void
--------------

空类型常用于无需返回值的函数定义中。下例中，函数只执行打印而不返回结果，因此定义为 ``void`` 类型：

.. code-block:: c++

    #include <iostream>

    void print_char_twice(char c) {
        std::cout << c << c << std::endl;
    }

    int main() {
        print_char_twice('a');
        return 0;
    }

void 也用在指针类型中，参考 :ref:`void-pointer` 一节。
