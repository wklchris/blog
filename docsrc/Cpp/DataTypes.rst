常用数据类型
==============

本节介绍 C++ 的常见数据类型，包括：

* 基础数据类型：
  
  * :ref:`布尔型 bool <bool-type>` 与 :ref:`逻辑运算符 <bool-operator>`
  * :ref:`整型 <integral-type>` （如整数 `int` 与字符型 `char`）
  * :ref:`浮点数 double <floating-number>`

* 高级数据类型：
  
  * :ref:`其他数字类型 <other-number-types>` ，例如复数
  * :ref:`引用 & 与指针 * <reference-and-pointer>`
  * :ref:`基础数组 [] <basic-array>`
  * :ref:`字符串与 std::string <string>`
  * :ref:`枚举类 enum class <enum-class>`
  * :ref:`变体类型 std::variant <std-variant>` ，包括 union
  * :ref:`可选类型 std::optional <std-optional>`

* 其他相关内容：
  
  * :ref:`空类型 void <void-type>`
  * :ref:`运算符与比较符 <operator-and-comparator>` ，包括 :ref:`位运算符 <bitwise-operator>`
  * :ref:`常量 const 与常量表达式 constexpr <const-and-constexpr>`
  * :ref:`类型别名与推断 <type-aliases>` ，包括 using, typedef, auto 与 decltype

类（包括结构体）会在另外的 :doc:`Class` 章节中介绍。其他 std 数据类型，例如向量 `std::vector`\ 、映射 `std::map`\ 、数组 `std::array` 等，将在独立章节（:doc:`StdTypes`）中介绍。

.. hint::

    严格意义上说，以上并不全是“数据类型”。但本文在这一概念上不作纠缠。


.. _bool-type:

布尔型
------------

布尔型 `bool` 可能是最简单的类型，它只允许真 ``true`` 或者假 ``false`` 两种值。例如：

.. code-block:: cpp
    :linenos:

    bool has_cat = false;
    unsigned int cats = 0;
    
    cats = 1;
    has_cat = true;

其他类型在转换到布尔型时，一般在值为 0 或对象为空时表示逻辑假，其余情况表示逻辑真。

.. _bool-operator:

逻辑运算
^^^^^^^^^^^

布尔型对象可以使用与 ``&&``、或 ``||``、非 ``!`` 进行逻辑运算，并也能像数字运算那样用圆括号来分配优先级。

.. code-block:: cpp
    :linenos:

    bool x = false;
    bool y = true;

    bool r1 = x && y;  // false
    bool r2 = x || y;  // true
    bool r3 = !x;      // true

**C++ 的逻辑运算是短路的**\ 。如果当前的逻辑运算结果已经能确定表达式的值，那么就不会计算后续的表达式。例如， ``x && y && r1 && r2`` 会在检查到 `x` 为 `false` 时就立刻停止。利用这一特性，我们可以“防御”一些非法语句被执行。下面是一个利用逻辑短路而不会在除数为 0 时进行计算的例子：

.. code-block:: cpp
    :linenos:

    int x = 2;
    int y = 0;

    bool r = (y != 0) && (x / y > 0);


.. _integral-type:

整型：整数与字符
-------------------------

在 C++ 中，整数与字符型可以统称为整型（Integral type）。而在狭义上，我们用整型来称呼整数类型（Integer type）。下表列出了常见的整型类型；其中，数字的字面值标识符为后缀，字符的则为前缀。

.. csv-table:: C++ 的常用基础整型数据类型
   :header: "关键字", "类型", "最小位数 :superscript:`1`", "字面值前/后缀"
   :widths: 40, 30, 20, 20
   :width: 75%
   :align: center
   
   **字符型**,,,
   char,字符,8,
   signed char,有符号字符,8,
   unsigned char,无符号字符,8,
   char8_t |cpp20|,UTF-8 字符,固定 8,``u8``
   char16_t |cpp11|,UTF-16 字符,固定 16,``u``
   char32_t |cpp11|,UTF-32 字符,固定 32,``U``
   wchar_t,宽字符,/,``L``
   **整数型**
   (signed) short,有符号短整数,16,
   unsigned short,无符号短整数,16,
   int/signed/signed int,有符号整数,16,
   (signed) long,有符号长整数,32,``L`` 或 ``l``
   unsigned long,无符号长整数,32,``UL`` 或 ``ul``
   (signed) long long |cpp11|,有符号长长整数,64,``LL`` 或 ``ll``
   unsigned long long |cpp11|,无符号长长整数,64,``ULL`` 或 ``ull``

:superscript:`1` C++ 中的许多类型的具体位数取决于硬件，但最小位数是在所有硬件条件下均需满足的 C++ 标准。

例子：

.. code-block:: cpp

   int n1 = 12;
   unsigned long n2 = 1234;
   unsigned long n3 = 1234567UL;

C++ 还拥有一些定宽类型，例如 ``std::int8_t``\ , ``std::uint64_t`` 等。本文不介绍这些类型。

