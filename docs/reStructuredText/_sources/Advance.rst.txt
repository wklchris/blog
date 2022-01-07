高级功能
=============

本章介绍 reStructuredText 的高级语法功能。


代码输出
-----------

行内代码我们在之前已经介绍过，使用一对双反引号 ````text```` 或者 literal 角色 ``:literal:`text``` 。

本节主要介绍代码块的使用。


文本代码块
^^^^^^^^^^^^^

.. note::
   
   reStructuredText 原生的代码块指令是 ``code`` （ :docutils-directive:`code` ），本文不做介绍。

Sphinx 中独立的代码块输出，使用 ``code-block`` 指令（或其别名 ``sourcecode`` 指令）。

- 在该指令的同一行，可选指定一种编程语言的语法进行高亮。restructuredText 使用 Pygments 进行语法高亮，它支持的编程语言的简要列表可以参考 `Supported languages <https://pygments.org/languages/>`_ ；这些编程语言除了正式名，也有一些别名可以使用，具体可以参考本地安装的 pygments 库下的这个文件中的 ``LEXERS`` 变量：

  .. code-block:: none
     
     site-packages\pygments\lexers\_mapping.py
  
  * 例如，在 ``LEXERS`` 变量中，我们可以找到关于 Python 语法高亮的那一行：
    
    .. code-block:: python
       
        'PythonLexer': ('pygments.lexers.python', 'Python', ('python', 'py', 'sage', 'python3', 'py3'), ...
    
    注意到此行内侧嵌套的那组圆括号，表示 python, py, sage, python3, py3 这些名称都可以用来指定 Python 语法高亮（但我一般推荐最靠前的那个名称）。
  * 如果不需要在该代码块中启用语法高亮（纯文本），可以指定一个不被 Pygments 支持的名称，比如 text 或者 none。

- 代码块的行号选项
  
  * 启用行号 ``:linenos:``
  * 指定第一行行号从何数字开始 ``:lineno-start: NUM`` 。该选项会自动启用行号选项
  * 强调某一行或几行 ``:emphasize-lines: NUM1,NUM2,...``

- 添加代码块标题 ``:caption: TEXT`` 
- 代码块被以 ``:ref:`` 引用时显示的文本 ``:name: TEXT``
- 反向缩进代码块 ``:dedent: NUM`` 


文本代码块的例子。注意，所有的选项都不是必须的。

.. code-block:: reST

    .. code-block:: python
       :linenos:
       :emphasize-lines: 1,4-5
       :caption: A highlighted code-block example
       :name: 一个代码块示例

       def foo():
           x = 3
           y = 4
           z = x ** 2 + y ** 2
           print(f"Val = {z}")
           return z
    
该例将会输出下述的代码块。它在被引用时会显示为 :ref:`code-block-eg` 这个链接。

.. _code-block-eg:

.. code-block:: python
    :linenos:
    :emphasize-lines: 1,4-5
    :caption: A highlighted code-block example
    :name: 一个代码块示例

    def foo():
        x = 3
        y = 4
        z = x ** 2 + y ** 2
        print(f"Val = {z}")
        return z


导入代码文件
^^^^^^^^^^^^^^^

.. note::
   
   reStructuredText 原生的导入代码文件指令是 ``include`` （ :docutils-directive:`including-an-external-document-fragment` ），本文不做介绍。

Sphinx 支持从外部文件导入代码文本，使用 ``literalinclude`` 指令。该指令支持的选项有：

* 显示行号 ``:linenos:``
* 语法高亮 ``:language: LANG``
* 行包括，即有选择地导入哪些行： ``:lines: NUM1,NUM2,...``
* 行强调 ``:emphasize-lines: NUM1,NUM2`` 。注意，如果有选择地导入代码行，行号将与文件原本的行号不同。

.. code-block:: reST

    .. literalinclude:: conf.py
       :linenos:
       :language: python
       :emphasize-lines: 3-6
       :lines: 1, 17-21, 23-
    
以上导入代码的例子将导入与当前 rst 文档同目录下的 conf.py 文件，并输出以下结果：

.. literalinclude:: conf.py
    :linenos:
    :language: python
    :emphasize-lines: 3-6
    :lines: 1, 17-21, 23-



.. _display-math:

数学公式
-----------

.. note::
   
   reStructuredText 中支持的数学公式使用 LaTeX 语法。对使用 LaTeX 书写数学公式不熟悉的读者，可以在网络上找到许多入门语法；或者，也可以参考我撰写的 `《简单粗暴LaTeX》一书 <https://github.com/wklchris/Note-by-LaTeX>`_ 中的数学公式章节。

行内数学公式直接使用角色 ``:math:`` ，例如 :math:`\sin\alpha` ，这里主要讲行间公式的处理。

reStructuredText 语法中使用 ``math`` 指令（ :docutils-directive:`math` ）来插入行间数学公式。

* 数学公式语法上与 LaTeX 的原生命令一致。
  
  - 单行公式可以直接写在指令的同一行，比如 ``.. math:: a + b = c`` 。
  - 多行公式需要在公式间插入一个空白行。

* 数学公式中可以使用与符号 ``&`` 来对齐列，使用双反斜线 ``\\`` 来换行。Sphinx 会自动将整个块放在一个 LaTeX 语法的 split 环境中。

关于 Sphinx 中的数学公式使用：

.. note::

    在 Sphinx 输出 HTML 时，建议在 conf.py 中加载 `sphinx.ext.mathjax`_ 插件。本文档开启了该插件，且**配置了 MathJax 的自动编号**。下文中所有右侧的编号都由 MathJax 提供，而左侧的、位于公式前一行的编号是 Sphinx 构建的结果。当然，这两者的格式都可以在配置（或 CSS 文件）中进行变更。

    Sphinx 用户可以参考下文的 :ref:`mathjax-support` 一节来获取更多关于 MathJax 的信息。

* Sphinx 支持以 ``:label: TEXT`` 选项来给公式添加编号，并使其能够被 ``:eq:`` 角色交叉引用。更复杂的引用可以使用 MathJax 中的功能支持，见 :ref:`mathjax-support` 一节。
* Sphinx 支持以 ``:nowrap:`` 选项来取消自动公式环境（equation, align, split），而显式地由读者自行指定。


示例
^^^^^^^^^^^^

单行公式的例子如下。使用 ``:eq:`math-single``` 引用时会显示 :eq:`math-single` 这个链接。

.. code-block:: reST

    .. math::
        :label: math-single
    
        \int_1^\infty \frac{1}{x^2} dx = 1

.. math::
    :label: math-single

    \int_1^\infty \frac{1}{x^2} dx = 1

使用 ``&`` 与 ``\\`` 进行标记的对齐多行公式，引用如 :eq:`math-multi` 。

.. code-block:: reST

    .. math::
        :label: math-multi

        (a + b)^2 &= (a + b)(a + b) \\
                  &= a^2 + 2ab + b^2
       
.. math::
   :label: math-multi

   (a + b)^2 &= (a + b)(a + b) \\
             &= a^2 + 2ab + b^2

用空白行分隔的多个公式，在 MathJax 支持下的 HTML 输出会默认向右对齐。如果开启了 MathJax 的自动编号，那么右侧会对整体附加一个序号（而不是给每行编号）；这类似于 LaTeX 中的 split 环境。

.. code-block:: reST

    .. math::
        
        f(x) = x^2 + \sin x

        S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \}

