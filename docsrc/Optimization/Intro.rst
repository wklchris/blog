引言
==============

**优化问题**\ （Optimization Problem），也称最优化问题，其目标是选择一组变量取值，在满足给定\ **约束条件**\ （Constraints）或无约束条件的情形下，使\ **目标函数**\ （Objective Function）的取值达到最优。

优化问题常常写成以下形式：

.. math::

         & \min f(\boldsymbol{x}) \\
   s.t.\ & C_{leq}(\boldsymbol{x}) \leq \boldsymbol{0} \\
         & C_{eq}(\boldsymbol{x}) = \boldsymbol{0} \\

* 变量 :math:`\boldsymbol{x}` （粗体）表示一个向量 :math:`(x_1, x_2, \ldots, x_n, \ldots)`
* 目标函数 :math:`f(\boldsymbol{x})` 写为求最小值的形式。如果原函数是求最大值，添加负号。
* 约束条件：整理为不等式约束 :math:`C_{leq}` 与等式约束 :math:`C_{eq}` 两类。
  
  * 不等约束均写为小于等于的形式。原使用大于等于号的，两边同乘 -1 来变换不等号为小于等于号。不等约束中的不等号应该包含等号（例如使用小于等于号而不是小于号），因为带等号的不等式才是符合实际的。
  * 等号约束写照常书写。

因此，我们也常常将其称为\ **最小化问题**\ （Minimization Problem）。


优化问题分类
-----------------

优化问题一般分为以下几种类型：

* 线性规划（LP, Linear Programming）：线性约束条件、线性目标函数的优化问题。
* 其余的问题称为非线性规划（NLP, Non-Linear Programming）：
    
  * 二次规划（QP, Quadratic Programming）：线性约束条件、二次目标函数的优化问题。
  * 二次锥规划（SCOP, Second-Order Cone Programming）：二次锥约束条件的优化问题。
  * 指数锥规划（EXP, Exponential Programming）：指数锥约束条件的优化问题。
  * 半正定规划（SDP, Semi-Definite Programming）：半正定矩阵的约束。

* 整数规划（IP, Integer Programming）：变量必须取整数值的优化问题。

  * 混合整数规划（MIP, Mixed-Integer Programming）：部分变量被规定为整数的优化问题。
  * 类似地，我们有混合整数线性规划（MILP）与混合整数非线性规划（MINLP）。


常用求解器
----------------

商业求解器：

* CPLEX_\ ：IBM 提供的求解器，主要负责线性、混合整数与二次规划。
* COPT_\ ：杉树科技提供的求解器，在近年来性能达到了一流水准。
* Gurobi_\ ：最广泛使用的商业求解器之一，性能上表现一流。同样是线性、混合整数与二次规划。
* Xpress_\ ：FICO 提供的求解器。

开源/免费求解器：

* Coin-OR_\ : 由 OR 界提供的一系列求解器集合，全称为 Computational Infrastructure for Operations Research. 例如：
  
  * Cbc_\ ：COIN-OR 提供的混合整数规划求解器，使用分支定界法
  * Clp_\ ：COIN-OR 提供的线性规划求解器（包含在 Cbc 中）
  * Ipopt_\ ：COIN-OR 提供的非线性规划求解器

  完整的 Coin-OR 求解器集合请参考其官方网站。

* MOSEK_\ ：广泛支持各种问题的规划求解器。
* OR-Tools_\ ：Google 提供的 OR 求解器。
* SCIP_\ ：混合整数规划求解器。

Python 提供的调用库包括：

* cvxpy_\ : 一个常用的凸优化求解库。它也支持调用的外部求解器，可以参考 `cvxpy 支持的外部求解器 <https://www.cvxpy.org/tutorial/advanced/index.html#choosing-a-solver>`_\ 。
* Pyomo_\ ：一个功能更强的优化问题库，必须配合外部求解器使用。但它的使用方法较为不直观，语法的抽象程度比较高。


求解器性能基准测试*
----------------------

.. warning::

    性能基准测试不能完全代表求解器的性能表现。求解器的表现可能是取决于具体问题的。

可以参考 Hans Mittelmann 的性能测试结果（\ `Benchmarks for Optimization Software <https://plato.asu.edu/bench.html>`_）。

.. attention::
   
   请注意，这个测试中的许多项中，并没有测试 IBM CPLEX_ 与 FICO Xpress_\ 求解器。这是因为 Gurobi_ 在 2018 年利用该页面不当宣传其性能优势——尤其是相比 CPLEX 与 Xpress——它们两者自那之后就要求不再参与该性能测试。
