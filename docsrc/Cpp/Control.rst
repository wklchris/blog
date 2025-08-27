控制流
===========


.. _if-statement:

If 条件判断
----------------

使用 if 语句对圆括号内的条件表达式的逻辑值（\ `true` 或 `false`\ ）进行判断，按照判断的结果执行不同的代码分支。If 语句有三种嵌套形式：

* 最简单的 `if (..) {..}`\ 。如果条件不满足，则不做任何事。
* 带 `else` 的 `if (..) {..} else {..}`\ 。条件满足则执行 `if`` 分支的代码，否则执行 `else` 分支的代码。
* `else` 语句块可以嵌套另一个 `if` 语句块，从而实现 `if .. else if ..` 这种结构。如果有必要，还可以继续嵌套更多的 `if` 语句块。

以下是 if 条件语句的使用示例：

.. literalinclude:: codes/if/if.cpp
   :linenos:
   :language: cpp

输出：

.. code-block:: console

   x is positive
   v is not empty. It has 3 elements
   s has exact 5 characters

.. _if-with-initialization:

带初始化的 if 语句
^^^^^^^^^^^^^^^^^^^^

除了在条件语句处（圆括号内）使用单个表达式，现代 C++ 还提供了一种灵活的写法，即带初始化的 if 语句 |cpp17| 。它允许在条件表达式处定义临时变量来进行较复杂的判断，即 `if (init; cond) {..}` 语法。

一个典型的例子是使用 `<algorithm>` 头文件中的 `std::find` 来检索 std 容器中是否存在要查询的数据（以及第一次出现时的下标）。相对于传统的 for 循环查询，这是一种更现代、更简单的写法，写起来更难以出错，阅读起来也更轻松。

.. literalinclude:: codes/if/if-init.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 10

这种带初始化的 if 语句的好处在于能够避免将只需要在 if 语句块内使用局部变量（比如上例中的 `it` 指针）暴露在语句块外。该例子的输出如下：

.. code-block:: console

   Target value 20 found at index 1


三元运算符
^^^^^^^^^^^^

C++ 使用三元运算符（Ternary Operator）语法 `cond ? true-state : false-state` 来进行简单的条件运算。当 `cond` 为真时，执行 `true-state` 语句；否则，执行 `false-state` 语句。

三元运算符常常作为简短 `if-else` 语句的替代用于初始化或赋值。下例是对 std::abs 作用在 int 上时的一个简单模仿：

.. literalinclude:: codes/if/ternary.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 5

输出：

.. code-block::

   When x = -4, abs(x) = 4


switch-case 语句
-----------------------

C++ 支持用 `switch .. case` 语句处理多重选择条件。

* switch 语句不接受字符串或浮点数类型。它一般接受布尔型、枚举类型、整数与字符型等。
* 一般地，每个 case 语句都以 ``break`` 结尾。如果省略子母船了，那么 case 语句会 *继续向下执行，直到抵达结尾或遇见 break 语句*\ 。
* 当一个 case 块为空时，它会自动与下一个 case 块共享要执行的内容。 
* switch 语句的最后可以添加一个 ``default:`` 块，用来囊括所有没有通过 case 列出的情形。

例子：

.. literalinclude:: codes/if/switch.cpp
   :linenos:
   :language: cpp

输出：

.. code-block::

   Day of the week:
   Meeting Mon-Fri morning
   Coding Thu & Fri afternoon


.. _for-loop:

For 循环
----------------

.. hint::

    现代 C++ 推荐使用 `size_t` 作为循环变量，因此我们不再介绍传统的以 `int` 作为循环变量的写法。

C++ 的 for 循环语句有两种语法：

* **传统 for 循环**\ ： `for (init; cond; iter)` 格式。它最初执行一次 `init`\ ；然后在每次执行循环体之前检查 `cond` 是否为真，如果假则退出循环；接着它执行循环体，并执行 `iter` 语句，最后进入下一次循环。
  
  * for 循环中的三个表达式均可省略（但分号不可省略）。当 `cond` 省略时，默认其恒为真。
  * 在实践中，我们常常对标准类型（\ `std::string`\ ， `std::vector`\ 等）进行循环，而它们还支持通过迭代器语法 ``begin()`` 或 ``end()`` 来遍历，并通过 ``std::distance`` 来计算下标。我们在例中也包含了这部分代码，但更详细的内容请参考 :doc:`StdTypes` 章节。

* **范围 for 循环** |cpp11| ：现代的简化语法循环，格式为 `for (decl : range)`\ 。其中 `decl` 语句声明了每一步循环中使用的元素，而 `range` 则是要进行遍历的、包含此类元素的可索引对象。
  
  * 范围 for 循环在 `decl` 语句中可以使用常量修饰 ``const`` 或者引用 ``&``\ ，且元素的类型可以使用 ``auto`` 。请按需使用这些特性。

例子：

.. literalinclude:: codes/loop/for.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 7, 12, 17

以上 for 循环的输出结果相同：

.. code-block::

   H e l l o 
   H e l l o 
   H e l l o 

特别地，如果要在范围 for 循环的同时获取下标值，可以使用 ``std::views::enumerate`` |cpp23| （头文件 `<ranges>`\ ）：
  
  .. literalinclude:: codes/views/enumerate.cpp
     :linenos:
     :language: cpp
     :emphasize-lines: 7


.. _reverse-loop:

反向遍历
^^^^^^^^^^^^^^^

要特别注意以无符号整数 `size_t` 作为循环变量时，反向循环的写法与使用有符号整数（例如 `int`）时不同。

.. literalinclude:: codes/loop/for-reverse-size_t.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 7-9

在循环第一步之前，判断 i 是否为 0（布尔 false），如果不是则递减并进入循环。在结束 i=0 的循环步骤之后，循环会在递减之前发现 i 等于 0，因此结束循环。我们不能用 ``i >= 0`` 来判断，因为无符号整数 `size_t` 总是大于等于 0 的。

另一种做法是，对于 std 标准容器 `std::array`\ ，我们可以使用更现代的反向迭代器 ``rbegin/rend`` |cpp14| 来反向遍历：

.. literalinclude:: codes/loop/for-reverse-iter.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 7

最后，更现代的 C++ 标准中允许使用 ``std::views::reverse`` |cpp20| 配合范围循环语法来增强可读性，也避免了解指针操作，不过其本质实现与反向迭代器是一致的：

.. literalinclude:: codes/loop/for-reverse-view.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 8 


(do) while 循环
-------------------

while 循环常用于循环次数未知的情形，语法类似于 `while (cond)`\ ，即等价于 `for (;cond;)`\ 。while 循环也有两种语法，一种语法是先检查后执行的 `while` 语句，如果首次检查未通过则循环体不会被执行（直接跳过）；另一种是语法是先执行后检查的 `do .. while` 语句，它至少会被执行一次。

例子：

.. literalinclude:: codes/loop/while.cpp
   :linenos:
   :language: cpp

输出：

.. code-blocK::

   n = 2
   n = 1
   Ending: n = 0
   m = 0
   Ending: m = 1


break 与 continue
-------------------------

C++ 使用 ``break`` 来中止当前的循环体（或当前的 `switch` 语句），使用 ``continue`` 来跳过本次循环中的后续行，直接进入下一循环。例子：

.. literalinclude:: codes/loop/break-continue.cpp
   :linenos:
   :language: cpp

输出如下。由于 `break` 的中止，for 循环没有访问最后一个元素。

.. code-block::

   1 = 2 * 0 + 1
   3 = 2 * 1 + 1
   4 is not odd

