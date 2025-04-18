预备知识：凹凸性
=========================

集合与函数的凹凸性（Convexity）是优化问题讨论中的基本概念。


仿射集
--------------

对于 :math:`n` 维空间 :math:`\mathbb{R}^n` 中的两个不同的点 :math:`x_1` 与 :math:`x_2` (:math:`x_1\neq x_2`)，我们可以用一个参数 :math:`\theta` 来表示过这两个点的直线（即由下列 :math:`y` 组成的点集）：

.. math::

    y = \theta x_1 + (1-\theta) x_2, \quad \theta \in \mathbb{R}.

* 当 :math:`0\leq \theta \leq 1` 时，点 :math:`y` 在 :math:`x_1` 与 :math:`x_2` 这两点之间连成的线段上。
* 当 :math:`\theta < 0` 时， 点 :math:`y` 在该两点连线的延长线上偏 :math:`x_2` 的一侧；反之，当 :math:`\theta > 1` 时，点 :math:`y` 在该两点连线的延长线上偏 :math:`x_1` 的一侧。

上式可以看作是点 :math:`x_1` 与 :math:`x_2` 的一个\ **仿射组合**\ （Affine Combination），即将它们进行总权重为 1 的加权平均。如果你知道线性组合的概念，那么仿射组合可以看作是一种特殊（权重之和为 1）的线性组合。两个点的仿射组合描述过它们的直线，而这两点的线性组合则描述了它们所张成的平面。

这种仿射组合的定义可以推广到任意多点的情形。对于 :math:`k` 个点 :math:`x_1, x_2, \ldots, x_k`，我们可以用 :math:`\theta_1, \theta_2, \ldots, \theta_k` 来表示它们的仿射组合：

.. math::

    y = \sum_{i=1}^k \theta_i x_i = \theta_1 x_1 + \theta_2 x_2 + \cdots + \theta_k x_k , \quad \sum_{i=1}^k \theta_i = 1, \quad \theta_i \in \mathbb{R}.

在了解仿射组合的概念后，我们来介绍仿射集的定义：

.. admonition:: 仿射集
   :class: important

   **定义：**\ 如果集合 :math:`S` 中任意不同两点确定的直线都在集合 :math:`S` 内，即

   .. math::
      
      x_1, x_2 \in S  \implies  \theta x_1 + (1-\theta) x_2 \in S, \quad \theta \in \mathbb{R}.

   那么称集合 :math:`S` 为\ **仿射集**\ （Affine Set）。 

.. admonition:: 仿射集的相关性质
   :class: note

   1. 仿射集包含该集合内任意点组成的仿射变换。
   2. **仿射集可以由线性子空间平移后得到**\ 。对于仿射集 :math:`S` 中的任意一点 :math:`x_0`，我们将其平移到原点（平移 :math:`-x_0`\ ），即可得到一个新集合 :math:`S' = \{x - x_0 \mid x \in S\}`。我们对新集合 :math:`S'` 验证线性子空间的定义：
      
      * 非空（或包含原点）：取 :math:`x = x_0`，则得 :math:`x - x_0 = 0 \in S'`。
      * 对加法与乘法闭合：对在新集合 :math:`S'` 中的任意两点 :math:`y_1`, :math:`y_2`，我们知道点 :math:`y_1 + x_0` 与 :math:`y_2 + x_0` 在仿射集 :math:`S` 中。考虑新集合中两点的任意线性组合 :math:`y = \theta_1 y_1 + \theta_2 y_2` （其中 :math:`\theta_1, \theta_2 \in \mathbb{R}`\ ），并将其反向平移 :math:`x_0` 得到点 :math:`x`：

        .. math::
           
           x &= \theta_1 y_1 + \theta_2 y_2 + x_0 \\
           &= \theta_1 (y_1 + x_0) + \theta_2 (y_2 + x_0) - \theta_1 x_0 - \theta_2 x_0 + x_0 \\
           &= \theta_1 (y_1 + x_0) + \theta_2 (y_2 + x_0) + (1 - \theta_1 - \theta_2) x_0
        
        由于上述线性组合的系数之和为 1，因此该线性组合实质上是集合 :math:`S` 中三个点 :math:`y_1 + x_0`, :math:`y_2 + x_0` 与 :math:`x_0` 的一个仿射组合。故上述点 :math:`x` 也在仿射集 :math:`S` 中；该点在平移后应在新集合 :math:`S'` 中，即 :math:`\theta_1 y_1 + \theta_2 y_2 \in S'`。因此，集合 :math:`S'` 对加法与乘法闭合。
      
      综上，新集合 :math:`S'` 满足线性子空间的定义，它是一个线性子空间。
   3. 线性方程组 :math:`\boldsymbol{A}x = b` 的解集 :math:`S = \{x \mid \boldsymbol{A}x = b\}` 是一个仿射集。这一点很容易用仿射集的定义验证。对解 :math:`x_1` 与 :math:`x_2` 及它们的任意仿射变换 :math:`y = \theta x_1 + (1-\theta) x_2`，我们有：
     
      .. math::

         \boldsymbol{A}y & = \boldsymbol{A}(\theta x_1 + (1-\theta) x_2) \\
                         & = \theta \boldsymbol{A}x_1 + (1-\theta) \boldsymbol{A}x_2 \\
                         & = \theta b + (1-\theta) b \\
                         & = b.
     
      这表示 :math:`y` 同样是该线性方程组的解，即解集 :math:`S` 是一个仿射集。

      * 当该方程组是一个齐次线性方程组时（:math:`b = 0`），解集 :math:`S` 既是仿射集也是线性子空间。

