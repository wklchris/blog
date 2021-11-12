.. meta::
   :category: Misc
   :keywords: documentation,rst,sphinx
   :series: Misc
   :series_num: 1
   :date_init: 2018-10-15
   :date_modified: 2020-09-20
   :abstract: 本文介绍 reStructuredText，一种最初用于创建 Python 技术文档的标记语言。

reStructuredText 简介
=======================

.. warning::
   
   本文由个人之前的旁置子站点 /Gitbooks 迁移而来。由 Markdown 文档转为了 reStructuredText，且内容有更新。

reStructuredText（简写为 reST，RST，或 ReST）是一种纯文本标记语言。虽然它并不像 Markdown 那样流行，但提供了更丰富的定制功能与扩展性。

本文适合：

* 对轻量标记语言有所了解的读者。最好有 Markdown 的使用经验。关于 Markdown，可以参考 Github 的这篇 `英文简介 <https://guides.github.com/features/mastering-markdown/>`_ 。
* `Sphinx <https://www.sphinx-doc.org/>`_ 的用户，他们非常需要了解 reST 。本文中的许多功能并不是 reStructuredText 原生支持的，而是由 Sphinx 在 reStructuredText 的语法上进行扩展而实现的。
  
  如果您对 Sphinx 知之甚少，可以配合本站的另一篇博文 `Sphinx 简介 <../Sphinx/>`_ 阅读。

* 正在寻找一种平衡的标记语言的读者。从某种意义上讲，reST 算是一种在“轻量/易读易写”与“强功能性/定制性”之间的达到平衡的文本格式。对我来说，reST 是在某些网络文档构建的场合下是一种恰当的格式。
  
  * HTML 功能强大，但是易读性差。
  * Markdown 易读易写，但是牺牲了太多的功能性。有些功能可以通过插入 HTML 来解决，但无疑是与 Markdown 的核心优势背道而驰。
  * 论外，LaTeX 语法——这并不是标记语言——是牺牲易用性来换取功能性的典范。但在网站上展示 PDF 通常不是一个恰当的选择；同时，对于页面的内容更新来说，LaTeX 的编译套件也过于笨重了。


.. toctree::
   :maxdepth: 2
   :caption: 目录

   Intro.rst
   Fundamentals.rst
   Advance.rst

最后更新于 |today|。
