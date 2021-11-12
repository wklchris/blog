Git 基础命令
===============

本章节介绍 Git 仓库的基本操作。


仓库创建
-------------

要开始创建一个本地仓库，用户可以选择从零初始化一个仓库，或者从一个给定的远程仓库克隆。


初始化仓库：init
^^^^^^^^^^^^^^^^^^^^^^^

常规的初始化仓库，可以新建一个文件夹，然后在其中执行 `git init` 来初始化：

.. code-block:: sh
   
   $ git init
   Initialized empty Git repository in project/.git/


设置远程仓库：remote
^^^^^^^^^^^^^^^^^^^^^^^

如果你有远程的仓库（比如 Github 仓库）需要推送文件，往往需要用 `git remote` 添加对应的远程仓库地址：

.. code-block:: sh

   # 格式：git remote add <remote-name> <url>
   $ git remote add origin https://github.com/wklchris/wklchris.github.io

其中，`origin` 是最常用的远程仓库名称；用户当然也可以选择其他的名称。

要管理当前仓库配置的远程仓库，可以使用 `git remote -v` 来查看：

.. code-block:: sh
   
   $ git remote -v
   origin  https://github.com/wklchris/wklchris.github.io (fetch)
   origin  https://github.com/wklchris/wklchris.github.io (push)

上述返回的信息表示，当前仓库配置了名为 `origin` 的远程仓库；后缀的 fetch/push 表示取回与推送时使用的地址。


从远程仓库克隆：clone
^^^^^^^^^^^^^^^^^^^^^^^^

用户也可以从指定的远程仓库网址（可能是 https, git, 或者 SSH 协议）取回整个仓库，便于在本地展开工作。比如将本站仓库克隆到本地：

.. code-block:: sh
   
   git clone https://github.com/wklchris/wklchris.github.io

以上命令会自动在当前目录创建一个与远程仓库同名的文件夹（即 `wklchris.github.io` 文件夹），并将内容拖取到其中。远程仓库中的所有分支都会被同步，且远程仓库会在本地记录中被自动命名为 `origin` （就像默认的分支名叫 master 一样）。


提交文件
-------------

在本地仓库中的修改，需要提交到版本控制记录。


检查文件状态：status
^^^^^^^^^^^^^^^^^^^^^^^^^

在初始化仓库后，立刻使用 `git status` 命令会返回以下结果：

.. code-block:: sh
   
   $ git status
   On branch master
   nothing to commit, working directory clean

这表示自从上次提交以来，Git 追踪的文件都没有发生变化；同时，也没有任何新的文件被检测到。

如果新建一个 `README` 文档，再运行此命令：

.. code-block:: sh
   
   $ git status
   On branch master
   Untracked files:
     (use "git add <file>..." to include in what will be committed)
     README
   nothing added to commit but untracked files present (use "git add" to track)

这告诉我们发现了一个新的文件（untracked file）,它还从没被 git 版本仓库记录过。

该命令还可以使用 `-s` 参数，生成一个简略列表。关于暂存、修改、追踪，可以参考 :ref:`git-status` 一节。

.. code-block:: sh
   
   $ git status -s
    M README
   MM Rakefile
   A  lib/git.rb
   M  lib/simplegit.rb
   ?? LICENSE.txt

上例中，偏右的 `M` 表示修改了尚未暂存，偏左的 `M` 表示修改并已暂存。`A` 表示一个新加入追踪的文件，最后 `??` 表示新检测到的未追踪的文件。你也可以使用 `-sb` 参数，这会显示你当前的分支信息。


暂存文件：add
^^^^^^^^^^^^^^^^^

利用 `git add` 命令来将新文件（untracked）或未暂存（unstaged）文件提交到暂存区。下例

.. code-block:: sh
   
   $ git add README
   $ git status
   On branch master
   Changes to be committed:
     (use "git reset HEAD <file>..." to unstage)

       new file: README
       modified: test.py


你也可以通过 `git add *` 来暂存所有文件：

.. code-block:: sh
   
   $ git add *