.. admonition:: char 的特殊性
   :class: warning

   在 C++ 中，`char` 是一种特殊的类型，因为它的无符号或者有符号取决于编译器的具体实现。`char` 并不是 `unsigned char` 或者 `signed char` 其中某一个的别名，它们三个是\ **三种不同的类型**\ 。在现代 C++ 中，`char` 类型至少会覆盖 ASCII 字符。


size_t 类型
^^^^^^^^^^^^^^^^^^^^^^^^^^

现代 C++ 还定义了一种 ``std::size_t`` |cpp11| 类型（可以由头文件 ``<cstddef>`` 引入），它表示程序中最大允许的对象尺寸。如果某种对象的尺寸超过了 size_t 的上限值，那么这个程序是错误的。size_t 被规定为无符号整数，且至少应该有 16 位。

size_t 常常被用作循环变量类型。不过由于它是无符号的，因此在反向循环时的写法与传统的 int 反向循环的写法不同，具体请参考 :ref:`reverse-loop` 一节。

不同数字进制
^^^^^^^^^^^^^^^

C++ 允许整数字面值通过前缀标识其进制，以 ``0b`` 开头是二进制，以 ``0`` 开头是八进制，以 ``0x`` 开头是十六进制。通过头文件 `<iomanip>` （或者更现代的 `<format>`\ ），我们可以方便地控制这些数字的打印：

.. literalinclude:: codes/math/number-base.cpp
   :linenos:
   :language: cpp

输出：

