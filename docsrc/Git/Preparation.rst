Git 准备工作
================


安装
--------

前往 `Git 官网 <https://git-scm.com/downloads>`_ 下载和安装 Git。


全局配置：用户名与邮箱
------------------------

设置用户名和邮箱地址：

.. code-block:: sh

   $ git config --global user.name "wklchris"
   $ git config --global user.email wklchris@example.com

* 选项 `--global` 表示这些设定会应用于每个项目的 Git 仓库。如果只想为当前仓库设置，取消 `--global` 参数即可。
* 当前计算机用户的“全局配置”会被存储在 `~/.gitconfig` 文件中（Windows 用户的 `~` 路径是 `C:\Users\username` ）。

要查看我们的配置文件，使用 `git config --list` ；要查询单个键的值，使用 `git config <key>`：

.. code-block:: sh
   
   $ git config user.name
   wklchris

除了用户名与邮箱，我们还常常用 `git config` 命令来：

* 配置别名（alias）命令，方便我们用更短的命令来实现复杂操作。
* 配置全局的 `.gitignore_global` 文件，用来在所有仓库中忽略指定类型的文件。


查阅帮助
-----------

使用 `git help <command>` 来显示帮助内容．这些帮助内容实质是本地的 HTML 文件，均可以离线访问。例如，查看 `git config` 命令的用法：

.. code-block:: sh
   
   $ git help config
   ... (在网页浏览器中打开)