最后，一个集合 :math:`S\in \mathbb{R}^n` 的所有仿射组合所构成的集合称为该集合的\ **仿射包**\ （Affine Hull），记作 :math:`\text{aff}(S)`。

.. math::
   
   \text{aff}(S) = \left\{x \,\middle|\, x = \sum_{i=1}^k \theta_i x_i, \quad x_i\in S, \quad \sum_{i=1}^k \theta_i = 1, \quad \theta_i\in\mathbb{R}\right\}.

一个集合的仿射包通常是包含该集合的最小仿射集。例如，一个圆的仿射包是它所在的平面。


凸集
--------------

将仿射集的定义表述中的“直线”替换为“线段”，我们就可以得到凸集的定义：

.. admonition:: 凸集
   :class: important

   **定义：**\ 如果集合 :math:`S` 中任意不同两点确定的\ :uline:`线段`\ 都在集合 :math:`S` 内，即

   .. math::
      
      x_1, x_2 \in S  \implies  \theta x_1 + (1-\theta) x_2 \in S, \quad \forall\theta \in [0, 1].

   那么称该集合 :math:`S` 为\ **凸集**\ （Convex Set）。 

   * 推广到无穷和的形式：对于凸集 :math:`S` 中的无穷个点 :math:`x_i`，其凸组合 :math:`\sum_{i=1}^{\infty} \theta_i x_i` 也在该集合内，即

     .. math::

        x_1, x_2, \ldots \in S  \implies  y = \sum_{i=1}^{\infty} \theta_i x_i \in S, \quad \forall\theta_i\geq 0, \quad \sum_{i=1}^k \theta_i = 1.

类似于仿射组合、仿射包的定义，我们限制 :math:`0\leq \theta\leq 1`，就得到凸组合与凸包的定义：

* **凸组合**\ （Convex Combination）：

  对于 :math:`k` 个点 :math:`x_1, x_2, \ldots, x_k`，我们可以用 :math:`\theta_1, \theta_2, \ldots, \theta_k` 来表示它们的凸组合：

  .. math::

     y = \sum_{i=1}^k \theta_i x_i = \theta_1 x_1 + \theta_2 x_2 + \cdots + \theta_k x_k , \quad \sum_{i=1}^k \theta_i = 1, \quad \theta_i\geq 0.

* **凸包**\ （Convex Hull）：

  集合 :math:`S` 的所有凸组合所构成的集合称为该集合的凸包，记作 :math:`\text{conv}(S)`。

  .. math::

     \text{conv}(S) = \left\{x \,\middle|\, x = \sum_{i=1}^k \theta_i x_i, \quad x_i\in S, \quad \sum_{i=1}^k \theta_i = 1, \quad \theta_i\geq 0\right\}.
  
  集合 :math:`S` 的凸包是包含该集合的最小凸集。例如，圆心角为 :math:`270^\circ` 的扇形，其凸包是整个圆。


凸集的例子
----------------

TBD


保持凸性的运算
----------------

TBD