.. math::
    
    f(x) = x^2 + \sin x

    S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \}

如果要居中对齐，使用 ``:nowrap:`` 选项配合 LaTeX 语法中的 gather(\*) 环境：

.. code-block:: reST

    无编号多行居中：

    .. math::
        :nowrap:
        
        \begin{gather*}
        f(x) = x^2 + \sin x \\
        S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \}
        \end{gather*}

无编号多行居中：

.. math::
    :nowrap:
    
    \begin{gather*}
    f(x) = x^2 + \sin x \\
    S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \}
    \end{gather*}

要给多行公式中的每一行进行自动编号（并使它们在文中能够被交叉引用），参考 :ref:`mathjax-multi-ref` 一节。


.. _mathjax-support:

MathJax 支持
^^^^^^^^^^^^^^^^^

MathJax （ `官方文档 <http://docs.mathjax.org/en/latest/index.html>`_ ）是一个 JavaScript 数学公式渲染引擎。在使用 Sphinx 将 reStructuredText 文档转换为 HTML 后，往往需要用 MathJax 来支持其中的数学公式输出。

Sphinx 中启用 MathJax 的方式是在 conf.py 中加载 `sphinx.ext.mathjax`_ 插件：

.. code-block:: python

    # 向 extensions 变量中添加一项 'sphinx.ext.mathjax'
    extensions = ['sphinx.ext.mathjax', ...]

