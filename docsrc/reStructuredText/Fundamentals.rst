reST 基础
===============

本章包含最基础的 reStructuredText 语法。

语法速览
-------------

段落
    段落之间用空白行作为分隔。正文的段落一律顶格书写（行首不得有空格）。

缩进
    reStructuredText 的许多格式都依赖于行首缩进——作为 Python 的文档生成器，借鉴了 Python 的风格也是可以理解的。

    不过它比 Python 的缩进要求更为宽松；一般来说，用户只有一个最小的缩进要求。比如无编号列表中的项目内段落，至少要缩进2格；但用户也可以使用大于2格的缩进。

    - 要想省事，一律缩进4格。
    - 每当缩进量改变时，内容就进入了新的缩进层级。
    - 请保持（相邻的）同级内容使用同样的缩进量。

块
    以缩进为级别，整个文档可以看作不同级别的缩进结构内容的排列与嵌套。从某个缩进的行开始，到某个同等长度缩进的行结束，如果中间没有缩进长度更小的行（父级内容），这些连续的行就可以视作一个块（block）。
    
    - 块内也可以有段落，同样用空白行分隔。
    - 大部分情况下，块与其父级块之间也需要用空白行分隔，即在块的首尾各插入一个空白行。

    块的示例：
    
    .. code-block:: reST

        一段正文文字，父级块。块从此行后开始。

            缩进的文字。这是块内的第一段。

            保持缩进，这是块内的第二段。
        
        另一段正文文字，块在此行前终止。

角色（roles）
    角色是一种行内标记方式。被名称为 ``role`` 的角色所标记的文本 ``text`` ，形式为 ``:role:`text``` 。

    例如，数学角色 ``:math:`\sin x``` 的效果如 :math:`\sin x` 所示。

指令（directives）
    指令是一种块标记方式。被名称为 ``directive`` 标记的块内容，其形式为 

    .. code-block:: reST
    
        .. directive:: main-value
           :option1: value1
           :option2: value2
           
           block content
    
    ..

    - 并不是所有指令都需要在 ``main-value`` 处传入值。
    - 并不是所有指令都有参数（上例中的  ``:option:`` 部分）。拥有参数的指令，参数往往也不是必选项。

注释
    使用双点 ``..`` 来添加注释。

    - 单行注释：在双点右侧输入一个空格，然后增加注释内容，如 ``.. 注释`` 。
    - 多行注释：在双点后立即换行，并在新的行开始一个块。

    示例：

    .. code-block:: reST

        .. 单行注释

        ..
            多行注释。

            多行注释的段落二。


行内标记
-----------

最基础的行内标记（ :docutils:`inline-markup` ）有强调、加粗、代码等。

