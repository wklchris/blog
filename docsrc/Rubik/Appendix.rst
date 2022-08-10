附录：向网页中插入魔方动画
==============================

本文中的魔方动画使用了 `Roofpig <https://github.com/larspetrus/Roofpig>`_ 这个 Javascript 库。网站 Ruwix_ 提供了一个 **在线的 roofpig 预览页面**，可以输入不同的参数来预览动画效果。

如同本文一样，向 Sphinx 站点中加入该动画的方法是：

1. 从 Roofpig 仓库中下载 ``roofpig_and_three.min.js`` 文件，并放入 Sphinx 项目的路径中（如果在 ``conf.py`` 中定义了 ``html_static_path``，请放在这个定义的路径中）。
2. 在 ``conf.py`` 文件中，更新 ``html_js_files`` 变量：
   
   .. code-block:: python3
      
      html_js_files = ['roofpig_and_three.min.js']

3. 在 reStructuredText 文中添加 HTML 块，以支持魔方动画。例如：
   
   .. code-block:: restructuredtext
      
      .. raw:: html
         
         <div class="roofpig" data-config="alg=M2 E2 S2 | flags=showalg"></div>
4. 向网站添加对 roofpig 类的 CSS 样式支持。类似上文，可以添加一个新的 CSS 文件并更新 ``html_css_files`` 变量，或者直接在现有的 CSS 文件上添加样式。这部分可以参考下文的 CSS 支持这一小节。
5. 编译 reST 文件为网页。可以在本地建立 HTTP 服务器来检查 Javascript 魔方动画是否正确。

上述代码的预期结果：

.. raw:: html
         
   <div class="roofpig" data-config="alg=M2 E2 S2 | flags=showalg"></div>


CSS 支持
--------------

如有需要，可以更新网站的 CSS（或单独写一个新的 CSS 文件），添加对 roofpig 的样式支持。

在此附上本文对 roofpig 库使用的 CSS：

.. literalinclude:: ../_static/roofpig.css
   :linenos:
   :language: css


.. _Ruwix: https://ruwix.com/widget/3d/