在 conf.py 中，我们还可能需要配置 ``mathjax_config`` 变量来设置 MathJax，比如启用 MathJax 支持的 `公式自动编号 <http://docs.mathjax.org/en/latest/input/tex/eqnumbers.html#automatic-equation-numbering>`_ ：

.. warning::

    由于 reStructuredText 与 MathJax 语法的兼容性，Sphinx 并非接受 MathJax 的所有功能。MathJax 的自动编号在 Sphinx 文档中很难进行交叉引用，因此仍然推荐使用 Sphinx 的 ``:label:`` 角色。

    同理，在 reStructuredText 文档中，应当使用 ``:math:`` 行内角色，而不是 MathJax 支持的 ``$..$`` 语法。

.. code-block:: python
    
    # 如果是 MathJax v2，使用：
    # mathjax2_config = {
    #    'TeX': {
    #        'equationNumbers': { 'autoNumber': "AMS" }
    #    }
    # }
    mathjax3_config = {
        'tex': {'tags': 'AMS', 'useLabelIds': True},
    }

单行公式引用
~~~~~~~~~~~~~~~~~~~~~~~~~

单行公式引用需要启用 ``:nowrap:`` 选项，并以 MathJax 语法（LaTeX 语法）中的 ``\label`` 显式地声明标签。在需要引用时，使用 ``\ref`` 引用公式序号，或者使用 ``\eqref`` 引用由圆括号括起的公式序号。

LaTeX 中支持的单行公式有两种：

* 带编号的单行公式： ``\begin{equation}..\end{equation}`` 
* 无编号的单行公式： ``\begin{equation*}..\end{equation*}`` 

由于需引用的公式一般都含编号，下面以带编号公式为例。

.. code-block:: reST

    引用 MathJax 单行公式： :math:`\ref{mathjax-single}` 或 :math:`\eqref{mathjax-single}` 。

    .. math::
        :nowrap:

        \begin{equation}
        \label{mathjax-single}
        \alpha + \beta = \gamma
        \end{equation}

引用 MathJax 单行公式： :math:`\ref{mathjax-single}` 或 :math:`\eqref{mathjax-single}` 。

.. math::
    :nowrap:

    \begin{equation}
    \label{mathjax-single}
    \alpha + \beta = \gamma
    \end{equation}

.. _mathjax-multi-ref:

多行公式引用
~~~~~~~~~~~~~~~~~~~~~~~~~

多行公式需要配合 ``math`` 指令的 ``:nowrap:`` 选项，并以 MathJax 语法（LaTeX 语法）中的 ``\label`` 显式地声明标签。

LaTeX 语法中常用的多行公式环境有（不带星号环境将给每行编号，带星号的不做任何编号）：

* align(*)：支持以 ``&`` 对齐各列，每行独立编号。列对齐方式在居右与居左之间轮替，即各列的对齐依次是：居右、居左、居右、居左、……
* split(*)：与 align(*) 类似，但所有行共享一个编号。与 equation-aligned 嵌套环境的效果类似。
* gather(*)：每行内容居中且独立编号。
* gathered：在 equation 内部嵌套 gathered 环境，可以达成居中且共享编号的输出效果。

先看一个 gather 环境的例子，每行独立编号（align 环境也是如此）。要引用的行需要用 ``\label`` 语法声明一个标签。

.. code-block:: reST

    类似单行公式引用，引用时使用 :math:`\ref{mj-gather-a}` 或者 :math:`\eqref{mj-gather-a}` 。

    .. math::
        :nowrap:

        \begin{gather}
        f(x) = x^2 + \sin x \label{mj-gather-a} \\
        S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \} 
        \end{gather}

类似单行公式引用，引用时使用 :math:`\ref{mj-gather-a}` 或者 :math:`\eqref{mj-gather-a}` 。

