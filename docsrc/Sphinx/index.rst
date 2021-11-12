.. meta::
   :category: Misc
   :keywords: documentation,rst,sphinx,website
   :series: doc-build
   :series_num: 2
   :date_init: 2020-09-20
   :date_modified: 2020-09-21
   :abstract: 本文介绍 Spinx，一个文档或文档网站生成器。

Sphinx
==========

Sphinx_ 是一个文档或文档网站生成器，最初为了 Python 编程语言的在线文档所编写。它可以生成 HTML 的网站式输出，也可以转为 pdf、帮助文档等离线阅读格式。你可以前往 `Python 官方文档 <https://docs.python.org/>`_ 站点来体会 Sphinx 所生成网站的（其中一种）风格。

Sphinx 的完整功能面向以 reStructuredText 标记语言撰写的文档。但通过插件，用户也可以使用 Markdown 文本、Jupyter Notebook 文件等不同的形式。

本文读者：

* 必须了解 reStructuredText 的基本语法；读者可以参考本站提供的 `reStructuredText 简介 <../reStructuredText/>`_ ，或者访问 Sphinx 提供的参考页面 `Sphinx - reStructuredText Primer <https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html>`_ 。
* 最好对 Python 的基本语法有所了解（为了更好地对 `conf.py` 文件进行配置）
* 如果有针对 Sphinx 做深度定制或者开发需求的读者，推荐在阅读本文之后（或同时），选读:

  * Jinja2_ ：这是 Sphinx 底层的模板定制必须了解的 HTML 模板语言，类似 Django 模板。如果只是想简单地了解，也可以阅读本文附加章节中对 Jinja2 的介绍。
  * `Python - Packaging Python Projects <https://packaging.python.org/tutorials/packaging-projects/)>`_ ：如何向 Python 的官方包索引库 Pypi 分发自己编写的包。适用于想开发 Sphinx 主题（或插件）的读者。或者也可以阅读本文中给出的编写 Sphinx 主题的示例。

.. toctree::
   :maxdepth: 2
   :caption: 目录

   Jinja.rst
   ThemeDevelopment.rst

本文档最后构建于 |today|。
