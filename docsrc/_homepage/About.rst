本站历史
===========

本站的发展史。

* 个人主站点 `wklchris.github.io`_ 在我的 Github 帐号下（wklchris_）的同名仓库开源。
* 博客子站点（当前站点）在 `wklchris/blog`_ 仓库开源。

更新日志
------------

以下是本站的更新日志。日志包括了迁移前的站点的内容。

* 2023年

  * 3月，整理了之前开坑的多篇博文内容，并将它们更新到主分支。
    
    * 将 Sphinx 升级到 6.x 后对网页进行了测试。
    * Rubik 博文成为了本站第一篇使用复杂 JS 动画的博文。
    * 为了衔接 Roofpig_ 动画库与 Sphinx 引擎，我还专门写了一个表格转 HTML 文件的 formatter 工具，并覆写了相当数量的 CSS。这可能是我在 Web 实现上花费时间最长的一篇博文。

* 2022年
  
  * 8月
    
    * 修复了一个博客站点基础模板 layout.html 的 JS 引用错误。
    * 修复了在 MathJax 中引用 LaTeX 公式时，使用 ``\label`` 命令不显示编号的问题。
    * 注意到了 Sphinx 定义的 admonition 命令（如 note）不能正常显示标题，必须通过 ``:class:`` 参数指定的特性。修改了与此相关的页面。
    * 优化了网站 _static 路径的加载内容。
  
  * 1月，在我自己开发的 Simrofy_ 主题上完成了个人站点的重建，并更新到了原 wklchris.github.io 域名，\ **恭喜本站成功来到了 v2.0 时代！**\ 关停了之前测试用的 self-contained 域名。

* 2021年
  
  * 11月，本地整理完成。向 blog 仓库开始更新，并继续在本地进行测试。
  * 9月底，收到学术参会邀请。尽管不清楚是否有机会向他人展示个人站点，但仍决定在参会前完成站点重建工作。开始从 self-contained 域名向原 io 站点迁移。
  * 上半年，主要在进行学位论文的工作，因此在站点这边没有太多进展。
    
    * 继续 Simrofy_ 开发，尝试将早期版本发布到 Pypi。
    * 测试新站点情况，并确认已能够收到 Google Analytics 报告。

* 2020年
  
  * 9月，开始新站点的模板开发工作，即名为 Simrofy_ 的网页模板。
  * 8月底，提交了站点地图，等待 Google Search Console 的确认。
  * 8月中，正在添加站点到搜索引擎，等待 Google Search Console 的确认。
  * 8月初，结束功能性测试。在个人账户下创建了组织 self-contained，开始向其下的 self-contained.github.io 域名迁移旧博客。
  * 7月下，检测了测试仓库多日的访问量，确认 Google Analytics 可以正常运作。
  * 7月中，在 Sphinx 主站找到了一份 Google Analytics 的嵌入示例，测试后已能正常匹配。
  * 4月下，尝试加入 Google Analytics 的功能，未能实现。
  * 3月下，编写了 Python 的文档管理脚本，并添加了 404 导航页面。
  * 1月初，开始在另外的仓库进行功能性测试。

    1. 重新组织了文档结构，利用了 Github Pages 的 `docs/` 主页功能。
    2. 重写了 Sphinx 的生成器 `make.bat` 的部分功能。
    3. 寻找了 `.nojekyll` 的解决方案，测试站点部分上线。

* 2019年

  * 11月，开始正式用 Sphinx 重写站点。当时最大的两个难点是 Google Analytics 的部署，以及站内中文搜索的支持。
  * 10月，确认了 Sphinx 插件对 Jupyter Notebook 有很好的支持效果，大大优于旧站点我自写的转 Markdown 的处理方法。决定启动个人博客站点的重构与维护计划。
  * 9月，沉迷于 Sphinx 简约而稳重的 Read the Doc 主题。因而萌生了重写旧站点的想法。
  * 一直到7月初，我陆续在 gitbook 仓库的 gh-pages 分支进行更新。这部分内容不同于过往，组织上也稍显杂乱，因此并没有直接在旧博客站点更新。

* 2018年
  
  * 10月15日，发现了专用于生成技术文档网页的工具 `Sphinx`_ 。由于头痛于 rst 写作，加上没有去探索好看的主题，所以我并没有深入研究。但我此时实质上已经放弃了 Gitbook。
  * 10月，发现了 `Gitbook <https://docs.gitbook.com/>`_ 工具，使用了一段时间，并无感。
  * 年中处于忙碌状态。
  * 1月15日，旧站点 wklchris.github.io 的最后一次博文更新，是为 D3.js 课程准备的 JavaScript 内容。

* 2017年

  * 10月，优化了移动设备的体验。
  * 7月中，撰写了一篇 FFmpeg 的博文。这是本站点第一篇编程以外的技术文章。
  * 6月中，新加并更新完毕 Matplotlib 博文。这是我旧站点中最满意的一篇文章，我也借此非常系统地学习了当时的 Matplotlib 2 文档。
  * 6月初，更新了一篇围棋的博文。这是本站点第一篇非技术文章，起因是遇到了会下围棋的外国友人。
  * 2月下到3月中，更新完毕 Python 的 numpy 与 pandas。当时的 Python 知识正处于稳步上升期。
  * 1月下到2月下，更新完毕 R 的 8 篇内容。这是站内最长的系列文章。起因是当时的课程正在教授 R，我就边学边整理了。
  * 1月7日，我的第一篇博客！使用的是 Jekyll 的 `minima <https://github.com/jekyll/minima>`_ 主题。

* 2016年

  * 在2016年下半年，注意到了好友 Snowkylin 的 github.io 站点：\ `snowkylin.github.io`_ 。