其他：

* 通常版本控制只针对文本文件；例如 `.pdf` 或 `.jpg` 这类文件一般不加入暂存。
* 在暂存时使用 `-i` （或 `--interactive` ）选项，可以进入交互式暂存界面。


忽略文件 (.gitignore)
^^^^^^^^^^^^^^^^^^^^^^^^^^

当目录中有许多文件或者子目录无须交付 Git 进行版本控制时（比如 `.ipynb_checkpoints` ），新建一个 `.gitignore` 文件:

.. code-block:: sh
   
   $ touch .gitignore

向其中添加内容来忽略匹配的文件：

* `.gitignore` 文件特性：

   * 空行或以 '#' 开头的行会被忽略
   * 使用 glob 模式进行匹配
   * 以 `/` 开头防止匹配时递归
   * 以 `/` 结尾确保匹配目录
   * 以 `!` 开头表示取反

* **glob 模式特性** ：glob 模式是 shell 使用的简化后的正则表达式。

   * 用 `*` 表示匹配字符 0 到无穷次
   * 用 `?` 表示匹配单个任意字符
   * 用 `[...]` 匹配任意一个方括号内的字符(例如 `[acd]` 可以是 `a` `c` 或 `d`)，用 `[x-y]` 匹配任意一个字符 `x` 与 `y` 之间的字符（例如 `[0-9]` 匹配任意一个阿拉伯数字）
   * 用 `**` 匹配任意中间目录，例如 `a/**/b` 可以匹配 `a/c/b` 与 `a/c/d/b`。

一个简单的例子：

.. code-block:: sh
   
   *.a         # 忽略所有扩展名为 .a 的文件
   /A          # 忽略当前目录下名为 A 的文件
   A/          # 忽略文件夹 A 内的所有内容
   B/*.pdf     # 忽略文件夹 B 下的（不包括子文件夹） pdf 文件
   B/**/*.pdf  # 忽略文件夹 B 及其子文件夹中的 pdf 文件

如果你想要将一些后缀加入全局的忽略列表，可以在 `~` 目录下新建一个 `.gitignore_global` 文件，并使用命令：

.. code-block:: sh
   
   $ git config --global core.excludesfile ~/.gitignore_global


这里有一个 `Github 仓库 <https://github.com/github/gitignore>`_ ，收录了许多编程语言的 `.gitignore` 文件样式，可以参考。


内容比对：diff
^^^^^^^^^^^^^^^^^^^

如果你有修改了但尚未暂存的文件，使用 `git diff` 来查看 **尚未暂存的改动** ：

.. code-block:: sh
   
   $ git diff [<filename>]


如果不指定文件名，那么会查看两次版本快照所有文件的差异。

如果加入 `--staged/--cached` 选项，则可以查看暂存区与版本库中最新版本之间的差异：

.. code-block:: sh
   
   $ git diff --staged [<filename>]

diff 命令提供了众多的参数，我时而会用到的有：

* `--name-only` 参数：用来显示哪些文件与比对的版本不同。如果无，则不返回任何信息。
* `--dirstat` 参数：用来显示分别是哪些子文件夹发生了改动，改动量的占比分别是多少。另外，也存在一个按子文件计算占比的 `--dirstat-by-file` 参数。
* `--stat` 参数：用来快速显示文件的更改数目（插入与删除的行数）。

比如利用 `--name-only` 参数，显示在子文件夹 `folder` 中哪些文件已修改并暂存了：

.. code-block:: sh
   
   $ git diff --name-only --staged folder/

该参数的输出结果可以帮助脚本来判断文件的更改情况。


提交更新：commit
^^^^^^^^^^^^^^^^^^^^^^^

使用 `commit` 命令来提交**暂存区的所有内容**：

.. code-block:: sh
   
   $ git commit

这时，需要你使用编辑器（默认是 Vim）来输入提交的说明文本。对于不熟悉 Vim 操作的用户，在输入内容后按 Esc 切换到 Normal 模式，再输入 `:wq` 命令即可保存并退出。

