附录B：Sphinx 主题开发
=========================

本章介绍了开发 Sphinx 主题的步骤。Sphinx 官方简要说明了如何创建一个玩具般的（定制性低）主题，参考 `Spinx - HTML theme development`_ 。

读者可以参考的主题示例有：

* python-docs-theme_ : Python 官方文档使用的 Sphinx 主题。非常短小精悍，又不失定制性。是一个很好的入门读物。


主题的文件结构
----------------

Sphinx 的主题一般位于一个文件夹中。下面是一个用 Python 开发的 ``theme-name`` 主题的文件结构示例：

.. code-block:: none

    theme_name/
        static/
            theme.css
            ...
        __init__.py
        layout.html
        ....
        theme.conf
    setup.py

* 文件夹名 ``theme_name`` 是开发名称。当主题的正式名（此例中的 ``theme-name`` ）用横线符 ``-`` 连接时，建议在开发名称中将横线换为下划线 ``_`` ；这是因为 setuptools 库在给文件打包时会自动对一些文件夹名进行这一转换。
* ``static`` 文件夹不可更名，用于存放 css, javascript，图片等主题需要用到的文件。这些内容会在构建使用该主题的网页时，自动复制到 HTML 输出文件夹的 ``_static`` 路径中。
* ``theme.conf`` 不可更名，用于配置主题的基本参数。
* 文件夹中还可能存放 ``layout.html`` 等文件，这些文件一般是用来覆盖 Sphinx 默认输出的模板文件。它们的名称虽不硬性要求，但习惯上设置为与要覆盖的 Sphinx 默认模板同名。
* ``__init__.py`` 与父文件夹的 ``setup.py`` 文件是用 setuptools 打包主题时需要的文件，便于用户随后分发该主题到 Pypi。  


theme.conf 文件
------------------

该文件实质上遵循 ``.ini`` 配置文件的语法，基本上可以理解为键值对 ``key = value`` 的语法。该文件中所有的值（ ``value`` ）都会被读取为 **字符串类型** 。

下面是一个简单的例子：

.. code-block:: none

    [theme]
    inherit = basic
    stylesheet = theme.css

    [options]
    opt_name = option value here

* 该文件分为 theme 与 options 两个小节。前者是所有 ``theme.conf`` 文件都必须有的。
* 在 theme 小节中：

  * 使用 ``inherit`` 来指定基础的网页模板。如果想从基础风格开始，选择 ``basic`` 即可。从零开始的 ``none`` 非常不推荐，你往往更需要的是继承 ``basic`` 然后把样式与模板中需改动的功能都覆盖掉。
  * 使用 ``stylesheet`` 来指定主题的主 CSS 文件。我比较喜欢使用 ``theme.css`` 这个文件名，记得把这个文件放在 ``theme_name/static`` 路径中。

* 在 options 小节中（本小节可选），用户可以指定一些变量。比如上例中声明了一个 ``opt_name`` 变量，并给它设置了默认值。
  
  * 在 Sphinx 文档的 ``conf.py`` 中，利用 ``html_theme_options`` 这个字典变量，可以覆盖这些默认值：
    
    .. code-block:: python

        # 在 conf.py 中覆盖主题变量
        html_theme_options = {"opt_name": "option value there"}
  
  * 在该主题的模板中（比如 ``layout.html`` ），可以利用 Jinja2 语法引用这些变量，但是 **变量名称需要添加前缀** ``theme_``。例如：
    
    .. code-block:: html

        {{% if theme_opt_name is defined -%}}
          <p>theme_opt_name is defined with value {{ theme_opt_name }}</p>
        {{%- endif %}}


构建 Python 包
------------------

.. note::
 
   本节需要用到的 Python 库有 twine 与 wheel。它们可能需要用户用 pip 命令安装。

   在使用 setuptools 之前，强烈建议将其升级到最新的版本：

   .. code-block:: none
    
        pip install --ugprade setuptools

将主题构建为一个 Python 包并上传到 Pypi 是一个 Sphinx 主题开发者必须懂得的操作。

构建包时主要需要配置主题文件夹 ``theme_name`` 中的 ``__init__.py`` 文件，以及父文件夹中的 ``setup.py`` 文件。

@@@

.. _python-docs-theme: https://github.com/python/python-docs-theme
.. _Spinx - HTML theme development: https://www.sphinx-doc.org/en/master/development/theming.html
