控制流语句
===============

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


do..while 循环
^^^^^^^^^^^^^^^^^^^



条件语句：if 与 switch
---------------------------

if 语句
^^^^^^^^^^^

下例的 if 条件语句能够根据用户输入的整数，判断其正负号：

* C++ 支持 ``else if`` 语法块。

.. literalinclude:: codes/control_if.cpp
    :linenos:
    :language: c++
    :emphasize-lines: 10-16