你也可以使用 `-m` 选项来避免打开编辑器：

.. code-block:: sh
   
   $ git commit -m "Input text here."

提交后，控制台终端会显示该次提交的 SHA-1 校验、提交到的分支（关于分支的内容会在下文介绍）、修改的文件数量，以及修改的行数量。

最后，git 还提供了一种将工作区内所有文件直接暂存然后提交的选项 `-a` ：

.. code-block:: sh
   
   $ git commit -a -m "Input text here."


版本变更与回退
----------------

我们简单提到过 git 使用 HEAD 指针指向最新的一次提交。每一次提交的之前的紧邻提交称为父提交。比如次新的提交就是 `HEAD~` ，父提交的父提交是 `HEAD~2` （确切地说，`~` 指代的是第一父提交，第一父提交的第二父提交需要使用 `HEAD~2^2` ）。

* 更多关于分支的内容，参考 :ref:`branch` 章节。
* 如果要回退的提交是一个合并提交，请参考 :ref:`revert-merge-commit` 部分的内容。


从工作目录回退：reset --hard
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

你对工作目录的内容做了修改，但尚未 `add` 到暂存区。现在你想放弃这些修改，回到上次 `commit` 之后的状态:

.. warning:: 

   这是个危险的命令；由于被放弃的内容从未被提交，因此无法再找回。

.. code-block:: sh
   
   # 危险的命令！
   $ git reset --hard HEAD <filename>

这里 `HEAD` 是缺省值，可以省略；你也可以用 SHA-1 值（或其前 7 位）来指定要回退到的版本。本质是放弃并销毁上次 `commit` 以来所有的更改。


从暂存区回退：reset --mixed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

你的修改已经 `add` 到暂存区，现在你想把暂存区清空，但在本地文件中仍保留这些更改：

.. code-block:: sh
   
   $ git reset --mixed HEAD <filename>

这里的 `--mixed` 选项是缺省值，可以省略。该命令相当于取消了 `add` 命令，更改仍存在于文件中。


从版本回退：reset --soft
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

你的文件已 `commit` 到仓库记录中去，现在你想将 HEAD 指针移动到上一个 commit 的位置:

.. code-block:: sh
   
   $ git reset --soft HEAD~

`HEAD~` 表示 HEAD 指针的父节点。

此时你的暂存区、工作目录并未被回退，仍保留着你的改动。本质是撤销了最近的一次 `commit` 命令。

.. warning::

   **如果你要应用回退的版本已经推送到远程仓库，那么不要使用 reset 命令** ，因为 reset 命令会更改日志。请使用 `revert` 命令来新建一个提交，这个提交的内容将与你指定的版本一致：

   .. code-block:: sh

      $ git revert HEAD~
   
   `revert` 命令在还原合并提交中也有作用，可以参考 :ref:`revert-merge-commit` 部分的内容。


修改提交：commit --amend
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. important::
   
   不建议在提交已被推送到远程的情况下对其进行更改。

如果在提交时忘记了 `add` 某个文件，或者其他需要修改提交的场合，使用 `--amend` 参数。例如：

.. code-block:: sh
   
   $ git commit -m 'initial commit'
   $ git add forgotten_file
   $ git commit --amend

它会将暂存区内的修改追加到上个提交中去。如果没有任何修改，它允许你更改提交的说明文本。

如果修改时也不更改上次的 commit 信息，可以追加 `--no-edit` 选项：

.. code-block:: sh
   
   $ git commit --amend --no-edit


查看提交历史：log
-----------------------

命令是 `log`，不过有很多有趣的参数细节：

.. code-block:: sh
      
   $ git log


基本参数
^^^^^^^^^^^^^^^^^^^^^

这里将 `log` 命令的参数分为输出参数与过滤参数两种。输出参数主要有：