.. math::
    :nowrap:

    \begin{gather}
    f(x) = x^2 + \sin x \label{mj-gather-a} \\
    S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \} 
    \end{gather}

如果将上例中的 gather 环境改为带星号的 gather 环境，将不进行任何公式编号。此时，标签命令 ``\label`` 应该写在数学环境内部、第一行公式之前。引用公式 :math:`\ref{eq:gatherstar-a}` 的语法同上。

.. math::
    :nowrap:

    \begin{gather*}
    \label{eq:gatherstar-a}
    f(x) = x^2 + \sin x \\
    S(r) = \{ x \in \mathbb{R}^n \,|\, \|x\| \leq r \} 
    \end{gather*}

最后，看一个 split 环境的例子。split 环境中所有行共享同一个编号，引用为 :math:`\ref{eq:split}` 。标签命令同样写在第一行公式之前。

.. code-block:: reST

    .. math::
        :nowrap:

        \begin{split}
        \label{eq:split}
        a &> b & c &\geq d \\
        e &\neq f & \lim_\infty g &= h
        \end{split}

.. math::
    :nowrap:

    \begin{split}
    \label{eq:split}
    a &> b & c &\geq d \\
    e &\neq f & \lim_\infty g &= h
    \end{split}


关于 MathJax 支持的全部 LaTeX 命令，参考 `MathJax: Supported TeX/LaTeX commands <http://docs.mathjax.org/en/latest/input/tex/macros/index.html#supported-tex-latex-commands>`_ 文档。


自定义数学命令
~~~~~~~~~~~~~~~~~~~~~~~

MathJax 允许自定义简单的 LaTeX 命令，即 LaTeX 中的 ``\newcommand`` 命令。参考 `MathJax: Defining TeX Macros <http://docs.mathjax.org/en/latest/input/tex/macros.html#defining-tex-macros>`_ 页面。

在 Sphinx 中，由于 ``rst_prolog`` 变量的存在，我们可以直接在 conf.py 文件中更改该变量值，来在每一个文档文件的头部添加一个额外的数学环境，用于自定义数学命令：

.. literalinclude:: conf.py
    :language: python
    :lines: 33-
    :emphasize-lines: 2-5

上例是本文档使用的 conf.py 文件的一部分，定义了两个数学命令：

