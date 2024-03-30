控制流语句
===============

C++ 的控制流语句包括：

* 循环语句
* 条件语句
* 跳转语句
* 异常处理语句


循环语句：for 与 while
-------------------------------------

C++ 循环语句可以分为 for 与 while 两大类：

* **for 循环**\ ：最常用的循环体，常用于已知循环次数（或循环迭代对象）的情形。
  
  * 常规 for 循环：控制循环变量的变化，以此来完成给定次数的循环。
  * 范围 for 循环 |cpp11| ：允许指定迭代对象来进行循环，而不用显式地指明循环次数。

* **while 循环**\ ：循环次数未知，或要在循环体之后使用循环变量。
  
  * do..while 循环：与 while 类似，用于循环体无论如何也要执行一次的情形。


常规 for 循环
^^^^^^^^^^^^^^^^^^

* for 循环的循环头包含三个部分：初始化语句、循环条件，以及表达式。
* 初始化语句中的对象 **在离开 for 循环之后不可使用** 。

下例将从 0 到 3 的整数累加：

.. literalinclude:: codes/control_for.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 7-9

C++ 中循环体如果只包含一条语句，可以不放在花括号内。例如：

.. code-block:: c++

    for (int k = 0; k < 4; ++k) s +=k;
    for (int j = 0; j < 10; ++j) ;  // 空语句


范围 for 循环
^^^^^^^^^^^^^^^^^^

范围 for 循环 |cpp11| 使用冒号 ``:`` 来表示对迭代对象的元素进行遍历。

下例实现了对指定向量中的所有数字累加求和。关于向量，请参考 :ref:`std-vector` 一节。

.. literalinclude:: codes/control_for_range.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 10-12

范围 for 循环的另一个不同之处在于可以方便地使用引用，避免额外开销：

.. code-block:: c++
    
    for (const int &k: vec) {  // 使用引用
        s += k;
    }


while 循环
^^^^^^^^^^^^^^^^

用 while 循环来处理未知循环次数的任务。下例从用户输入中读取若干个数字，并将它们相加：

.. literalinclude:: codes/control_while.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 9-11


.. admonition:: cin 的读取何时会终止？
    :class: note

    ``while(cin >> k)`` 表示从输入流依次地读取内容，并赋值给变量 k。这种 cin 的读入行为在以下情况终止：

    * 读取到输入流的末尾（EoF）。对输入文件来说，EoF 就是它的最后内容；对控制台的用户输入来说，EoF 需要手动地输入：在 Windows 上，使用 Ctrl + D；在类 Unix 上，使用 Ctrl + Z。
    * 读取到异常内容。上例中，限于变量 k 的类型，用户输入的内容应当是 int 类型的数字；如果用户输入其他内容（例如字母、符号），\ ``cin`` 读取将会终止。
      
    在上例中，如果输入 ``1 2 xyz 4``\ ，程序将输出 ``Sum = 3``\ 。


do..while 循环*
^^^^^^^^^^^^^^^^^^^

do..while 循环与 while 区别很小——除了它会先执行一次循环体后，再检查循环条件。也就是说，do..while 循环的循环体最少也会被执行一次。

* 请注意 do..while 的结尾需要有分号。

.. literalinclude:: codes/control_do_while.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 8-10


跳转语句：break 与 continue
-----------------------------

.. warning::

    由于脆弱且可读性差，不建议在代码中使用 goto 语句。

跳转语句报考 break, continue 与 goto 三种。这里只介绍 break 与 continue 这两种跳转语句。

* break：结束并跳出当前循环体，执行循环体之后的代码。
* continue：结束当前迭代，执行循环的下一个迭代。

下例统计了字符串中第一个单词（以空格分割单词）的长度及其包含的字母 o 的数量。

.. literalinclude:: codes/control_break_continue.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 14,16


条件语句：if 与 switch
---------------------------

* if 语句：根据条件判断是否执行条件体。它支持 if..else 形式以及嵌套的 if..else if 形式。
* switch 语句：根据给定选项判断条件符合哪一种，然后执行对应的条件体。

if 语句
^^^^^^^^^^^

下例的 if..else 嵌套条件语句能够根据用户输入的整数，判断其正负号：

* C++ 支持 ``else if`` 语法块。

.. literalinclude:: codes/control_if.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 10-16


switch 语句
^^^^^^^^^^^^^^^^

* switch 语句将执行符合 case 标签的每一个语句直到 switch 的结尾，或者到发现 break 为止。
  
  * 因此，一般在每个 case 标签的末尾都会写有 ``break;`` 语句。
  * case 标签必须是\ **整型常量表达式**\ 。
    
    .. code-block:: c++
        
        int val = 7;
        // 错误：以下 case 标签不合法，因为它们不是整型常量表达式
        case 1.414:
        case val:
    
  * 在同一 switch 语句内部，不能有相同的 case 标签。
  * switch 语句允许特殊的 ``default`` 关键字，表示在没有 case 匹配时需执行的操作。

下例分别计数了字符串中字符 a, b, c 以及它们以外的字符出现的次数：

.. literalinclude:: codes/control_switch.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 14-27

一个常用技巧是，在 switch 的多个 case 需要执行的操作相同时，合并它们。下例统计了字母 a, b, c 的总数：

.. code-block:: c++

    int count_abc = 0;
    // ...
    switch(c) {
        // 将多个 case 写在同一行内或拆成多行均可
        case 'a': case 'b': case 'c':
            count_abc += 1;
            break;
    }
    // ...


异常语句：try 与 throw
---------------------------

.. important::

    try..catch 与 throw 语句是异常处理部分的内容。本节只对语句语法作介绍，而不涉及异常处理的详细知识。


try..catch 语句
^^^^^^^^^^^^^^^^^^^

try..catch 语句捕获异常并允发出有关该异常的信息。

* try 语句块后至少需要一个 catch 语句块，也可以是多个。
* 通常需要包含 ``<stdexcept>`` 库。常用的异常是 ``std::runtime_error``\ 。

下例尝试将 string 转为 double，并在无法转换时捕获 ``std::invalid_argument`` 异常：

* error 对象的 ``what()`` 方法将返回一个 C 风格字符串，用于提示错误信息。
* 本例中将错误信息整理后输出到标准错误 ``std::cerr``\ 。

.. literalinclude:: codes/control_try_catch.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 12-16


throw 语句
^^^^^^^^^^^^^^^

throw 语句用于直接抛出异常。

下面是一个简单的例子。在 int 除法时，若检查到除数为 0 就会抛出异常：

.. literalinclude:: codes/control_throw.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 11

请注意，上例中的异常被抛出，但并没有 try..catch 来捕获它，因此程序在抛出异常后就终止了。通常我们在抛出异常时也会捕获它，请参考下一节的例子。


完整的异常处理例子
^^^^^^^^^^^^^^^^^^^^^^

一般地，我们将 throw 定义在被调函数内部，并在外部调用函数时用 try..catch 检查异常。

下面是一个更完整的异常抛出与捕获的例子，仍然是处理整数除法中除数为 0 的问题。本例中结合使用了 throw 与 try..catch 语句。

.. literalinclude:: codes/control_try_throw.cpp
    :linenos:
    :language: c++