* `-p` ：查看提交内容的差异。
* `--abbrev-commit` ：只显示简洁 SHA-1，一般是其前 7 个字符。
* `--color` ：启用颜色。常用的颜色包括：red, green, yellow, blue, magenta, cyan, black, white, normal; 以及可在以上颜色之前加上格式 bold, dim, ul, blink, reverse. 例如：`%C(bold blue)`。
* `--graph` ：用图像的方式显示你的分支历史。
* `--stat` ：列出提交修改的文件以及一些基本修改的信息。
* `--shortstat` ：只列出修改的文件数量和修改的行数。
* `--relative-date` ：显示相对日期，即 "2 days ago" 这种格式。
* `--pretty=<option>` ：可选的 `option` 有 `short`, `full`, `oneline` 等。

特别地，`--pretty=format:"<format-str>"` 可以自定义显示内容，例如：

.. code-block:: sh
   
   $ git log --color --pretty=format:"%Cred%h%Creset %d - %s (%cr by %an)"
   36e8d6b  - Update README. (2 days ago by wklchris)
   bae6fc8  (origin/master, origin/dev, master) - Init (3 days ago by wklchris)

上例的第一列会显示为红色。我的 `lg` 命令自定义参考下文中 :ref:`alias` 一节的内容。

常用的选项有：

========    =============================================
   选项         说明    
========    =============================================
%s          提交的说明文本
%H/%h       提交记录的完整/简洁 SHA-1 字符串
%T/%t       树对象的完整/简洁 SHA-1 字符串
%P/%p       父对象的完整/简洁 SHA-1 字符串
%an/%cn     作者/提交者的名字
%ae/%ce     作者/提交者的电子邮件地址
%ad/%cd     作者/提交者的修改日期（可用 `--date=` 指定格式）
%ar/%cr     作者/提交者的修改日期，以相对日期方式显示
========    =============================================

过滤参数主要有：

* `-[num]` ：显示最近 num 次的提交，比如 `-2` 表示最近 2 次的提交。 
* `--author` ：搜索某作者的提交。
* `--commiter` ：搜索某提交者的提交。
* `--grep` ：搜索提交说明文本中包含对应内容的提交。
* `--since/--after` ：显示自从某日期以来的提交，可以是 `--since="2000-01-01“` 或者 `--since="1 year ago"` 形式。
* `--until/--before` ：显示某日期之前的提交。

.. important::
   
   过滤参数中的“搜索”使用时，默认会以逻辑“或”连接，除非添加 `--all-match` 选项。


比较分支间的提交
^^^^^^^^^^^^^^^^^^

还有一种常用的 `log` 命令的操作，用于显示位于某分支但未合并到另一分支的提交。比如显示位于 dev 分支但尚未加入 master 分支的提交、以及在当前分支却不在远程仓库的提交：

.. code-block:: sh
   
   # 两点命令
   $ git log master..dev
   $ git log origin/master..HEAD

如果使用三点命令，则会显示只位于两分支之一的提交。通常使用 `--left-right` 选项来让 git 显示提交位于哪个分支上：

.. code-block:: sh
   
   # 三点命令
   $ git log --left-right master...dev

用 `^` 或者 `--not` 指明你不想查看的提交。比如，查看被 A, B 包含但不被 C 包含的提交，以下两种均可：

.. code-block:: sh
   
   $ git log refA refB ^refC
   $ git log refA refB --not refC


文件操作
-------------

Git 可以管理文件的删除、追踪、移动与重命名。


删除文件：rm
^^^^^^^^^^^^^^^^

手动删除文件不是常规的 git 管理操作，应该使用 `rm` 指令：

.. code-block:: sh
   
   $ git rm <filename>

其中，`<filename>` 可以是文件（夹）名，或者是它们的通配 glob 表达式。下例表示删除 `data` 文件夹下的所有后缀名为 `.log` 的文件：

.. code-block:: sh
   
   git rm data/\*.log

其他选项：

* 选项 `--dry-run` 会显示你将删除的文件（但不执行删除操作），这往往用于检查你的 glob 表达式是否书写正确。
* 选项 `-f` 用来删除已经暂存的文件。这是防止未快照的文件被误删。


