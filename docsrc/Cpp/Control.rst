控制流
===========


.. _if-statement:

If 条件判断
----------------


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

