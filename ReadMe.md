# Blog 博文 <!-- omit in TOC -->

这时我个人 Github Page ([wklchris.github.io](wklchris.github.io)) 页面的博文仓库。 

下文将介绍如何使用该仓库中的工具或模板：
- [依赖项](#依赖项)
- [模板结构](#模板结构)
- [make.py 工具](#makepy-工具)
  - [创建新文档](#创建新文档)
  - [构建文档](#构建文档)
  - [移除文档](#移除文档)
  - [本地预览](#本地预览)
- [ju.ps1 脚本](#jups1-脚本)
- [其他注意事项：nojekyll](#其他注意事项nojekyll)
- [许可证](#许可证)


## 依赖项

本站使用网页文档构建工具 [Sphinx](https://www.sphinx-doc.org/) 构建。要使用本站模板，请先安装 Python (>=3.6)，并安装以下库：

- sphinx
- sphinx-rtd-theme
- sphinx-copybutton

可以使用 `Python` 自带的 `pip` 工具进行安装，命令行如下，
```powershell
pip install sphinx sphinx-rtd-theme nbsphinx sphinx-copybutton
```

本仓库的开发环境是 Windows 10，并未在其他环境下测试。已知的 macOS/Linux 不兼容有：
- `make.py`：`--server` 参数调用了 Powershell 来打开网页文件。

## 模板结构

本仓库的 Github Pages 功能定位于 master 分支的 `docs/` 文件夹，这可以在 Github 仓库的设置中进行配置。

> 读者如果要使用本站的模板，请保留以下列出的所有关键文件，并用 `make.py` 文件来管理博文。

关键文件：
- `make.py`：原 `make.bat` / `Makefile` 的优化替代。
- `ju.ps1`：一个快速以文档文件夹为工作目录启动 Jupyter Notebook 的脚本。
- `docs\`
  - `_config\`：全局文件。
    - `db.json`：全站的文档 meta 数据。
    - `hyperconf.json`，`index.html`，`index.rst`：用于初始化文档仓库的文件。
    - `index-homepage.rst`：用于更新主页的模板文件。
  - `.nojekyll`：阻止 Github Pages 的 Jekyll 功能。
- `docsrc\`
  - `_homepage\`: 主网站页面的源文件夹。
    - `404.rst`：网站内的 404 错误提示页。
    - `conf.py`：屏蔽了 homepage 的 template，准备稍加自定义。
  - `_static\`：样式文件。
    - `homepage_style.css`：专为 homepage 定制的 CSS 文件。
    - `style.css`：普通博文的 CSS 文件。
  - `_templates\layout.html`
    - 配置了侧边栏的“返回主页”按钮。
    - 配置了 Google Analytics。

网站的主页使用了 DataTables 来呈现博文列表，其路径在 `docs/_config/static/DataTables`。值得注意的是，由于 `requirejs` 的存在，`DataTables` 必须以一种不同于官网的形式调用（见 `docsrc/_templates/layout.html` 中的 `require.config()` 部分）——尽管只有主页需要它，但目前它会在所有页面上都被加载。

使用 `make.py` 初始化的 `index.rst` 文件均带有文档头，用于记录文档的数据并存储在 `config/db.json` 中。例如：
```rst
.. meta::
   :category: Python
   :keywords: python,matplotlib,plot,computing
   :series: Python-libs
   :series_num: 1
   :abstract: 本文介绍了 Python 最广为使用的科学绘图库 Matplotlib
```

各个键的功能仍在开发中，目前的设想有：
- [x] category：主页的博文列表按照 category 进行分类。
- [ ] keywords
- [ ] series：同 series 的博文互相推荐，并引导读者按序阅读。
- [x] abstract：主页的博文列表中展示文章摘要。


## make.py 工具

仓库中的 `make.py` 是本人编写的文档快速管理工具，用法是：

```powershell
python make.py [-h] 
    [--build | --create | --remove | --server]
    [--title TITLE [TITLE ...]]
    [--no-update-homepage]
    docname
```

对于 Windows 用户，如果在 `PATH_EXT` 环境变量中加上对 `;.py` 的执行支持，并将 `.py` 文件的默认打开方式设置为了 Python 解释器，那么可以省略最前面的 `python` 前缀；在下述内容中，该前缀默认省略。

各参数：
- `-h`：显示帮助。
- 互斥参数组：以下三个参数最多只能同时传入1个。
  - `--build` / `-b`：（默认）网页构建模式。
  - `--create` / `-c`：创建模式。
    - `--title` / `-t`：指定文档一个与项目名称不同的标题。仅在创建模式生效。
  - `--remove` / `-R`：删除模式。
  - `--server` / `-s`：本地服务器模式。
- `--no-update-homepage` / `-N`：在构建或删除文档时，不自动更新全站主页。仅在构建或删除模式生效。
- `docname`：必选参数。文档项目名称，同时也是文档文件夹的名称。

以下样例均在 Windows 10，**Powershell 环境**中执行。请注意，在 CMD 中的表现很可能不同。

### 创建新文档

用 `--create/-c` 参数创建一个名为 `doc1` 的文档，路径在 `docsrc/doc1`。它会被自动初始化，加入 `index.rst`，`index.html` 与 `conf.py`。

```powershell
./make.py -c doc1
```

文档内标题默认与项目名相同。如果要指定一个文档内标题，使用 `--title/-t` 参数来配合 `--create/-c` 参数：

```powershell
./make.py -c doc1 -t Long title with spaces
```

特别地，`-t` 参数允许带空格；上例的 `doc1` 文档标题即为 `Long title with spaces`。

### 构建文档

使用 `--build/-b` 参数（或者省略）来构建文档，将其转为 HTML。构建后的 HTML 会临时生成在 `docsrc/doc1/build` 文件夹中，随后 `docsrc/doc1/build/html` 中的所有文件会被移动到 `docs/doc1` 中，然后临时文件夹 `build` 会被删除。

```powershell
./make.py doc1
```

同时，该命令还会尝试自动更新数据库 `db.json`，并自动构建主页（从 `docsrc/_hompage` 到 `docs/`）。因此用户会在控制台中观察到两次 sphinx 构建。如果用户不想自动构建主页，可以添加 `--no-update-homepage/-N` 参数：

```powershell
./make.py -N doc1
```

* 如果要单独构建主页，请使用 `-N` 参数： `./make.py -N _homepage`

### 移除文档

使用 `--remove/-R` 参数来移除指定的文档。

```powershell
./make.py -R doc1
```

该文档的所有记录均会被删除，包括：
- 源文件：移除整个 `docsrc/doc1` 文件夹；
- 数据库记录：移除 `db.json` 中所有关于文档 `doc1` 的记录项；
- 主页的文档列表：（如果未使用 `--no-update-homepage/-N` 参数）在更新数据库后，主页会自动重编译，以保证 `doc1` 已经从列表中被移除。

### 本地预览

> 部分线上功能必须通过 HTTP 服务才能测试（请记得按 Ctrl + F5 刷新页面缓存），仅仅在本地双击打开 HTML 文件是不行的。

使用 `--server/-s` 参数来在 `docs/` 文件夹搭建本地 HTTP 服务（默认 `http://localhost:8000`），并自动使用浏览器打开 `doc1` 项目的 HTML 主页：

```powershell
./make.py -s doc1
```

按 Enter 键（推荐），或者按 Ctrl + C 强制打断，即可中止该本地服务器。注意，在浏览器打开的选项卡过多时，中止操作可能会变得不灵敏。


## ju.ps1 脚本

该脚本帮助用户迅速以给定文档名所在的目录为工作目录，打开 Jupyter Notebook 服务。例如，下面的命令会以 `docsrc/Python/` 为工作目录运行 Jupyter Notebook 服务： 

```powershell
./ju.ps1 Python
```

## 其他注意事项：nojekyll

本仓库是作为个人 github.io 域名的次级域名启用的，Github Pages 服务的运行根目录需要在仓库的设置中设置为 `docs/` 目录。

特别注意，此种情形下，`.nojekyll` 文件应该放在 `docs/` 目录下，而不是根目录中。否则会引起无法加载 CSS 等文件的问题。


## 许可证

[MIT](./LICENSE)