放弃追踪文件：rm --cached
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. attention::
   
   特别地，此方法也适用于某文件在之前已经 commit 到了远程仓库（比如 Github），现在想将其从远程仓库中移除的情形。

放弃追踪（untrack）文件：即让 git 放弃记录某一文件的修改状态，但仍保留该文件在磁盘。这一情形通常是你在添加 `.gitignore` 前就进行了 `add` 的误操作.这是你需要 `--cached` 选项：

.. code-block:: sh
   
   $ git rm --cached <filename>


移动或重命名文件：mv
^^^^^^^^^^^^^^^^^^^^^^^

相当于先 `rm` 再 `add`，但是 `mv` 命令更简洁：

.. code-block:: sh
   
   $ git mv <filename_from> <filename_to>



远程仓库操作
------------------

本地的 Git 仓库经常会设置一个远程的仓库，以便将文件分享与备份。如无特殊说明，本文中的远程仓库默认指 `Github <https://github.com/>`_ 仓库。


设置与管理远程仓库：remote
^^^^^^^^^^^^^^^^^^^^^^^^^^^

不只是 Github，所有远程仓库都是类似的。首先你需要指定的远程仓库：

.. code-block:: sh
   
   # git remote add <remote-name> <url>
   $ git remote add origin https://github.com/wklchris/wklchris.github.io

默认地，我们把远程仓库名称叫做 origin；用户也可以使用其他名称。使用 `remote -v` 来查看该本地仓库已配置的远程仓库列表：

.. code-block:: sh
   
   $ git remote -v
   origin  https://github.com/wklchris/wklchris.github.io (fetch)
   origin  https://github.com/wklchris/wklchris.github.io (push)

其中 fetch 表示从哪个远程仓库抓取， push 表示推送到哪个远程仓库。

查看某个特定的远程仓库，使用 `remote show` ：

.. code-block:: sh
   
   $ git remote show <remote-name>

重命名远程仓库，使用 `remote rename`:

.. code-block:: sh
   
   $ git remote rename <old-name> <new-name>

从当前本地仓库已配置的远程仓库列表中，移除某远程仓库：

.. code-block:: sh
   
   $ git remote rm <remote-name>

.. _fetch-and-pull:

抓取与拉取：fetach & pull
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

使用 `fetch` 命令来抓取远程仓库的内容：

.. code-block:: sh
   
   $ git fetch <remote-name>

但这个命令需要你手动进行文件合并操作。如果存在一个分支跟踪远程分支（详见下文分支部分的内容），那么一般使用 `pull` 指令拉取内容；该指令会自动尝试合并文件：

.. code-block:: sh
   
   $ git pull <remote-name>

如果你从某一远程仓库将其 `clone` 到本地，会自动设置跟踪其远程仓库的默认分支（通常叫 master）。之后你的 `pull` 命令会自动从该地址取得数据并尝试合并。

如果要拉取远程仓库的一个非 master 分支（如 dev），只需要在本地切换到同名分支再拉取即可。如果本地的 dev 分支未能正确地匹配到远程仓库的 dev 分支，可以使用 branch 命令的 ``--set-upstream-to/-u`` 参数，然后再拉取：

.. code-block:: sh
   
   $ git checkout dev
   $ git branch -u origin/dev dev
   $ git pull


推送到远程仓库：push
^^^^^^^^^^^^^^^^^^^^^^^^^

.. note::
   
   在从当前计算机的本地仓库推送到 Github 远程仓库之前，请确认您的权限。如果远程仓库为您自己的 Github 账户所创建，请检查您的 Github 账户中是否配置了当前计算机的 SSH 密钥。关于这部分内容，请参考 `使用 SSH 连接到 Github <https://docs.github.com/cn/github/authenticating-to-github/connecting-to-github-with-ssh>`_ 官方帮助页面。

当你的仓库内容处于上游、且你拥有写入权限时，使用 `push` 命令即可推送：

.. code-block:: sh
   
   $ git push origin master

该命令的含义是将本地的 master 分支推送到名为 origin 的远程仓库。如果你当前在 master 分支，且已经设置过它的跟踪分支为 origin/master（参考 :ref:`tracking-branch` ），那么你可以省略分支名，使用更简短的命令：

