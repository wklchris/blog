引言
=======================

本章快速展示了 reStructuredText 的风格特定，并讨论了与更轻量的 Markdown 的对比。

快速示例
-----------

下面是一段 reST 文档的快速示例，帮助读者对文档的写作模式有个初步的概念。具体的用法从下一张开始介绍。

.. code-block:: ReST
   
   Emphasis *text* , bold **text** and inline ``code`` are close to Markdown style.

   A new paragraph starts after a blank line. Here is a displayed math equation:

   .. math::

      \sum_{k=1}^{2n} k &= 1 + 2 + 3 + \cdots + 2n \\
                        &= n(2n + 1)

上面这段通过 Sphinx 转为 HTML 后的效果如下：

Emphasis *text* , bold **text** and inline ``code`` are close to Markdown style.

A new paragraph starts after a blank line. Here is a displayed math equation:

.. math::

   \sum_{k=1}^{2n} k &= 1 + 2 + 3 + \cdots + 2n \\
                     &= n(2n + 1)


与 Markdown 的比较
----------------------

作为一个标记语言，Markdown 应该是站在了轻量、易读、易写三者结合的巅峰了．那么，生成在线文档时（特别是 HTML 网页），有什么理由不考虑静态网站生成器 + Markdown，而是考虑 Sphinx + reST 呢？

因为 Markdown 有个最大的弊病：**不统一**．

这个不统一体现在多个方面；既包括风格的不统一（这里最通用的可能是 Github Flavor，但是仍不能说所有平台都统一了），也包括渲染效果的不统一．

风格的不统一带来了很严重的问题，最主要体现在扩展功能的实现．举例来说，Github 风格的 Markdown 支持勾选框（checkbox），但是这一功能并不是“原生”Markdown 的特性．这导致在其他的在线 Markdown 预览服务商，带有勾选框功能的文本不能正常显示．

渲染效果的不统一主要是体现在代码块上．虽然这一点往往能够通过插件解决，但是 Markdown 也为没能提出简洁的解决方案而受到弊病．比如有的网站可以识别形如 ``\`\`\`java`` 的代码块起始，并用 Java 语法进行高亮；而有的却不行．不过，如果你能对一个静态网站生成器从一而终，渲染风格可能并不是一个大问题。

-----

Markdown 在严谨和易用中取了平衡，就注定了其偏向日常的定位，且需要更多的其他社区努力来完善一整套解决方案．相比之下，reST 无疑是牺牲了易读和易写性的；但是作为补充，它提供了更多灵活的定制功能．在一份需要严格排版、保证效果唯一稳定的文档中，这些特性都较为可贵．


兼容 Markdown 风格的 reST
--------------------------------

由于 reStructuredText 的语法几乎是 Markdown 的超集，我们常常在书写 reStructuredText 时也注意对 Markdown 风格的兼容性。

这一点在一些提供 Markdown 渲染的站点上较为实用。比如 Github 提供了仓库内 Markdown 的预览功能，这个功能也会被应用到 reStructuredText 文件上。

这一点比较常顾及的是 reStructuredText 的反斜线转义命令 ``\`` ；因为 Markdown 只对特定的字符进行转义，而 reStructuredText 对所有接在反斜线后的那个字符都进行转义（虽然有时这并不必要）。因此，我们总是建议只对 Markdown 转义字符集中的字符前添加反斜线，这能一定程度上改善在线预览 reStructuredText 的可读性。