.. code-block::

   Dec: 63
   Hex: 63
   Oct: 63
   Binary: 63
   They are the same value.
   
   std::hex: 0x3f
   setbase(16): 0x3f
   std::format {:#x}: 0x3f
   std::format {:x}: 3f


.. _operator-and-comparator:

运算符与比较符
----------------

C++ 正常地使用四则运算符来进行加减乘除运算，也允许用圆括号来表示运算的优先级。类似地，C++ 也用大于、小于等数学比较符（也称关系符）来比较对象；如果比较关系成立则返回逻辑真（\ ``true``\ ），否则返回逻辑假（\ ``false``\ ）。关于逻辑运算或布尔型变量，参考 :ref:`bool-type` 一节。

C++ 的运算符和比较符如下：

.. csv-table:: C++ 运算符与比较符
   :header: "运算符", "名称", "示例", "结果"
   :widths: 30, 30, 30, 20
   :width: 75%
   :align: center
   
   **二元运算符**,,,
   `+`, 加, ``4 + 2``, 6
   `-`, 减, ``4 - 2``, 2
   `*`, 乘, ``4 * 2``, 8
   `/`, 除, ``4 / 2``, 2
   `%`, （整型）取余, ``7 % 2``, 1
   **一元运算符**,,,
   `-`, 负, ``-3``, -3
   `++`, （整型）递增, ``int x=2; ++x;``, 3
   `--`, （整型）递减, ``int x=2; --x;``, 1
   **二元比较符**,,,
   `>` 或 `>=`, 大于（等于）, ``3 >= 2``, `true`
   `<` 或 `<=`, 小于（等于）, ``2 < 1``, `false`
   `==`, 等于, ``2 == 2``, `true`
   `!=`, 不等于, ``3 != 2``, `true`

位运算符将稍后在本节中介绍（见 :ref:`bitwise-operator` 一节）。逻辑运算符并未收录在本表中，具体请参考 :ref:`bool-operator` 一节。

.. admonition:: 关于递增与递减运算
   :class: tip

   递增与递减运算有两种写法。一种是作为前缀 ``++i``\ ，另一种是作为后缀 ``i++``\ 。通常来说，如果情况允许，我们更倾向于使用前缀运算的写法。

   两种写法的区别在于将该表达式用作语句的一部分时，变量的值是在递增（减）之后还是之前参与到语句中。前缀运算会先进行递增或递减运算，然后返回值；而后缀运算则相反。以下是一个例子：

   .. literalinclude:: codes/operator/incr-prefix-suffix.cpp
      :linenos:
      :language: cpp
   
   其输出为：

   .. code-block:: console
      
      i = 0
      a = 1
      i = 1
      b = 1
      i = 2

   这种微妙的差异将会影响循环语句中的循环变量递增（正向遍历）或递减（反向遍历）的写法，请参考 :ref:`for-loop` 一节。


运算中的类型转换
^^^^^^^^^^^^^^^^^^

在 C++ 中，两个整数之间的运算结果仍然是整数，例如整数间的除法将舍弃掉小数部分。如果是一个整数与一个浮点数计算除法，则结果自动转为浮点数。

要将两个整数间的除法结果保留成小数，需要利用 ``static_cast<double>``\ ，显式地将被除数或者除数转换为浮点数类型。例如：

.. literalinclude:: codes/operator/type-convert.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 10

以上输出结果：

.. code-block:: console
  
   Int = 1
   Double / Int = 1.66667
   Int / Double = 1.66667

现代 C++ 建议使用 ``static_cast<double>(x)`` 代替传统的 C 风格 ``(double)x`` 写法，因为前者有更好的类型安全性。


.. _bitwise-operator:

位运算符*
^^^^^^^^^^^

**位运算**\ （Bitwise operation）是一种特殊的运算，它使用对象的计算机的二进制位数据来进行计算。

* 按位与： ``&`` ，依次按位进行二元逻辑与计算（双方均为 1 则结果为 1，否则结果为 0）
* 按位或： ``|`` ，依次按位进行二元逻辑或计算（双方均为 0 则结果为 0，否则结果为 1）
* 按位异或： ``~`` ，依次按位进行二元逻辑或计算（双方不同则结果为 1，否则结果为 0）
* 取反： ``~`` ，对所有位进行一元逻辑非计算（1 则 0，0 则 1）
* 左移与右移： ``<<`` 与 ``>>`` ，将所有的位向左或右移动若干位。左移时低位补 0，右移时高位补 0。

下面是上述位运算符的使用示例：

.. literalinclude:: codes/operator/bitwise.cpp
   :linenos:
   :language: cpp

我们得到：

.. code-block:: console
   
   x = 9, y = 5
   Bitwise AND: x & y = 1
   Bitwise OR : x | y = 13
   Bitwise XOR: x ^ y = 12
   Bitwise NOT: ~x = -10
   Left-shift : x << 1 = 18
   Right-shift: x >> 2 = 2

.. admonition:: 如何理解取反（`~`）的运算结果？
   :class: note
   
   要理解为什么 `9` （二进制 1001）的取反结果是 `-10`\ （而不是二进制 0110 即 6），我们必须了解计算机中的带符号整型是如何按二进制存储的。
   
   带符号整型的最高位为 0 时，表示存储正数；为 1 时，表示存储负数。以一个 8 位的整型类型为例，该类型一共能存储 :math:`2^8 = 256` 种数字。一般来说，其范围是从 -128 到 127 的每个整数。最高位为 0、后续位全为 1 的数（\ `0111 1111`\ ）表示该类型能存储的最大数，即 127。如果不考虑溢出，再尝试加 1时，会进位并改变最高位为 1，得到 `1000 0000`\ ，这也就是该类型能存储的最小数，即 -128。

   对于正二进制数，我们很容易将二进制数转为十进制，例如 `0000 0101` 就可以由按位累加 2 的幂得到 :math:`1\times 2^0 + 0\times 2^1 + 1\times 2^2 = 5`\ ，即 5。对于负二进制数，我们注意到 `1000 0000` 表示 -128；而 `1111 1111` 表示 0 之前的那个数，即 -1。那么，我们根据线性对应关系，可知\ :uline:`将负二进制数转为十进制的步骤是：先取反得到正二进制数，将该数字转为十进制，再加上 1，最后添加负号`\ 。

   例如，对于数字 9，其二进制表示中的低四位是 1001，再往上的高位全部是 0。现在以 8 位为例，即 `0000 1001`\ 。我们对它进行取反操作，得到 `1111 0110`\ 。由于最高位是 1，这是一个负二进制数。要将这个取反后的结果转为十进制，我们先将它取反转为十进制（重新得到 9）、再加 1（得到 10），最后添加符号（得到 -10）。因此，数字 9 的按位取反后会得到 -10。


.. _floating-number:

浮点数
-------------

C++ 的小数通常使用浮点数表示，分为单精度浮点数 ``float`` 与双精度浮点数 ``double`` 两种类型。

* 一般地，我们更多地使用 double 类型。单精度的有效位数大约是 7 位，而双精度大约是 15 位。
* 小数字面值默认是 double 类型的（例如 ``1.2``\ ）。如果需要，可以通过后缀 `f` 来将其变为 float 类型（例如 ``1.2f``\ ）。

通过引入 `<iomanip>` 头文件，我们可以使用 ``std::setprecision`` 来控制打印小数时的有效位数。如果还指定了 ``std::fixed``\ ，那么 ``std::setprecision`` 将指定小数位数而不是有效位数。利用 `<limits>` 头文件，我们可以打印（设备所能存储的）完整精度：

.. literalinclude:: codes/math/double.cpp
   :linenos:
   :language: cpp


.. _other-number-types:

其他数字类型*
----------------

除了整数与浮点数，C++ 还有一些数字类型，但并不常用：

* 复数：头文件 `<complex>` 提供了 ``std::complex`` 来表示数学上的复数。它用 ``real()`` 与 ``imag()`` 获取实部与虚部，并允许通过 ``std::complex_literals`` 命名空间来使用虚数后缀 ``i``\ 。C++ 中的复数与其他数字之间可以进行数学意义上的运算。  

  .. literalinclude:: codes/math/std-complex.cpp
     :linenos:
     :language: cpp
  
  输出：

  .. code-block::
     
     Complex number (3 + 4i) has norm: 5
     Complex number (5 + 12i) has norm: 13

* 编译期有理数：头文件 `<ratio>` 提供了 ``std::ratio`` 来计算有理数，例如 `std::ratio<1,3>` 表示 1/3 。它还提供了一些进位单位，如 ``std::kilo`` 表示千。它使用 ``::num`` 来获取分子、用 ``::den`` 获取分母。

  .. literalinclude:: codes/math/std-ratio.cpp
     :linenos:
     :language: cpp
  
  输出：

  .. code-block::
     
     Half: 1/2
     Result: 503/1000 = 0.503


.. _enum-class:

枚举类
-----------

C++ 提供了一种特殊的类，枚举类，用 ``enum class`` |cpp11| 来定义枚举数据。例如：

.. code-block:: cpp
   
   // 定义一个 AngleType 枚举类（锐角、直角与钝角）
   enum class AngleType { acute, right, obtuse };
   AngleType x = AngleType::acute;

* 在使用枚举类数据时，必须添加作用域前缀，如上例中的 ``AngleType::``\ 。在名称无冲突时，我们可以使用 ``using enum`` |cpp20| 来省略作用域前缀。
  
  .. note::

     传统 C++ 还提供了一种不带 class 的枚举 ``enum`` 数据类型，它在使用时不需要作用域前缀。但是，这显然增加了名字冲突的风险，因此现代 C++ 中推荐使用 enum class 代替它。

* 枚举类实际上是将每一种数据存储为整型（从 0 开始递增），因此可以将它与整型之间进行转换。
* 在实践中，有时候会把枚举类的最后一个数据设置为 `size`\ ，以此获取枚举总数。

枚举类默认提供了一些操作符，例如等于比较符 ``==``\ ，不过我们可以像正常的类一样为枚举类定义其他的操作符（参考 :ref:`class-operator` 一节）。下例定义了一个交通信号灯的枚举类，并用 ``++`` 递增操作符来切换红绿灯到下一个状态。

.. literalinclude:: codes/class/enum-class.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 9

输出：

.. code-block:: console

   Light is green
   Now light is yellow


.. _void-type:

空类型
----------

空类型 ``void`` 在用作函数的返回类型时，表示该函数不返回实际数据。对于一个 `void` 函数，我们不需要在最后添加 `return` 语句。例如，一个简单的打印函数不用返回任何数据：

.. code-block:: cpp
   :linenos:
   
   // #include <iostream>
   void print_hello() {
       std::cout << "Hello" << std::endl;
   }

如果需要在一个 `void` 函数的中间中止函数，使用一条 ``return;`` 语句即可。


.. _const-and-constexpr:

常量与常量表达式
-----------------------------

在 :ref:`variable-declaration` 一节中，我们简单介绍了变量的用法。C++ 还支持定义一种不可变的对象，也就是\ **常量**\ （Const）。除了 ``const`` 关键字，我们还可以使用 ``constexpr`` |cpp11| 关键字，也即\ **常量表达式**\ （Const expression）。

常量的概念与科学中的常数类似，例如，圆周率 :math:`\pi` 的值是固定的，因此能以一定的精度定义为一个浮点型常量。

.. code-block:: cpp
   
   const double pi = 3.1415926535;
   constexpr double e = 2.718281828;

.. hint::

   `const` 与 `constexpr` 常量在声明时都必须显式地初始化它的值。这在语法上是合理的，因为常量在概念上就会固定在创建时的状态，禁止在之后的任何情况下对其进行赋值。

其中，\ `constexpr` 常量也称编译时（compile-time）常量，即在代码编译时就能确定值的常量。而 `const` 常量则可以放宽要求，允许在代码运行后才确定数值，因此叫运行时（runtime）常量。科学意义上的常数可以直接给出（在一定精度上近似的）浮点数值，因此不依赖于运行任何代码的运行，它们也就都可以定义为编译时常量。

除了直接给出数值，我们也可以使用常规函数的返回结果来定义一个 `const` 常量。但对于 `constexpr` 常量的定义，它还要求函数必须是由 ``constexpr`` 或 ``consteval`` 关键字修饰的函数。

* `constexpr` 函数必须是纯函数（Pure function），也就是说，它的运行结果只取决于传入的参数，而不取决于其他外部状态（如全局变量等函数外部的非常量对象）；同时，除了返回值，它们也不影响任何外部状态（如 I/O 操作）。
* 一个 `constexpr` 函数可以在运行时被调用，例如赋值给某个变量或者 `const` 常量，这是为了避免我们为同一个函数定义普通与 `constexpr` 两个版本。如果要禁止函数在运行时被调用，只允许它在编译时被调用，那么使用 ``consteval`` 关键字来代替。

例子：

.. literalinclude:: codes/function/func_constexpr.cpp
   :linenos:
   :language: cpp

输出结果为：

.. code-block:: console

   Area 1 = 3.14159
   Area 2 = 12.5664

最后， `const`关键字还常常用于在为函数传入参数时指定参数为常量，表示该函数不会修改传入的参数；或者用于修饰类的成员函数，表示该成员函数不会修改调用它的类对象（参考 :doc:`Class` 一节）。最常见的用法就是传入常量引用，例如 ``func(const std::array<int>&)``\ ，它是一种对较大参数的高效传递。关于引用，参考 :ref:`reference-and-pointer` 一节。

.. _basic-array:

基础数组
--------------

.. important::

   现代 C++ 中更多地使用标准库提供的 std 数组（参考 :ref:`std-array` 一节）来代替基础数组，因为 C++ 为这类标准容器实现了一系列实用的功能。

C++ 中使用 ``[]`` 来表示基础数组（或称原生数组、裸数组），即连续分配的一组同类型元素。基础数组在声明时必须指定数组的长度，且该长度必须是常数表达式（编译时常量）。例如：

.. code-block:: cpp
   
   // 声明一个长度为 3 的、元素为 char 类型的数组
   char arr1[3];
   // 定义一个元素为 1、3 的数组（长度自动设为 2）
   int arr2[] = {1, 3};

C++ 的基础数组（以及其他顺序容器）的下标从 0 开始。例如，对于一个长度 3 的数组 ``arr``，它含有的元素是 ``arr[0], arr[1], arr[2]`` 。


.. _string:

字符串
-------------

本节只是简单地介绍字符串类型。更多的字符串操作内容，参考 :doc:`StringAndIO` 一节。

字符串字面值
^^^^^^^^^^^^^^^^^

C++ 的字符串字面值用一对双引号包围，以与单个字符的单引号区分。字符串字面值使用与字符类似的前缀，并支持 ``s`` 与 ``sv`` 两种后缀：

.. csv-table:: 字符串字面值前缀/后缀表
   :header: "前缀/后缀", "名称", "类型", "示例"
   :widths: 20, 40, 50, 40
   :width: 75%
   :align: center

   (无), `const char[]`\ , 基础字符串, ``"hello"``
   **前缀**,,,
   u8 :superscript:`1` , `const char8_t[]` |cpp20| , UTF-8 字符串, ``u8"hello"``
   u, `const char16_t[]`\ , UTF-16 字符串, ``u"hello"``
   U, `const char32_t[]`\ , UTF-32 字符串, ``U"hello"``
   L, `const wchar_t[]`\ , 宽字符串, ``L"hello"``
   **后缀**,,,
   s, `std::string` |cpp14| , std 字符串后缀, ``"hello"s``
   sv, `std::string_view` |cpp17| , std 字符串视图后缀, ``"hello"sv``

:superscript:`1` 在 C++ 20 之前， ``u8`` 字符串的类型与基础字符串相同，即 `const char[]`\ 。

字符串还有一种特殊的以 ``R`` 开头的原始字符串语法，请参考 :ref:`R-string` 一节。

.. _std-string-basic:

std 字符串
^^^^^^^^^^^^^^^^

C++ 标准库的字符串 ``std::string`` 通过头文件 `<string>` 引入。下文中如果不特殊说明，字符串均指 `std::string`` 字符串，而不是 C 风格的字符串。

* std 字符串的长度可通过 ``.size()`` 或者 ``.length()`` 的方式获得。
* std 字符串使用类似数组的下标方式，其中元素的类型为 `char`\ ，例如 ``s[0]`` 表示取字符串 s 的第一个字符。同样类似数组，请在使用下标前检查字符串是否为空，并确保下标没有越界。
  
  .. code-block:: cpp
     
     std::string s = "Hello";
     if (!std.empty()) {
        std::cout << "First character is: " << s[0] << std::endl;
     }

C++ 字符串拥有非常多的操作函数，例如判空 ``empty()``\ 、取子字符串 ``substr``\ 、查询 ``find``\ 、替换 ``replace``\ 等。这些内容会在 :doc:`StringAndIO` 章节中介绍。


.. _wide-character:

关于宽字符与汉字*
^^^^^^^^^^^^^^^^^^

对于最常见的 UTF-8 编码，我们可以直接用字符型 ``char`` 来表示其数据。虽然每个 ``char`` 是单字节的，但是 ``std::string`` 类型（参见 :ref:`std-string-basic` 一节）被设计为能够存储一系列 ``char`` 组成的多字节字符串。因此，我们可以直接使用 std::string 来存储汉字（但字符串的长度失去意义，因为它计算字节数量而不是字符数量；打印时也不能从单个汉字的中间断开，否则会乱码）。

.. warning::

   在 C++ 17 及之前， ``u8`` 前缀的字符串字面值的每个元素是 `char` 类型的，因此可以直接用于初始化 `std::string`\ 。但在随后的 C++ 20 中，这类字符串字面值中的字符类型变为了 `char8_t`\ , 以与引入的新 UTF-8 字符串类型 `std::u8string`\ 相统一。相比于 `std::string` 的本质是 ``std::basic_string<char>``\ ，新的 `std::u8string` 在本质上是 ``std::basic_string<char8_t>``\ 。

一个 `std::string`\ 与 `std::u8string` |cpp20| 的用法示例。由于 `std::cout` 不能直接输出 `u8string`\ ，需要通过 ``reinterpret_cast`` 将它转换为普通的字符串字面值类型（\ `const char*`\ ）：

.. literalinclude:: codes/string/u8string.cpp
   :linenos:
   :language: cpp

汉字在使用 UTF-8 编码时可能占 3 个字节（但也可能不是），因此在打印时从中间断开会可能会导致乱码。上例的输出为：

.. code-block::

   std字串, string size: 9
   你好，世界！, string size: 18
   u8字串, u8string size: 8
   -s-t-d-�-�-�-�-�-�
   -字-串

此外，C++ 曾经使用过一段时间的宽字符 `wchar_t` 相关的类型，但并不是一种通用性强的方法（因为大部分的字符串操作都基于 std::string 类型）。头文件 `<codecvt>` 在 C++ 20 及之后也进入弃用状态，后续的 C++ 版本可能更依赖于头文件 `<locale>` 的功能。

总之，宽字符编码与处理在 C++ 中是一个复杂的工作。连简单的字符计数都会变得复杂，更不用提检索字符等其他操作了。C++ 在这方面有许多历史包袱，而显然 `u8string` 还不够成熟，也不能代替 `string`\ 。在 C++ 23 中，``std::print`` 被引入并支持了 `u8string` 的打印，但仅仅这种程度的支持是微不足道的。我推荐：

* 总是使用 UTF-8 编码。这可能需要调整系统命令行窗口的设置，让它以 UTF-8 模式工作（而不是 GBK）。
* 在试验性或小型项目中，如果不需要复杂的字符串操作，那就简单地使用 `std::string` 来存储宽字符。
* 在大型项目中，使用支持 UTF-8 的第三方字符库（如 `ICU`\ ）。或者使用框架库自带的字符串类型（如果有），比如 Qt 库的 `QString` 类型。


.. _reference-and-pointer:

引用与指针
--------------

**引用**\ （Reference）在 C++ 中是一种特殊的概念，可以将一个名字与对象绑定。我们用 ``&`` 加名字来定义一个引用，例如：

.. literalinclude:: codes/ref-and-ptr/ref.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 5

以上会输出：

.. code-block:: console

   x (&r) = A
   x = B
   x (&r) = Z

引用的特点：

* **引用不是对象**\ ，它只是被引用对象的自定义名字。
* 引用必须在定义时初始化它要绑定的对象，且不能再更改绑定到新的对象。
* 引用一般需要绑定到同类型对象。特别地，允许常量引用（参考 :ref:`constant-reference` 一节）绑定到能转换为该类型的对象或字面值；定义基类引用时，也允许绑定到该类的派生类对象。

利用引用的特性，我们可以在向函数传递参数时使用引用，以将函数内的修改传递到函数外：

.. literalinclude:: codes/function/func_arg_ref.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 3

以上输出会显示变量 ``a`` 的值被改变了：

.. code-block:: console

   a = -1
   b = 5.6

.. _constant-reference:

常量引用
^^^^^^^^^^^^^^

常量引用是一个容易误解的概念。常量引用是指“\ **不能通过它修改被引对象的一种引用**\ ”，而不是指“被引对象是常量的一种引用”。换言之，常量引用只是提供一种“常量视图”，而不要求被引对象本身是常量。它可以被绑定到可以被转为该类型的任意对象（变量、常量或者字面量）。

.. literalinclude:: codes/ref-and-ptr/ref-const.cpp
   :linenos:
   :language: cpp

如果被引对象的值发生了变化，那么通过引用访问它得到的值当然也会随之变化。上例将给出输出：

.. code-block:: console

   const &rx = 3
   x = 4
   const &rx = 4

在向函数传递参数时，使用常量引用（如 ``const std::vector<int>&``），可以提供一个“常量视图”，以防止函数对实际对象进行更改。那为什么不直接传入值（如 ``std::vector<int>``）呢？这是因为传值的本质是将原对象复制为一个（只能在当前函数作用域中使用的）副本，而对大型对象进行复制是低效的。使用常量引用避免了复制的性能开销，同时提供了对被引对象的访问能力，也保护其在函数内不被修改。

.. _basic-pointer:

基础指针*
^^^^^^^^^^^^

.. important::

   现代 C++ 中提倡用智能指针 |cpp11| （\ `std::unique_ptr` , `std::shared_ptr` 等）来更安全地管理指针，而不是直接使用基础指针。

**指针**\ （Pointer）是 C++ 最有代表的概念之一。它像引用一样，提供了一种访问其他对象方式。不同的是，指针确实是一个对象，存储了所指对象的内存地址，也允许赋值、复制等操作。

基础指针（或称原生指针、裸指针）使用 ``*`` 加上指针名称来声明。初始化基础指针可以让它指向一个对象（利用 ``&`` 取地址符），或者让指针指向空指针 ``nullptr`` |cpp11| （代替了传统 C++ 中使用的 ``NULL``\ ）。

.. admonition:: 符号 `&` 与 `*` 的含义
   :class: hint

   在 C++ 引用与指针的相关语法中，符号 ``&`` 通常表示“取地址”（对应引用的概念），例如 ``&r`` 表示获取 `r` 在内存中的地址位置。相对地，符号 ``*`` 通常表示“取内容”（或者叫“解引用”，对应指针的概念），例如 ``*p`` 表示获取 `p` 指向的地址中存放的数据内容。

我们不会过多地介绍基础指针的内容，而是尽快地进入到智能指针章节。这里给出一个基础指针的例子：

.. literalinclude:: codes/ref-and-ptr/ptr.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 8, 15, 20

它的输出结果如下。其中，指针 p 的值是一个地址，因此每次运行都可能不同：

.. code-block:: console

   *p = 1.23, p = 0xffddff6e8
   *p = 4.56, x = 4.56
   *p = 7.89

指针的语法在初次接触时可能觉得比较复杂。在对指针或其所指变量进行赋值时，请牢记：

* 对解引用的指针 `*p` 进行赋值（如 ``*p = 1.0``\ ），等于对指针 `p` 所指对象进行赋值；指针仍然指向那个对象。
* 对指针 `p` 进行赋值（如 ``p = &y``\ ），等于更改指针 `p` 中存放的地址，即让指针指向一个新的对象。

最后，对无效指针进行操作是危险的，可能引发未定义行为。因此，在实践中，我们建议：

* 总是显式地初始化指针。如果暂时不知道它要指向的对象，那么就用 ``nullptr`` 来初始化指针。
* 在指针操作前（例如解指针 ``*p``），总是先检查指针的有效性（使用 ``if (p == nullptr)``\ 或等价的 ``if (p)``\ ）。

.. _pointer-and-const:

指针与常量
^^^^^^^^^^^^^^^^^^

.. warning::

   请注意，指针所指对象的“常量”性质，仅仅代表该对象不能通过指针被修改，而不是说“指针指向的是一个（C++语法意义上的）常量”。

指针比引用更复杂的地方在于常量性质。由于指针本身是一个对象，因此关于指针有两种常量修饰：

* *顶层常量*\ ：指针本身是一个常量（固定地指向某个对象），而它指向的对象的值可以通过指针修改。这种指针叫\ **常量指针**\ （Constant pointer），形如 ``int* const``\ 。
* *底层常量*\ ：指针所指的对象的值不能通过指针修改，而指针本身不一定是常量（可以改为指向其他对象）。这种指针叫\ **指针常量**\ （Pointer to const），形如 ``const int*``\ 。

如果我们整合它们，还能得到第三种指针，也就是 *指向常量的常量指针* ，即 ``const int* const``\ 。这种指针固定地指向某个对象，且不允许通过解指针来更改这个对象的值。

.. admonition:: 如何阅读声明指针时使用的类型？
   :class: hint

   C++ 在声明时使用的类型大多遵循 *从右向左* 的阅读原则，例如：

   * ``int* p``\ ：声明 ``x``\ ，它是一个指针（\ ``*``\ ），指向类型 ``int``\ 。
   * ``int* const p``\ ：声明 ``x``\ ，它是一个常量（\ ``const``\ ）的指针 ``*``\ ，也即一个常量指针。它指向类型 ``int``\ 。
   * ``const int* p``\ ：声明 ``x``\ ，它是一个指针 ``*``\ ，指向类型 ``int`` 的“常量”（不可通过指针修改）。

下面是一个例子：

.. literalinclude:: codes/ref-and-ptr/ptr-const.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 8, 10, 14, 22

它的输出如下：

.. code-block:: cpp

   *p1 = 15
   *p2 = 23 (Initial)
   *p2 = 16

.. _pointer-to-member:

成员指针*
^^^^^^^^^^^^^

在 C++ 语法中，使用类似 ``&MyClass::data`` 的形式表示 `MyClass` 类的指向该类 `data` 成员的\ **成员指针**\ （Pointer to member）。尽管以 ``&`` 开头，但它并不是引用，也不像普通指针一样指向一个实际地址。成员指针实际上指向成员对象的相对偏移量，并以此访问类对象的该成员。

成员指针在定义时，类型名中需要含有作用域运算符（此处是 `MyClass::`\ ）来指定指针的类型与该类相关：

.. literalinclude:: codes/ref-and-ptr/ptr-member.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 11-12

一般来说，我们不像这样直接使用成员指针。不过在用 `std::ranges::find` 检索容器的元素时，我们会使用到它（参考 :ref:`std-ranges-find` 一节）。


.. _type-aliases:

类型别名与推断
-----------------

C++ 中大致有以下类型别名和推断方法：

* 别名：using（以及 typedef）
* 推断：auto 或 decltype

using 类型别名
^^^^^^^^^^^^^^^^^^^

``using`` 关键字在 C++ 中历史悠久，但提供类型别名 |cpp11| 的功能是从 C++ 11 开始的。以下是一个例子：

.. code-block:: cpp
   :linenos:

   using ages = int;     // 将 ages 定义为 int 的别名
   ages person_age = 24;

.. hint::

   C++ 还提供了 ``typedef`` 来自定义类型名，用法如 ``typedef int ages;`` 但这里不再推荐这种用法。由于 `using` 完全覆盖了 `typedef` 的使用情景，并且还能用在一些后者无法使用的地方（比如模板别名），因此建议总是使用 `using`\ 。


auto 关键字
^^^^^^^^^^^^^^^^

现代 C++ 允许使用 ``auto`` |cpp11| 来在变量定义时自动推断类型。例如，``2`` 是 `int` 类型， ``2.718`` 是 `double` 类型：

.. code-block:: cpp
   :linenos:

   auto x = 2;        // int
   auto y = 2.718;    // double
   auto z = x + y;    // double
   auto s = "Hello";  // const char*

在一般的场合，我们应当在定义时直接写出类型全名来提供较好的可读性，也避免推断的类型不符合预期。例如，我们可能希望上例中的字符串变量类型为 ``std::string`` 而不是 ``cosnt char*``\ 。

auto 的一种使用场合是在类型全名太长时，这时反而使用 auto 会获得更好的可读性。另一种常用的情况是要定义的变量类型是显然的（或者不重要的），例如在 for 循环中使用 auto 来定义循环变量。 

decltype*
^^^^^^^^^^^^^

现代 C++ 允许使用 ``decltype`` 来“借用”已有对象的类型。比较特殊的是，它会保留引用类型以及顶层常量属性。

.. code-block:: cpp
   :linenos:

   const int m = 12, &r = m;
   decltype(n) n1 = 0;     // 推断为 const int
   decltype(r) r1 = m;     // 推断为 const int& 引用
   
   int n = 37, *p = &n;
   decltype(*p) r2 = n;    // 解引用后，推断为 int& 引用


.. _std-variant:

变体（std::variant）与 union 类型*
------------------------------------------

.. hint::

   现代 C++ 使用 ``std::variant`` |cpp17| 代替传统的 ``union`` 类型。

传统 C++ 支持 ``union`` 类型，能够存储指定的多种类型中的一种，以此节省空间占用。例如：

.. code-block:: cpp

   union NumberUnion {
       int val_int;
       double val_double;
   };

由于它不包含类型信息，这种设计需要配合一层额外的包装来存储类型信息，就像：

.. code-block:: cpp
   
   enum class NumberType { Int, Double };
   struct Number {
       NumberType t;
       NumberUnion u;
   };

   // 在使用时
   Number n {NumberType::Int, 123};
   if (n.t == NumberType::Int) {
       std::cout << n.u.val_int << // ...
   }

可以看到，直接使用 union 的管理方式十分复杂，而且容易出错。作为替代，现代 C++ 的头文件 `<variant>` 引入了变体 ``std::variant`` |cpp17| ，它写法更简单。同时，也允许使用 ``std::holds_alternative`` 来检查变体的具体类型，并用 ``std::get`` 来获取对应类型的数据。

下面是一个变体代码示例，它定义了一个 Shape 变体以存储三角形、矩形或者圆这三种图形之中的一种。在函数 ``calcShapeArea`` 中，我们为每一种图形类型提供了一个匿名函数入口（参考 :ref:`lambda-function` 一节）。配合定义的 ``overloaded`` 模板类（参考 :doc:`Template` 章节），C++ 会通过 ``std::visit`` 自动寻找当前图形类型对应的面积计算函数来进行调用。之后在 for 循环中打印图形面积时，我们换用了另一种写法，即使用 ``std::holds_alternative`` 与 ``std::get`` 来检查与取得图形数据并打印信息。

.. literalinclude:: codes/alternative/std-variant.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 10, 13-15, 19-26, 40-41 

以上代码将输出：

.. code-block:: console

   Area of circle (1) = 3.14159
   Area of triangle (3,4,5) = 6
   Area of rectangle (2,3) = 6

最后，C++ 的头文件 `<any>` 还提供了一种 ``std::any`` 类型，用于存储任何类型的数据（在概念上类似于一个包含所有类型的 `std::variant` 对象），并允许通过 ``any_cast<T>`` 函数来将 `any` 类型的对象转为 `T` 类型。它的应用场景较少，这里不做介绍。


.. _std-optional:

可选（std::optional）类型*
----------------------------------

可选类型 ``std::optional`` |cpp17| 由头文件 `<optional>` 引入，它相当于一个指针，要么指向某一种给定的类型，要么是空对象 `std::nullopt`\ （或者使用一对空的花括号）。

可选类型在检索查询时可能用到。下面是一个例子，按照给定的首字母来检索：

.. literalinclude:: codes/alternative/std-optional.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 7, 13, 19-20

请注意，在 `std::optional` 对象含有数据时，我们需要解指针（\ ``*fruit``\ ）来获取数据。上例的输出为：

.. code-block:: cpp

   Fruit with initial letter 'a' is found: apple
   Fruit with initial letter 'c' is NOT found
   Found fruit: peach