.. code-block:: sh
 
   $ git push

如果要将所有本地分支都推送到远程，使用：

.. code-block:: sh
   
   $ git push origin --all

上游的含义是在你克隆仓库到推送修改这一时段内，没有新的推送到达远程仓库。例如，如果你和另一个人同时克隆了仓库，但他先于你推送，那么你必须拉取他的内容合并后才能推送你的修改。


标签：tag
---------------

标签是用来标记重要版本的一种手段，以便于回溯。


添加或追加标签
^^^^^^^^^^^^^^^^^

有时我们需要标签来标记节点，比如重要版本是在哪个 commit 发布的：

.. code-block:: sh
   
   $ git tag v1.0

这个语句没有使用任何参数，称为 **轻量标签（Lightweighted tag）** 。它会将 "v1.0" 标签加到最后一次 commit 上。如果你想同时附上一些说明文字，使用 **附注标签（Annotated tag）** ，即用 `-a` 选项：

.. code-block:: sh
   
   $ git tag -a v1.0 -m "This is a new version."

如果需要输入一段多行说明文字，我推荐使用不带 `-m` 的 `-a` 选项：

.. code-block:: sh
   
   $ git tag -a v1.0

上述命令会自动打开编辑器（默认是 vim），输入完文字后，记得用 `:wq` 命令保存，这样标签说明文字才会被正常写入。

如果要添加标签到以往的 commit 位置，可以指定对应 commit 的哈希值（或其前 7 位），例如:

.. code-block:: sh
   
   $ git tag -a v1.0 36e8d6b


查看标签
^^^^^^^^^^^

查看所有的标签，或用上文介绍的 glob 模式来查询：

.. code-block:: sh

   $ git tag
   $ git tag --list "v1.0*"

要查看某一条标签:

.. code-block:: sh
   
   $ git show v1.0


推送标签
^^^^^^^^^^^^^^^

通常 `git push` 命令不会将标签推送到远程仓库，你需要手动推送：

.. code-block:: sh
   
   $ git push origin v1.0

如果你想将尚未推送到远程仓库中的本地标签全部推送，使用 `--tags` 选项：

.. code-block:: sh
   
   $ git push origin --tags


删除标签
^^^^^^^^^^^^

用 `-d` 选项删除标签：

.. code-block:: sh
   
   $ git tag -d v1.0 

即使标签已经被推送到远程，仍然可以从远程删除它，只不过需要加上特殊的前缀 `:refs/tags` ：

.. code-block:: sh
   
   $ git push origin :refs/tags/v1.0

   To https://github.com/wklchris/wklchris.github.io
   - [deleted]         v1.0


回退到标签
^^^^^^^^^^^^^^^^^^^

当你想回退到一个带有标签的 commit 的状态，你可以直接使用标签指令而不需找出它的 SHA-1 值。通常的做法是在标签上创建一个新分支：

.. code-block:: sh
   
   git checkout -b <branch_name> <tag_name>

其中 `checkout -b` 实质是新建分支的命令，我们在下文讨论。


.. _alias:

别名：alias
---------------------

关于别名的使用我们在前文已经有所提及：即配置用户名 `user.name` 与邮箱 `user.email` 。这里有一些常用的例子：

.. code-block:: sh
   
   $ git config --global alias.st status -sb
   $ git config --global alias.unstage 'reset HEAD --'
   $ git config --gloabl alias.last 'log -1 HEAD'

我个人在日常使用中，还将日志命令设置了别名：

.. code-block:: sh
   
   $ git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset:%C(ul yellow)%d%Creset %s (%Cgreen%cr%Creset, %C(bold blue)%an%Creset)' --abbrev-commit"

这样使用 `git lg` 的显示效果比原生的 `git log` 显示舒服得多。


贮藏：stash
-------------------

如果你需要切换分支，但不想为当前分支的工作创建一个提交．这时候需要用 `stash` 将更改到储存到一个栈上：

