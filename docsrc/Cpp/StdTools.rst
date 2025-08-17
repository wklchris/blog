std 实用工具
===============

C++ 的标准库提供了许多实用工具，比如 `<algorithm>` 与 `<utility>` 头文件中的内容。

.. _std-tools-find:

检索
----------

检索一个值（或者以该值作为标识符所对应的对象）是否位于容器中，是一项常见的任务。C++ 提供了许多方法来实现这一点：

* （\ **推荐**\ ，最简洁）\ `std::ranges::find` |cpp20| 。参考 :ref:`std-ranges-find` 一节
* `std::find`\ ，可能需要配合运算符重载。 :ref:`std-find` 一节提供了它与传统 for 循环的对比。
* `std::find_if`\ ，可能需要配合 lambda 函数。参考 :ref:`std-find-if` 一节。


.. _std-find:

std::find
^^^^^^^^^^^^^^^^

我们在 :ref:`if-with-initialization` 一节中已经给出了一个利用 ``std::find``\ （头文件 `<algorithm>`\ ）检索整数数组的例子。不过 `std::find` 真正的价值在于对复杂类型的检索，这可以通过对 ``==`` 等于比较运算符的重载实现：

.. literalinclude:: codes/find/std-find.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 18-22

得益于 std 容器的迭代器 `.begin()` 与 `.end()`\ ， ``std::find`` 函数能够在给定的两个迭代器位置之间检索值；本例从头检索到尾。如果没有检索到，那么返回的结果会停留在迭代器尾（即 `.end()`\ ），因此我们通过该逻辑来用 if 判断是否返回了有效的指针。如果有效，我们用 ``std::distance`` 函数（头文件 `<iterator>`\ ）来计算检索结果的下标，并用 ``->`` 运算符来获取指针所指对象的 ``grade`` 成员。

相对于传统的 for-if 嵌套（在上例中也给出作为对比）， `std::find` 写法的可读性更好，也更不容易写错。在 `std::ranges` 出现之前，\ `std::find` 一直是检索时常用的写法。


.. _std-find-if:

std::find_if 与 std::find_if_not
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``std::find_if`` 相比于 ``std::find`` 提供了更强的功能，那就是通过布尔型函数的返回值来作为检索结果。下例用于检索第一个名字以字母 B 开头的人：

.. literalinclude:: codes/find/std-find-if.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 15-19 

该例使用了一个 lambda 函数来检查人名的首字母，并在检索到结果时打印该人的名字与年龄。输出：

.. code-block:: console

   Found person with name initial letter 'B': Bob, age 33

函数 ``std::find_if_not`` 的用法类似，只是在检索函数返回 `false` 时才停止检索。这里不再赘述其用法。


.. _std-ranges-find:

std::ranges::find 及其 if 变体
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``std::ranges::find`` |cpp20| 是在 C++ 20 标准引入到头文件 `<algorithm>` 的（注意不是头文件 `<ranges>`\ ），它允许在第一参数直接传入容器（而不需要传入迭代器）、第二参数传入检索数据，因此语法更简单。当然，它也允许传入起、止迭代器作为第一、第二参数，然后在第三参数传入检索数据，就像 `std::find` 一样。

下例给出了该函数（以及其迭代器重载形式）的用法）：

.. literalinclude:: codes/find/std-ranges-find.cpp
   :linenos:
   :language: cpp
   :emphasize-lines: 16, 25-29

该函数最后一个投影参数默认是参数本身，而也可以使用函数、成员指针等其他投影方法。本例中的 ``&MyClass::id`` 表示类 MyClass 指向成员 id 的成员指针。关于成员指针，请参考 :ref:`pointer-to-member` 一节。

-----

函数 ``std::ranges::find`` 也有其 `if` 与 `if_not` 变体形式，其用法与逻辑都与 `std::find_if` 和 `std::find_if_not` 类似。而且 ``std::ranges::find_if`` 与 ``std::ranges::find_if_not`` 也既支持直接传入容器、也支持传入起止两个迭代器。这里不再赘述它们的用法，只给出一个简单的用例：

.. code-block:: cpp
   
   bool multiple_of_3 = [](int x) { return x % 3 == 0; }
   std::vector<int> v = {2, 4, 6, 8, 10};
   
   // 检索第一个被 3 整除的元素
   auto it = std::ranges::find_if(v, multiple_of_3);
   // 从下标 1 开始，检索第一个不能被 3 整除的元素
   auto it_not = std::ranges::find_if_not(v.begin() + 1, v.end(), multiple_of_3);
