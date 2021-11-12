附录A：Jinja2 快速介绍
========================

Jinja2_ 是 Sphinx 的格式与主题定制中的一个重要角色，作为网页模板语言被使用。它的风格与 Django 的模板语言非常类似。如果你接触过 Liquid_ 模板语言或相关项目，例如 Jekyll_ （使用 Github Pages 搭建站点的用户应该都不会陌生），你可能对 Jinja2 中的许多语法逻辑感到熟悉。

读者可以前往 Jinja2 官方文档的 :jinja:`template-designer-documentation` 一节寻找更多信息。

官方文档给出的示例：

.. code-block:: jinja

    <!DOCTYPE html>
    <html lang="en">
    <head>
        <title>My Webpage</title>
    </head>
    <body>
        <ul id="navigation">
        {% for item in navigation %}
            <li><a href="{{ item.href }}">{{ item.caption }}</a></li>
        {% endfor %}
        </ul>

        <h1>My Webpage</h1>
        {{ a_variable }}

        {# a comment #}
    </body>
    </html>

顺便一提，Sphinx 支持 Jinja2 的语法高亮，上面这个代码块使用了： ``.. code-block:: jinja``


语法结构
------------

Jinja 中有几种主要的语法结构：

``{% ... %}``
    块语句。例如一个 for 循环的语句：

    .. code-block:: jinja

        <ul>
        {% for k in mylist %}
            <li>{{ k.id | e }}</li>
        {% endfor %}
        </ul>

    有时用户会看到诸如 ``{% if k > 0 -%} ... {%- endif %}`` 这样带短横线的块语句，它们用于删去块首尾的多余空格及换行符。例如，下例会在 mylist 是数字 1 到 5 的列表时，打印紧凑的 ``12345`` 字符串：

    .. code-block:: jinja

        {% for k in mylist -%}
            {{ k }}
        {%- endfor %}

``{{ .. }}``
    表达式。解析其内部的表达式，并打印其值。比如 ``{{ variable_name }}``

``{# ... #}``
    标准注释。Jinja 模板中应使用该语法，而不是纯 HTML 文件中的 ``<!-- ... -->`` 注释语法。这是因为，后者内部的 Jinja 表达式仍会被解析，因此其注释内容如有错误也会报错；前者无此问题。

    该注释可以跨行。

    .. code-block:: jinja

        {# Comment here.
            {% if k > 0 %}
                This block is commented!
            {% end if %}
        #}

``# ...``
    行语句。比如上例中的循环语句可以写为：

    .. code-block:: jinja

        <ul>
        # for k in mylist
            <li>{{ k.id | e }}</li>
        # endfor
        </ul>
    
    * 开启代码块的语句（如 if, for）也可以以冒号结尾： ``for k in mylist:``
    * 行语句可跨行。如果检测到语法上未匹配的左括号（圆、方、花），会自动阅读到下一行。

``## ...``
    行内注释。比如在上例中： ``<li>{{ k.id | e }}</li>  ## This is comment``


变量使用
------------

Jinja 的基本变量与 Python 基本一致，而且它们基本可以直接运用 Python 中的内置方法（最常用的可能是 ``.format()`` 字符串方法）：

* 字符串：单引号或双引号均可 ``"Hello"`` 或 ``'world'``
* 数字：可以使用科学计数法 ``123, 1.23e10``
* 列表： ``[1, 2, 3]``
* 元组： ``('a', 'b')``
* 字典： 并不是一个常用的 Jinja 类型 ``{'key1': 'val1', 'key2': 'val2'}``
* 布尔型： ``true`` 与 ``false``

需要注意的与 Python 的区别是：

* 推荐使用 **全小写的布尔型关键字** true/false，而不是 True/False；尽管 Jinja 现在也能识别首字母大写的写法。
* 在元组只有一个元素时，必须添加一个空逗号： ``('one',)``

操作符上也基本与 Python 类似，有一些值得强调：

* 截断取整除法： ``//`` ，比如 ``{{ 5 // 3 }}`` 结果是 1
* 取余： ``%`` ，比如 ``{{ 5 % 3 }}`` 结果是 2
* 字符串连接： ``~`` ，它会将两侧对象转换为字符串型，然后连接起来。

字典变量
^^^^^^^^^^^

假设现在有字典变量 var，那么它的键 key 对应的值可以用 ``var[key]`` 或者 ``var.key`` 的方式访问。比如，要把字典的该值在 p 标签中打印出来：

.. code-block:: jinja

    <p>{{ var.key }}</p>  ## 或者 var[key]


变量过滤器
^^^^^^^^^^^^^^^^

变量还能以过滤器（filter）的形式访问，即带竖线的 ``variable | filter`` 语法。例如可能是最常见的转义过滤器 ``escape`` / ``e`` ，它能够将字符中的 HTML 特殊字符（\&, \<, \> 等）转义为能正常输出的字符格式：

.. code-block:: jinja

    {{ var.key | e }}

这里列出几个常用的过滤器：

``default(value，default_value =''，boolean = False)``
    如果 value 未被定义，那么返回 default_value。如果你想对布尔值为假的变量都应用 default_value 返回，那么需要将 boolean 参数设置为 true。

    .. code-block:: jinja

        {{ variable | default('Not defined') }}
        {{ "" | default('Boolean false', true) }}

``dictsort(value, case_sensitive=False, by='key', reverse=False)``
    返回排序后的字典，默认大小写不敏感、按键排序（按值使用 by='value'）、按升序排序。

    {% for item in mydict|dictsort(reverse=true) %}

``escape(s)`` ，或者 ``e``
    转换字符串为 HTML 安全字符（针对含 \&, \< 等符号的字符串）。别名 ``e`` ： ``{{ mystr|e }}``

``format(value, *args, **kwargs)``
    类似 Python 的格式化字符串，使用 `printf 风格 <https://docs.python.org/3/library/stdtypes.html#printf-style-string-formatting>`_ 。例如：

    .. code-block:: jinja

        ## mydict 中有 key1 键
        {{ "Key1 has value: %{key1}s"|format(mydict) }}

        ## 直接传键值对
        {{ "Key1 has value: %{key1}s"|format(key1='val1') }}

        ## 位置传参
        {{ "Key1 has value: %s"|format('val1') }}

``groupby(value, attribute)``
    分组返回（排序后的）列表。来看一个官方的例子：

    .. code-block:: jinja

        <ul>{% for city, items in users|groupby("city") %}
        <li>{{ city }}
            <ul>{% for user in items %}
            <li>{{ user.name }}
            {% endfor %}</ul>
        </li>
        {% endfor %}</ul>
    
    该命令还可以用 ``(grouper, list)`` 的模式进行调用：

    .. code-block:: jinja

        <ul>{% for group in users|groupby("city") %}
            <li>{{ group.grouper }}: {{ group.list|join(", ") }}
        {% endfor %}</ul>

``join(value, d='', attribute=None)``
    类似 Python 的连接字符串列表，如 ``{{ [1, 2]|join(',') }}`` 。其 attribute 参数支持连接 value.attribute 而不是 value 本身。

``map(*args, **kwargs)``
    应用过滤器或者选择变量的属性到对象中的每一项。官方文档给出了如下应用场景：

    .. code-block:: jinja

        ## 等同于 (u.username or "Anonymous" for u in users)
        {{ users|map(attribute="username", default="Anonymous")|join(", ") }}

        ## 应用 lower 过滤器，等同于 (do_lower(x) for x in titles)
        {{ titles|map('lower')|join(', ') }}

``select(*args, **kwargs)``
    应用测试器到对象中的每一项。例如：
    
    .. code-block:: jinja
    
        {{ numbers|select("odd") }}
        {{ numbers|select("divisibleby", 3) }}

``truncate`` 与 ``wordwrap``
    限制字符串长度时可能用到的过滤器。

一份完整的 Jinja2 内置过滤器列表，请参考： :jinja:`builtin-filters` 。


变量测试器
^^^^^^^^^^^^^^^^

变量测试器（test）是另一种变量的处理方式，即带关键字 is 的 ``variable is test`` 语法。例如测试一个变量是否为偶数，使用 ``even`` 测试器：

.. code-block:: jinja

    {% if var is even %}
        <p>Var is even.</p>
    {% endif %}

或者使用接受参数的测试器（当测试器只有一个参数时，可省略括号）：

.. code-block:: jinja

    {% if var is in(mylist) %}
    {% if var is in mylist %}

常用的测试器有：

* ``defined/undefined`` ：判断变量是否是定义的/未定义的
* ``divisibleby`` ：检查整除性。 ``{{ if 9 is divisibleby(3) }}``
* 比较测试：等于/不等于 ``eq/ne`` ，大/小于等于 ``ge/le`` ，大/小于 ``gt/lt`` 。这些测试器的单词名称一般不会直接书写（因为一般直接使用二元关系符代替），但可以用于上文介绍过的 ``select`` 过滤器。
* ``even/odd`` ：判断是否是偶数/奇数。
* ``in`` ：判断是否在 seq 中。 ``{{ if 2 is in([1, 2]) }}`` ；这个通常也不会直接书写。
* ``lower/upper`` ：判断是否全为大写/小写字母。
* ``true/false`` ：判断逻辑真/假。

一份完整的 Jinja2 内置测试器列表，请参考： :jinja:`list-of-builtin-tests` 。


变量赋值*
^^^^^^^^^^^^^

Jinja 中被 set 语句赋值的变量可以在 **块内部** 通用。

.. code-block:: jinja

    {% set var = ['a', 'bb', 'ccc'] %}

如果变量在顶层（所有块的外部）被赋值，那么它可以像宏一样，用 import 语句从其他文件引入（参考 :ref:`macro` 一节）。

Jinja 还支持一个 ``with`` 块，专门用于限制变量的作用域：

.. code-block:: jinja

    {% with %}
        {% set var = 1 %}
    {% endwith %}
    var is undefined here.

上例中的赋值也可以写在 with 块的开启语句内： ``{% with var = 1 %}``

控制语句与宏
--------------

控制语句和宏（macro）是 Jinja 的核心内容。

If 判断
^^^^^^^^^^^^^

If 判断的一个示例。用 ``{% if variable %}`` 来判断某变量是否被定义（这不同于空变量或值为假的布尔型变量）。

.. code-block:: jinja

    {# 本例来自官方文档 #}
    {% if kenny.sick %}
        Kenny is sick.
    {% elif kenny.dead %}
        You killed Kenny!  You bastard!!!
    {% else %}
        Kenny looks okay --- so far
    {% endif %}

If 语句还能使用 Python 中类似的一种三元语法。更灵活的是，Jinja 中三元语法的 else 部分是可忽略的（返回 undefined）：

.. code-block:: jinja

    {# 本例来自官方文档 #}
    {% extends layout_template if layout_template is defined else 'master.html' %}

    {{ "[{}]".format(page.title) if page.title }}


For 循环
^^^^^^^^^^^^^

For 循环的一个示例：

.. code-block:: jinja

    {# 本例来自官方文档 #}
    <ul>
    {% for user in users %}
        <li>{{ user.username|e }}</li>
    {% else %}
        <li><em>no users found</em></li>
    {% endfor %}
    </ul>

* Jinja 中的 for 语句的 else 块与 Python 不同。Jinja 不会中途中断循环，因此 else 在上述 users 为空时执行；而在 Python 中，只要循环未中途跳出就会执行。注意这两者的差别。
* Jinja 循环中的 ``loop`` 是个特殊的变量，它能够调用循环的某些数据。
  
  * 用 ``loop.previtem`` 与 ``loop.nextitem`` 来调用当前值（在循环对象中对应位置的）前一个与后一个值。
  * 用 ``loop.index`` 来获取当前循环序数（从1开始）。或者使用 ``loop.index0`` （从0开始）。

* Jinja 的插件 jinja2.ext.loopcontrols 提供了 break 与 continue 的支持。
  
  .. code-block:: jinja

     {% for user in users %}
         {%- if loop.index is even %}{% continue %}{% endif %}
         ...
     {% endfor %}

* 由于早期 Python 的字典变量顺序是不稳定的，在 Jinja 的循环中要特别注意。
* Jinja 中也支持过滤循环对象（类似于 Python 中的列表解析语法）：
  
  .. code-block:: jinja
     
     {# 本例来自官方文档 #}
     {% for user in users if not user.hidden %}
         <li>{{ user.username|e }}</li>
     {% endfor %}


.. _macro:

宏
^^^^^^^^^^^

Jinja 中的宏的概念类似于函数：

.. code-block:: jinja

    {# 本例来自官方文档 #}
    {% macro input(name, value='', type='text', size=20) -%}
        <input type="{{ type }}" name="{{ name }}" value="{{
            value|e }}" size="{{ size }}">
    {%- endmacro %}

    <p>{{ input('username') }}</p>
    <p>{{ input('password', type='password') }}</p>

如果宏在其他文件中定义，可以通过 import 语句来导入：

.. code-block:: jinja

    {% import 'macrofile.html' as mymacro %}
     <p>{{ mymacro.input('username') }}</p>

宏的一种灵活用法是结合 call 语句块，将块内的内容以 ``{{ caller() }}`` 的形式放入宏中。下例是一个接受单参数的 call 语句块的例子：

.. code-block:: jinja

    {# 本例来自官方文档 #}
    {% macro dump_users(users) -%}
        <ul>
        {%- for user in users %}
            <li><p>{{ user.username|e }}</p>{{ caller(user) }}</li>
        {%- endfor %}
        </ul>
    {%- endmacro %}

    {% call(user) dump_users(list_of_user) %}
        <dl>
            <dl>Realname</dl>
            <dd>{{ user.realname|e }}</dd>
            <dl>Description</dl>
            <dd>{{ user.description }}</dd>
        </dl>
    {% endcall %}


网页模板
-----------

本节的例子全部取自 Jinja2 的官方文档 :jinja:`template-inheritance` 一节。

假设我们有一个基本模板 ``base.html``

.. code-block:: jinja

    <!DOCTYPE html>
    <html lang="en">
    <head>
        {% block head %}
        <link rel="stylesheet" href="style.css" />
        <title>{% block title %}{% endblock %} - My Webpage</title>
        {% endblock %}
    </head>
    <body>
        <div id="content">{% block content %}{% endblock %}</div>
        <div id="footer">
            {% block footer %}
            &copy; Copyright 2008 by <a href="http://domain.invalid/">you</a>.
            {% endblock %}
        </div>
    </body>
    </html>

注意到那些 ``{{% block ... %}}`` 语句，即网页块。它们是网页模板复用的关键。

现在来看一个用户自定义的模板 ``template.html``，它替换了部分上述模板的功能：

.. code-block:: jinja

    {% extends "base.html" %}
    {% block title %}Index{% endblock %}
    {% block head %}
        {{ super() }}
        <style type="text/css">
            .important { color: #336699; }
        </style>
    {% endblock %}
    {% block content %}
        <h1>{{ self.title() }}</h1>
        <p class="important">
        Welcome to my awesome homepage.
        </p>
    {% endblock %}

在该自定义模板中，用户的操作涉及：

* 引用父模板： ``{% extends "base.html" %}`` 表示该自定义模板从 base.html 继承而来。
* 替换块内容：比如父模板中的 title 块会被当前模板指定的 "Index" 字串所替代。
* 扩展块内容：注意到 head 块中的继承指令 ``{{ super() }}``，它可以在块内的任意位置。它将在此处引入父模板中的块内容，因此整个 head 块在父模板的基础上添加一些内容。
* 重复打印块内容：上例中的 ``{{ self.title() }}`` 将打印 title 块的内容。


---------

一些其他的在使用 Jinja 模板时，值得注意内容：

1. Jinja 允许在 endblock 语句中包含块的名称，以提高可读性： ``{% block title %} ... {% endblock title %}``
2. 块嵌套时，外层的变量默认在内层块不可用（ :jinja:`block-nesting-and-scope` ）。需要在内层块中，指定 ``scoped`` 关键字：
   
   .. code-block:: jinja
      
      {% for item in seq %}
          <li>{% block loop_item scoped %}{{ item }}{% endblock %}</li>
      {% endfor %}


.. _Liquid: https://shopify.github.io/liquid/
.. _Jekyll: https://jekyllrb.com/