.. code-block:: sh
   
   $ git stash
   Saved working directory and index state WIP on dev: f435e49 Git: update to rebase.

该命令会储存工作目录和暂存区．现在再运行 `git status` ，工作目录是干净的．如果你不想把已经暂存的部分储藏起来，添加 `--keep-index` 选项．

.. code-block:: sh
   
   $ git stash --keep-index

储藏操作默认只关心已修改或已暂存的跟踪文件，而会忽略工作目录中的未跟踪文件（以及被 `.gitignore` 忽略的文件）。

* 使用 `-u` （或 `--include-untracked` ） 选项，可以将未跟踪文件也加入贮藏。
* 使用 `-a` （或 `--all` ）选项，可以将被忽略的文件也加入贮藏。

.. code-block:: sh
   
   $ git stash -u  # 同时加入未跟踪文件
   $ git stash -a  # 同时加入忽略的文件

查看你的储藏栈：

.. code-block:: sh
   
   $ git stash list
   stash@{0}: WIP on dev: f435e49 Git: update to rebase.


恢复储藏：stash apply
^^^^^^^^^^^^^^^^^^^^^^^^^^

从栈中恢复一个储藏到当前:

.. code-block:: sh
   
   $ git stash apply
   $ git stash apply stash@{0}

其中 `stash@{n}` 如果不指定，会默认恢复栈顶的储藏．

恢复储藏默认会把之前存入的内容都添加到工作目录（也就是说，如果你储藏时暂存区有添加的更改，这部分更改会被退还到工作目录而不是重新暂存）。使用 `--index` 选项以重新恢复暂存，以尽可能地恢复到贮藏前的状态：

.. code-block:: sh
   
   $ git stash apply --index
   On branch dev
   Changes to be committed:
     (use "git reset HEAD <file>..." to unstage)

           modified:   Git/Fundamentals.rst

   Changes not staged for commit:
     (use "git add <file>..." to update what will be committed)
     (use "git checkout -- <file>..." to discard changes in working directory)

           modified:   Git/Fundamentals.rst

.. note::

   如果你尝试恢复到一个储藏点入栈分支之外的分支，或者你的工作目录不是干净的，恢复可能导致问题．比如你建立了一个储藏，却继续在当前位置工作，再尝试恢复．这时，你需要一个新的分支（例如命名为 dev-stash）来帮助你恢复：

   .. code-block:: sh

      $ git stash branch dev-stash


丢弃储藏：stash drop
^^^^^^^^^^^^^^^^^^^^^^^^^

最后，如果恢复操作 `apply` 没有问题，你就可以把该储藏点从栈中丢弃了：

.. code-block:: sh
   
   $ git stash drop stash@{0}
   Dropped stash@{0} (2e843b866b3be25c3a8ccb5dd2c688b258d2d337)

你也可以用 `git stash pop` 来达到“恢复储藏，随即将其从栈中丢弃”的效果．


清理仓库：clean
---------------------

.. warning::
   
   这是一个危险的命令，可能会导致内容丢失。建议总是使用 `-n` 或 `--dry-run` 参数来预演该命令。

清理目录一般使用 `clean` 指令，它会移除所有未被追踪的文件（不包括你的 `.gitignore` 文件中排除的那些）。利用贮藏来将这些文件放入栈中是个更安全的选择：

.. code-block:: sh
   
   $ git stash --all

如果你确认要使用 `clean` 这个危险的命令，可以配合 `-d` 移除未追踪文件以及所有空的子目录。添加 `-f` 选项则意味着强制移除。

.. code-block:: sh
   
   $ git clean -f -d   # 危险的命令！

安全选项 `-n` （或 `--dry-run` ）来执行一次预演，即告诉你这个操作实际上将会移除哪些文件，但此次并不执行移除操作：

.. code-block:: sh
   
   $ git clean -d --dry-run   # 显示 git clean -d 将会移除的内容

最后，该命令还拥有一个选项 `-x` 。它允许你同时也清除那些 `.gitignore` 通配的文件。