强调
   或称加斜，用一对单星号 ``*text*`` 表示强调，效果如 *text* 所示。

   在 `Docutils`_ 支持下 [#docutils-support]_ ，它的角色（role）别名是 emphasis，即强调也可以用 ``:emphasis:`text``` 的形式来实现，效果相同 :emphasis:`text` 。

加粗
   用一对双星号 ``**text**`` 表示加粗，效果如 **text** 所示。

   角色名 strong，即也可以使用 ``:strong:`text``` 的角色写法。

代码
   用一对双反引号 ````text```` 表示代码输出，效果如 ``text`` 所示。

   角色名 literal，即也可以使用 ``:literal:`text``` 的角色写法。
   
   注意这两者有细微的差别，双反引号不会理会其中的反斜线（即不执行转义，而是把反斜线也打印出来），而 literal 角色中则会进行转义。示例：

   * 在双反引号内写 ``escape \`\` symbol`` ，给出 ``escape \`\` symbol`` 结果；
   * 在 literal 角色内写  ``escape \`\` symbol`` ，给出 :literal:`escape \`\` symbol` 结果。

解释文本（ :docutils:`interpreted-text` ）
   单反引号 ```text``` 括起的对象，较少用到。

待替换文本（ :docutils:`substitution-references` ）
   在输出中会被自动以其他文本代替的对象，用一对 ``|text|`` 符号括起。常用来书写一些复杂的、但又需要在文中多处使用的文本。

   具体的用法参考 :ref:`sec-substitution-text` 一节。

上下标
   分别使用角色名 superscript/sup 与 subscript/sub 来表示上标与下标。

   * 上标 ``x\ :sup:`2``` ，效果 x\ :superscript:`2`
   * 下标 ``H\ :sub:`2`\ O`` ，效果 H\ :sub:`2`\ O

   
行内标记在使用时的注意点：

1. 被行内标记的对象 **不可以用空格开始或结尾** ，例如 ``*text *`` 是不允许的。
2. 行内标记不能嵌套。
3. 行内标记在使用时，必须 **在前后添加额外的空格** 。可以直接使用空格，也可以添加转义空格（反斜线加空格）。如果需要紧跟其他字符，那么需要添加转义的空格。

   例如 ``some *emphasized word*\s`` 会给出 some *emphasized word*\s，注意 word 与 s 之间的处理。

.. note::
      
   值得指出的是，在 reStructuredText 中，无法简单地实现“强调且加粗”的功能。它的实现可能需要借助 HTML/CSS 功能。

.. rubric:: 本节注释

.. [#docutils-support] `Docutils`_ 是一个字处理引擎，支持 HTML, LaTeX, man-pages 等众多文本格式。对 reStructuredText 格式文本，最常用的处理引擎就是 Docutils。本文中若无特殊说明，默认以 Docutils 引擎为准。


章节标题
----------

reStructuredText 的章节标题有两种书写格式：

1. 在标题的下一行以某一种章节装饰符号填充，其长度不得小于标题文字长；
2. 在 1 的基础上，在标题的上一行也 **等长填充** 同种装饰符号。请注意，此法与 1 中的方法就算采用了同种装饰符号，也会被判断为不同级别的章节标题。

章节标题支持的装饰符号有： |section-symbols|

哪一种装饰符号对应哪一级章节标题，在 reStructuredText 中并没有特别规定。因此，以用户行文中出现的自然顺序为准。

我个人习惯使用的章节标题结构， **仅供参考** ；你完全可以使用不同的符号！

.. code-block:: text
   
   ##############################
   Part, I don't use very often
   ##############################
   
   Chapter
   ==========

   Section
   ----------

   Subsection
   ^^^^^^^^^^^^^^^

   Subsubsection
   ~~~~~~~~~~~~~~~

   Paragraph, I never use it
   """"""""""""""""""""""""""""""

- HTML 只支持最多 6 层章节级别。我认为一般从 Chapter 到 Subsubsection 就足以使用。
- 你也可以遵循 `Python 风格指南 <https://devguide.python.org/documenting/#sections>`_ 中的建议，使用：
  
  .. code:: text
     
     ###### ********
     Part   Chapter  Section  Subsec  Subsub  Para
     ###### ******** ======== ------- ^^^^^^^ """""""" 

分隔线
----------

restructuredtext 支持的分隔线（ :docutils:`transitions` ）语法使用与标题装饰符相同的符号集。用相同的4个或以上的连续符号来表示分隔：

.. code-block:: reST

    段落一。

    ----

    段落二。

* 分隔线与上下内容之间需要有空白行。
* 分隔线不能紧贴在大纲标题之前或之后，也不能放在文档最开头。
* 两个分隔线不能紧贴，必须有除了空白行之外的内容。


列表
----------

列表分为编号列表、无编号列表、定义列表等。

编号列表
^^^^^^^^^^^

编号列表与 Markdown 的语法类似。具体是：

* 列表第一项之前需要有空行，最后一项之后也需要有空行。
* 以数字+小数点+空格开头。数字可以用 `#` 号代替以实现自动编号。
* 列表的项可以包含多段内容。与正文一样，用一个空白行来开启新的段落。每一段的段首需要 **与首段对齐** （例中是3个空格），比如下例中第二项的段落 "with" 与该项首段 "another" 的字母 a 对齐。
* 列表可以嵌套。

  * 嵌套内容的序号需要与项的段首对齐。下例中的嵌套序号 "1." 对齐了 "a nested list" 的字母 a。
  * 嵌套列表的与常规列表一样，第一项之前需要有空行，最后一项之后也需要有空行。

编号列表的例子：

.. code-block:: reST

   1. item
   2. another item ...
      
      with a paragraph

   #. auto numbered item
   #. a nested list

      1. nested item
      2. another nested item

   #. item 


非编号列表
^^^^^^^^^^^^^

非编号列表除了用星号 ``*`` （加号 ``+`` 或减号 ``-`` 也可以）而不是序数+小数点开启每一项外，大致与编号列表的用法相同。

.. important::
   
   请特别注意，编号列表的分段一般是行首3个空格（对齐到 "\#. " ），而非编号列表的分段则是2个空格（对齐到 "\* " ）。

无编号列表（嵌套了一个编号列表）的例子：

.. code-block:: reST
   
   * item
   * another item
     
     with paragraph
   
   - a nested numbering list
     
     1. item
     #. another item
   
   + item


定义列表
^^^^^^^^^^^^^

这是一种用来排列术语的列表。与 LaTeX 中的 definition 环境有异曲同工之义。

定义列表的例子：

- 各术语 def1, def2, def3 不能跨行，必须是单行文本。

.. code-block:: reST

   def1
      Definition of def1.
   
   def2
      Definition of def2.
       
      A paragraph.
   
   def3
      Definition of def3.


选项列表\*
^^^^^^^^^^^^^

选项列表（ :docutils:`option-lists` ）用来展示命令的参数。

- 列表的参数项支持用 ``-`` 或 ``/`` 开头。
- 建议右侧的说明文字尽量对齐。
- 参数太长而侵入了说明文字列的，可以在本行空两格后书写说明文字，或者另起一行书写说明文字。

选项列表的例子：

.. code-block:: reST

   -V           简单参数
   -h, --help   以逗号分隔的参数
   -c docname   带空格的参数
   --file=flag  带等号的参数
   --an-longer-arg  有点长的参数
   --an-arg-that-is-very-long
                过长的参数的说明文字，可以从第二行开始。注意对齐。
   /S           斜线开头的参数


超链接
--------------

reStructuredText 中，最简单的超链接可以使用一种轻便的行内标记格式。例如：

.. code-block:: reST

    `Github <https://github.com>`_

就创建了一个指向 Github 的链接 `Github <https://github.com>`_ 。

另一种方式是超链接在文中多处被引用，这时可以（一般是文末）给它声明一个别名，并在需要链接时引用它。例如：

.. code-block:: reST

    `Gat hub`_ is the most popular gay dating website in the world. Here is the link: `Gat hub`_.

    .. _Gat hub: https://dont.take.it.seriously

链接的别名（如上例中的 ``Gat Hub`` ）一般由英文字母、空格与横线 ``-`` 组成。

其他关于 Sphinx 文档的注意事项：

- 要生成指向文档内某个章节标题的链接，参考 :ref:`cross-ref` 。
- 在 Sphinx 中，要简短地定义链接，比如用 ``:abbr:`linktext``` 创建一个到 ``https://long.website/keyword=linktext`` 的链接，可以参考 `extlinks 插件 <https://www.sphinx-doc.org/en/master/usage/extensions/extlinks.html#confval-extlinks>`_ 来定义上述 ``abbr`` 角色。
- 在 Sphinx 中，要在文档中的每一页都能使用某个超链接别名，可以将别名的声明放在 conf.py 文件的 ``rst_epilog`` 或 ``rst_prolog`` 这个字符串变量中。参考 `Sphinx: rst_epilog <https://www.sphinx-doc.org/en/master/usage/configuration.html?highlight=rst_prolog#confval-rst_epilog>`_ 。


图表
-----------

reStructuredText 中允许插入图片与表格内容。

常用的表格插入有简单表、序列表与 CSV 表三种书写格式，而图片插入可以使用 ``figure`` 或者 ``image`` 两种指令。


简单表
^^^^^^^^^^

简单表 ``simple-table``\ （ :docutils-directive:`table` ）是一种快速创建表格的方式。

- 行分隔：以等号 ``=`` 标记表格的顶线与底线。
  
  - 每列中的行分隔符在竖直方向上必须对齐。
  - 如果有表头，表头与表身也用 ``=`` 分隔。
  - 在简单表中，不允许跨行。

- 列分隔：以空格来分隔列。

  - 每列的文本左侧对齐到该列行分隔符的左侧。
  - 如果需要，表中最右侧的列文本的右侧可以溢出该列的行分隔符右侧。
  - 简单表允许跨列。用横线 ``-`` 来标记跨列的长度。跨列符必须与某一列的行分隔符对齐。
  - 跨列时的列间空格用 ``-`` 替代。

- 空白行：表内任一行内部允许文本中存在的空白行。表行之间的空白行会被忽略。
- 空白表格：用反斜线 ``\`` 标记空白表格。

简单表的例子：

.. table:: Caption of a Simple Table
    :name: table-simple-eg
    :align: center    

    =======     =======
        Multicol Head
    -------------------
    Col 1       Col 2
    =======     =======
    Row 1       Overlong text.
    Row 2       Short.
    Row 3       Multi line text
                of row 3.
    Row 4       Multi para text.

                Para 2 of row 4.
    \           Row 5 with empty first col.
    =======     =======

.. code-block:: reST

    =======     =======
       Multicol Head
    -------------------
    Col 1       Col 2
    =======     =======
    Row 1       Overlong text.
    Row 2       Short.
    Row 3       Multi line text
                of row 3.
    Row 4       Multi para text.

                Para 2 of row 4.
    \           Row 5 with empty first col.
    =======     =======

以上简单表的内容可以放在 ``table`` 指令内部，以便进行交叉引用，或者添加 ``:align:`` 等选项来对齐表格、设定表格宽度。


序列表
^^^^^^^^^^^

序列表（ :docutils-directive:`list-table` ）提供了一种类似列表的表格书写格式。它比起简单表的主要优势是不需要在编排时操心横线长度以及对齐。

- 用 ``:widths:`` 给出各列的百分比宽度，或者用 ``:width:`` 给出实际宽度值
- 表格的每一行以 ``*`` 开头。每一表格行的列以 ``-`` 开头，并额外缩进。
- 表格行的列数必须与 ``:width(s):`` 中指定的相同。如果有空白单元格，请留空。
- 通过 ``header-rows`` 指定表头行数、\ ``:stub-columns:`` 指定行表头的列数。

序列表的例子：

.. list-table:: Example of List table
   :widths: 15 10 30
   :header-rows: 1
   :align: center

   * - Header 1, col 1
     - Header 1, col 2
     - Header 1, col 3
   * - Row 1, col 1
     - 
     - Row 1, col 3
   * - Row 2, col 1
     - *Row 2, col 2*
     - Row 2, col 3

.. code-block:: reST
   
   .. list-table:: Example of List table
      :widths: 15 10 30
      :header-rows: 1
      :align: center

      * - Header 1, col 1
        - Header 1, col 2
        - Header 1, col 3
      * - Row 1, col 1
        - 
        - Row 1, col 3
      * - Row 2, col 1
        - *Row 2, col 2*
        - Row 2, col 3

以上网格表的内容可以放在 ``table`` 指令内部，以便进行交叉引用。


CSV 表
^^^^^^^^^^^^

CSV 表（ :docutils-directive:`csv-table` ）支持以 CSV 格式（逗号分隔格式）来输入表格，用法是 ``csv-table`` 指令。该指令包括以下选项：

- 表宽 ``:width: LENGTH/PERCENT`` 表格的总宽度，以长度值或者百分数来指定
- 列宽 ``:widths: INT,INT,...`` 每列的相对宽度（相对于100）可以由整数 INT 指定。默认各列等宽。
- 表头：有两种表示方法。
  
  - 表头行 ``:header-rows: INT`` 指定表格中的前 INT 行为表头。
  - 表头文本 ``:header: TEXT,TEXT,...`` 直接输入每一列表头的文本。它也可以与 header-rows 选项同时使用，但必须放在 header-rows 之前。

- 列头： ``:stub-columns: INT`` 将前 INT 列作为列头。
- 对齐： ``:align: ALIGN`` 用 left, center 或者 right 来指定整个表如何向外部环境对齐。
- 外部 CSV 文件： 用 ``:file: FILEPATH`` 引用本地文件或者 ``:url: URL`` 引用网络文件。

.. code-block:: reST

    .. csv-table:: CSV Table Caption
        :header: "First Name", "Age", "Gender"
        :widths: 30, 20, 20
        :width: 60%
        :align: center

        "Tom", 3, Male
        "Dick", 5
        "Harry",, Male

上例的 CSV 表将输出以下结果：

.. csv-table:: CSV Table Caption
    :header: "First Name", "Age", "Gender"
    :widths: 30, 20, 20
    :width: 60%
    :align: center

    "Tom", 3, Male
    "Dick", 5
    "Harry",, Male



图片：image 与 figure 指令
^^^^^^^^^^^^^^^^^^^^^^^^^^^

指令 ``image`` （ :docutils-directive:`image` ）是不含标题的图片。它沿用了 HTML 中 img 的格式选项：

.. code-block:: reST

    .. image:: img.jpg
       :height: 128px
       :width: 50%
       :alt: alternative text
       :align: right
       :target: https://jump.to.URL

- ``image`` 块支持 HTML 中的所有图片格式。在 Sphinx 中，还支持使用 ``*`` 扩展名让它自动选择文件。
- ``image`` 块内所有选项都是可选的。
- ``image`` 块内无正文内容。
- 尺寸选项可以使用 ``width`` ， ``height`` 或者 ``scale`` 。宽与高可以是确定数值，也可以是百分比。
- 对齐选项可以使用 ``left/center/right`` 标记水平对齐，或 ``top/middle/bottom`` 标记竖直对齐。
- 跳转选项 ``target`` 指出了点击图片时跳转的链接。链接可以是绝对地址、相对地址，或者 reStructuredText 语法中的超链接。

指令 ``figure`` （ :docutils-directive:`figure` ）与 ``image`` 非常类似。不过它可以在块内部书写一段或多端内容，作为图片的标题文本。

.. code-block:: reST

    .. figure:: img.jpg

       Caption of the figure.

       Another paragraph of the caption.

最后，给出一个 ``figure`` 指令的例子。

.. figure:: eg.png
    :width: 240px
    :alt: An adorable ginger cat.
    :align: center

    我不允许有人没见过我家的可爱小橘！

.. code-block:: reST

    .. figure:: eg.png
        :width: 240px
        :alt: An adorable ginger cat.
        :align: center

        我不允许有人没见过我家的可爱小橘！

.. _cross-ref:

交叉引用
--------------

reStructuredText 交叉引用上的功能远强于 Markdown，这也是我选择它撰写文档的重要原因之一。


章节或图表引用
^^^^^^^^^^^^^^^^^

主要的引用角色有两种：由 reStructuredText 支持的标题引用 ``:ref:`` ，以及 Sphinx 额外支持的带序号引用 ``:numref:`` 。

在章节前添加特定的标签，以便在文中的其他位置（之前或之后）使用 ``ref`` 角色对其进行引用。章节交叉引用实质是一个超链接，显示的文本是章节标题，指向该章节的浏览位置。

.. code-block:: reST

    .. custom-section-label:

    Section to ref
    ---------------------

    For details, see :ref:`custom-section-label` section.

在需要手动指定引用文本的时候，我们可以使用类似超链接的语法：

.. code-block:: reST

    For details, see :ref:`Custom <custom-section-label>` section.

以上 ``:ref:`` 引用语法也适用于：

- ``figure`` 图片的内部 ``:name:`` 字段。引用时将显示该图片的标题，见下例。
- ``table`` 表格的内部 ``:name:`` 字段。只有显示地放在 ``table`` 指令内部的表格可以这样进行引用。

在 Sphinx 中有另一种引用方式，即使用序号的 ``numref`` 角色引用。可以输出如 ``Fig. 1.1`` 这样的链接。

- 序号引用需要在文档的 conf.py 中设置 ``numfig=True`` 。用户还可以用 ``numfig_format`` 字典来自定义序号引用的格式，参考 `Sphinx: numfig_format <https://www.sphinx-doc.org/en/master/usage/configuration.html#confval-numfig_format>`_。
- 序号引用允许一种自定义的链接文本格式。用户可以用 ``{number}`` 来指代序号，用 ``{name}`` 来指代标题。

.. code-block:: reST


    .. figure:: img.jpg
       :name: custom-label
       
       Figure caption.
    
    A figure number link :numref:`custom-label` and a customized numbered link :numref:`Fig {number}: {name} <custom-label>`.

用 ``numref`` 角色引用上文中的简单表的例子：数字引用 :numref:`table-simple-eg` 与自定义引用 :numref:`表 {number}: {name} <table-simple-eg>` 。

.. code-block:: reST

    数字引用 :numref:`table-simple-eg` 与自定义引用 :numref:`表 {number}: {name} <table-simple-eg>` 。

除了 ``:ref:`` 中支持的引用对象，指令 ``:numref:`` 还额外支持 ``code-block`` 代码块。


脚注与文本引用
^^^^^^^^^^^^^^^^^^^

脚注在文中以 ``[#name]_`` 的链接形式标出。之后，一般在文章结尾的 ``rubric`` 指令后声明其内容。

脚注在文中会以编号的形式输出，且格式上位于上标位置。点击文中脚注的链接可以跳转到文末，之后可以点击文末该脚注的链接重新跳回之前文中的阅读位置。

.. code-block:: reST

    A paragraph with footnote [#my-fn]_.

    .. rubric:: Footnotes

    .. [#my-fn] Text of the footnote.

文本引用与脚注的用法极其类似，除了它在文中输出的是正文格式的文本而不是上标格式的编号。

.. code-block:: reST

    A paragraph with a citation [zhangsan1900art]_.

    .. [zhangsan1900art] An article published in 1900 by Zhang San.


其他交叉引用
^^^^^^^^^^^^^

Sphinx 还支持一些 reStructuredText 原生语法之外的交叉引用，可以参考 `Sphinx: 交叉引用 <https://www.sphinx-doc.org/en/master/usage/restructuredtext/roles.html#cross-referencing-syntax>`_。

下面是几个可能用到的、由 Sphinx 支持的交叉引用角色：

``:doc:``
    引用本项目中的另一个 reStructuredText 文件。例如 ``:doc:`another``` 引用与当前文件同路径的 ``another.rst`` 文件。
  
    它也可以用显式链接的方式引用： ``:doc:`Link text <another>``` 。

``:download:``
    （该指令只对 HTML 输出有效）

    提供文件的下载链接。该可下载的文件会被复制到输出文件夹的目录的 ``_download`` 文件夹内，并文中会提供一个指向它的链接（基于 Hash 计算）。

    例如 ``:download:`link text <code/eg.py>``` 将给出一个指向 ``code/eg.py`` 文件的链接。

    如需转换为非 HTML 格式，可以将上述文本放在一个 ``.. only:: builder_html`` 指令块中。这样可以在非 HTML 输出中隐藏这个链接。

``:term:``
    如果文档用 glossary 指令创建了术语词汇表，那么可以用该角色来引用对应的术语。参考 :ref:`directive-glossary` 。


.. 注释

.. _Docutils: https://docutils.sourceforge.io/