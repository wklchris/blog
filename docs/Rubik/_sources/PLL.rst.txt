完整 PLL
=============

.. admonition:: 手法基础最优先！
   :class: danger

   在学习 CFOP 公式前，请掌握最基础的指法（比如食指中指 U2 轮指、左手无名指做 D 与 D'）以及一些必要手法习惯（比如尽可能地从前手位起手、减少公式中不必要的换手位动作）。一些手法可能初做比较怪异，例如前手位（而不是下手位）的 RUR'U'，但我强烈推荐你学习它们。
   
   在每条公式的\ **肌肉记忆固定之前确保手法习惯的正确**\ ，这一点万分重要的！

本节给出了针对标准 PLL 的所有 21 种情形的 *我正/曾使用过或觉得顺手的* 公式，其中也包括了上面在两步 PLL 中的 6 个公式。

.. admonition:: 实用的 PLL 站点
   :class: attention

   * 计时器： csTimer_\ （电脑端），DCTimer（手机端）
   * **PLL 训练器**\ （强烈推荐）：打开 :jperm:`pll` 并点击 Trainer。你可以筛选需要训练的 PLL 情形（可以通过在 PLL 页面单击公式的图形将其标记为”学习中“（黄色）或者”已学习“（绿色）。在手机上则可以用 DCTimer 训练。
   * 公式查询：
     
     * :algdb:`pll`\ ：可能是最多魔友使用的公式查询站点。
     * :jperm:`pll`\ ：JPerm 出过非常多的公式与手法教学，但请注意他有部分公式是左手流的。
     * :speedsolving:`pll`

.. admonition:: 方括号标记的字母是什么意思（AUF）？
   :class: hint

   在 PLL 公式中可能会看到带有方括号的记号，比如 ``[U]``\ ，这表示这一步只是在转动顶层。这是由于 PLL 公式的起手不依赖于侧面中心块的颜色，因此复原顶层后（或者在起手前）顶层可能还需要转动；这种转动称为 **顶层调整**\ （Adjustment to Upper Face，AUF）。在顶层与中心块没有对齐的情况下，这个方括号标记的手法可能会被省略，或者用其他的顶层转动的操作（比如 ``[U2]``\ ）代替——取决于具体的起手情况。
   
   例如，在 PLL Z 双邻棱交换公式中最后需要做一个 ``[U2]``\ 。以红绿棱、黄蓝棱交换时顶层的红绿红一面朝前为例，标准公式这仅限于红绿红对准红色面（也就是F面中心块是红色）的情形。如果在起始时，红绿红是与橙色面对齐的，那么最后这个 ``U2`` 就可以省略；如果起手时与绿色面对齐，那么需要用 ``U'`` 代替 ``U2``。

   .. raw:: html
      
      <div class="roofpig-inline-container">
        <div class="roofpig inline" data-config="alg=M2' U M2' U M' U2 M2' U2 M' U2|flags=showalg|algdisplay=2p">PLL Z：红绿红对齐红色面，AUF=U2</div>
        <div class="roofpig inline" data-config="alg=M2' U M2' U M' U2 M2' U2 M'|setupmoves=y2|flags=showalg|algdisplay=2p">红绿红对齐橙色面时，无AUF</div>
        <div class="roofpig inline" data-config="alg=M2' U M2' U M' U2 M2' U2 M' U'|setupmoves=y|flags=showalg|algdisplay=2p">红绿红对齐绿色面时，AUF=U'</div>
      </div>

   因此，专业的选手可能会对一种 PLL 情形记忆多向的复原公式，以省略各种不同起手情况下 AUF 所需要的时间。但在 PLL 学习过程中，这并不是必须的；你完全可以用 AUF 甚至魔方转体来找到公式要求的起手位置。

以下是完整的 PLL 公式表，总计有 21 种情形（绝大部分公式都可以从\ **前手位**\ 起手！）。在交流中，我们往往使用 PLL 的符号名称（例如 PLL Na/Nb，统称为 PLL N 或 N Perm），而不是用 PLL 序号。

.. raw:: html
   :file: tools/PLL.html


.. raw:: html
   :file: tools/roofpig_styler.html