* 一个是 ``\ud`` 命令，无输入参数，用来打印一个竖直的积分符号。
* 另一个是 ``\pfrac[#1]{#2}`` 命令，有分子分母两个参数，用来打印偏导分式。参数1是分母，默认值是x；参数2是分子。

下面是一个使用了上述两个自定义符号的例子：

.. code-block:: reST

    .. math::

        \pfrac{f(x,y)} &= y \\
        \pfrac[y]{f(x,y)} &= \int_0^\pi \sin x \ud x 

.. math::

    \pfrac{f(x,y)} &= y \\
    \pfrac[y]{f(x,y)} &= \int_0^\pi \sin x \ud x 


警示标记
-----------

警示标记（ :docutils-directive:`admonitions` ）是我个人最喜欢的 reStructuredText 功能之一。它将绘制一个能够快速引起读者注意的消息框。比如 warning 警示标记：

.. code-block:: reST

    .. warning:: This is an optional title

        Warning mesage.

        Warning message paragraph 2.

.. warning:: This is an optional title

    Warning mesage.

    Warning message paragraph 2.

reStructuredText 提供特殊支持的警示标记有以下 9 种：

- attention 注意
- caution 警告。Sphinx 中，caution 的默认的 HTML （中文）输出样式与 warning 相同。
- danger 危险
- error 错误
- hint 提示
- important 重要
- note 注解
- tip 小技巧
- warning 警告。Sphinx 中，warning 默认的 HTML （中文）输出样式与 caution 相同。

它们的样式如下：

.. attention::
    attention

.. caution::
    caution

.. danger::
    danger
    
.. error::
    error

.. hint::
    hint

.. important::
    important

.. note::
    note

.. tip::
    tip

.. warning::
    warning

除了上述几种警示以外，reStructuredText 允许用户使用 ``admonition`` 指令来自定义警示。比如，用户可以创建一个不在上述 9 类中的一类新警示（比如叫 critical），然后再在 CSS 文件中对 critical 类进行样式定义。

.. code-block:: reST

    .. admonition::
       :class: critical
       
       Admonition message.

上例在 Sphinx 构建后，会输出一个具有 admonition 与 critical 类别的 div 容器。


.. _sec-substitution-text:

替换文本
-----------

reStructuredText 支持的替换功能（ :docutils:`substitution-definitions` ）有许多应用场景。一个是用来替代比较长的一个短语或称谓，减少键盘输入的痛苦。

* 以双侧竖线 ``|text|`` 来标记目标文本。在生成文档时，它会被替换文本所代替。
* 以含下划线后缀的语法 ``|text|_`` 将让目标文本在被代替的同时，还成为一个指向 ``_text`` 地址的超链接。
* 替换文本的写法类似于脚注，不过还需要 ``replace::`` 关键字。
* 替换文本中可以包含行内标记，比如强调、斜体等。

.. code-block:: reST

    本文将介绍文本标记语言 |rst| (reST)。由于 |rst-plain| 这个词太长了，很多人喜欢在输入时简化它。

    前往文档页面： |rst|_

    .. |rst-plain| replace:: reStructuredText
    .. |rst| replace:: **reS**\ tructured\ **T**\ ext
    .. _rst: https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html

本文将介绍 |rst| (reST)，一种文本标记语言。由于 |rst-plain| 这个词太长了，很多人喜欢在输入时简化它。

.. |rst-plain| replace:: reStructuredText
.. |rst| replace:: **reS**\ tructured\ **T**\ ext
.. _rst: https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html

----------

除了文本，替换对象也可以是图片。事实上它还可以是一些奇奇怪怪的东西，但用的比较少，这里就不介绍了。感兴趣的读者可以参考 Docutils 文档。

.. code-block:: reST

    本段中的这个目标对象 |kitty| 将会被替换为一个宽、高均为 70 px 的竖直居中图片。

    .. |kitty| image:: eg.png
        :height: 70
        :width: 70
        :align: middle

本段中的这个目标对象 |kitty| 将会被替换为一个宽、高均为 70 px 的竖直居中图片。

.. |kitty| image:: eg.png
    :height: 70
    :width: 70
    :align: middle

最后，Sphinx 还提供了几个默认的替换文本：

* ``|today|`` ：文档构建当天的日期。需要在 ``conf.py`` 文件中声明 ``today_fmt`` 变量来指定日期的格式，比如：
  
  .. code-block:: python
     
     today_fmt = "%Y-%m-%d"
  
  这会打印如 2000-01-31 这样的日期格式。定义日期格式的语法与 Python 中 datetime 格式的使用相同。

* ``|release|`` ：文档的发布信息，需要在 ``conf.py`` 中声明 ``release`` 变量。
* ``|version|`` ：文档的版本信息，需要在 ``conf.py`` 中声明 ``version`` 变量。


.. _directive-glossary:

术语表\*
-----------

术语表是由 Sphinx 支持的一个指令，本质上是一个位于 glossary 指令块内部的定义列表：

* 术语表中的每一组术语可以是单个（例中 a1），也可以是多个（例中 f2 与 c3）
* 术语表支持一个可选的选项 ``:sorted:`` ，它将按（每组的第一个术语的）首字母顺序排列该表所有术语组。
* 术语表中的术语可以用 ``:term:`` 角色引用（引用时忽略行内标记格式），比如 :term:`a1` 与 :term:`d4 term` 。

.. code-block:: reST

    .. glossary::
        :sorted:

        **a1**
            A1 is a term.
        
        f2
        c3
            F2 and C3 are two closely related terms, or they are identical.

        d4 term
        e4 term
            D4/E4 are two keys to be sorted.

上例将给出以下的输出结果：

.. glossary::
    :sorted:

    **a1**
        A1 is a term.
    
    f2
    c3
        F2 and C3 are two closely related terms, or they are identical.

    d4 term
    e4 term
        D4/E4 are two keys to be sorted.


.. _sphinx.ext.mathjax: https://www.sphinx-doc.org/en/master/usage/extensions/math.html#module-sphinx.ext.mathjax