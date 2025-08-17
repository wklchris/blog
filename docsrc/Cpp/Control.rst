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


.. _for-loop:

For 循环
----------------

.. hint::

    现代 C++ 推荐使用 `size_t` 作为循环变量，因此我们不再介绍传统的以 `int` 作为循环变量的写法。

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

