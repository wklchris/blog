完整 F2L
==============

.. admonition:: 手法基础最优先！
   :class: danger

   在学习 CFOP 公式前，请掌握最基础的指法（比如食指中指 U2 轮指、左手无名指做 D 与 D'）以及一些必要手法习惯（比如尽可能地从前手位起手、减少公式中不必要的换手位动作）。一些手法可能初做比较怪异，例如前手位（而不是下手位）的 RUR'U'，但我强烈推荐你学习它们。
   
   在每条公式的\ **肌肉记忆固定之前确保手法习惯的正确**\ ，这一点万分重要的！

.. admonition:: 实用的 F2L 站点
   :class: attention

   * 计时器： csTimer_\ （电脑端），DCTimer（手机端）
   * **F2L 训练器**\ （强烈推荐）：打开 :jperm:`f2l` 并点击 Trainer。你可以筛选需要训练的 PLL 情形（可以通过在 PLL 页面单击公式的图形将其标记为”学习中“（黄色）或者”已学习“（绿色）。在手机上则可以用 DCTimer 训练。
   * 公式查询：
     
     * :alg:`f2l`\ ：AlgDB 与 SpeedCubeDB 可能是最多魔友使用的公式查询站点。
     * :jperm:`f2l`\ ：JPerm 出过非常多的公式与手法教学，包括 F2L 的进阶技巧。     
     * :speedsolving:`pll`

F2L 实际上是从层先法到 CFOP 法中提速最显著的一步。但不同于 PLL 与 OLL，即使不背公式，用之前两步法中提到的 F2L 核心思路也能极大地提升速度。因此，我把学习 F2L 放在了学习 PLL 与 OLL 之后。

标准 F2L 公式不多，但有许多十分重要的非标准情形（一般是利用空槽简化手法），因此学习的压力也不算太小。此外，F2L 可能是最考验魔友观察功底的一步。不是说背下 F2L 的公式，就会比直觉 F2L 的速度有显著提升；这也是许多魔友感受到挫败的一点，所以就更应该把 F2L 放在学习的最后一步，在长期的巩固与练习中寻求提升。

最后，F2L 最重要不是对单个槽能把公式做得多快，而是\ **观察速度以及四槽之间的连贯衔接**。这与练习 PLL 与 OLL 的差异还是很大的，希望读者能够谨记这一点。


F2L 必知概念
---------------

.. admonition:: 必须理解 F2L 的基础概念
   :class: important

   F2L 并不像 PLL 与 OLL 那样，记忆公式后就能迅速提升。要掌握 F2L，我建议至少阅读以下基本概念：

   * 什么是棱块的朝向？正确的棱块朝向是什么意思？
   * 什么是空槽？空槽对解某一组 F2L 有什么帮助？
   * 什么是非标准公式（非标）？

   此外，F2L 与 PLL 一样有多向的概念，甚至更为重要。将 F2L 放入其他位置的槽（而不仅仅是标准的 FR 槽）可以减少转体，而且有时对观察有利（例如，我们复原了难以观察的 LB 槽后，块就不会再出现在那个槽中）。多向公式通常可以利用标准公式的镜像直接得到；少数因为手法原因而无法直接镜像的，将在标准公式中标出。


F2L 棱块的朝向
^^^^^^^^^^^^^^^^^

F2L 易学难精，不仅是因为它需要观察的块与槽更多，而且对同一种魔方情形的不同解法顺序也会影响效率。这里涉及到一个“棱块朝向是否正确”的问题。

任意一组 F2L 的目标块都由一个棱块与一个角块组成。如果一个 F2L 棱块可以只通过 R、U、L 层的转动（不包括转动 F 层），正确地放入目标槽的棱块位，那么我们称此时的棱块\ **朝向正确**\ 。否则，我们称棱块朝向错误。

当我们以 F 面朝前握持魔方时，棱块朝向正确的情况有两种：

* 棱块在顶层，且 F 色（或 B 色）朝上
* 棱块在中层（任何一个槽内），且 F 色（或 B 色）朝前或朝后

.. raw:: html
      
   <div class="roofpig-inline-container">
      <div class="roofpig inline" data-config="alg=L' R U2' L R'|colored=FR D*/e */m|flags=showalg">在槽内，F 色朝前</div>
      <div class="roofpig inline" data-config="alg=R' U R2 U' R'|colored=FR D*/e */m|flags=showalg">在槽内，F 色朝后</div>
      <div class="roofpig inline" data-config="alg=R U R'|colored=FR D*/e */m|flags=showalg">在顶层，且F面颜色朝上</div>
   </div>

.. note::

   请注意，F2L 的棱块朝向是否正确是相对于魔方的当前朝向而言的。如果我们将魔方转动 90 度（y 或者 y'），那么原先朝向正确的 F2L 组会变成朝向错误的，而原先朝向错误的则会变为朝向正确的。

判断一组 F2L 的棱块朝向是否正确，对于 F2L 复原有什么用呢？它可以指示这组 F2L 复原\ **是否需要转体**\ （或者转动 F 层）。绝大部分的 F2L 解法都是转动 R/L 与 U 层，非常顺手；因此朝向错误的 F2L 必须借助于其他“不顺手的转动”来调整棱块朝向，以此完成复原，例如 F 层、双层 r 转、M 层。因此，我们大致可以认为：\ **棱块朝向正确的一组 F2L 是比较容易复原的**\ 。

理想情况下，我们应当优先复原当前朝向正确的所有 F2L 组。然后转体一次魔方，将朝向错误的组变成朝向正确的，并复原它们。这样，我们整个 F2L 中至多只需要一次转体。因此，在完成十字后，我们遵循的 F2L 复原步骤应当是：

1. 观察在当前魔方状态下，哪些 F2L 组的棱块朝向是正确的
2. 复原这些棱块朝向正确的 F2L
3. 转体一次，复原剩下的 F2L


F2L 空槽利用
^^^^^^^^^^^^^^^

F2L 标准公式通常以 FR 槽作为目标槽，且假设其他槽都已经复原。因此，标准公式需要保证在复原 FR 槽时，所有其他的 F2L 槽不会被打乱。但是，在实际的复原过程中，其他槽很可能尚未复原，这称为\ **空槽**\ 。我们无需关心空槽中的块是否被打乱，因此公式可能可以变得更短。一个典型的例子：

* 本例如果使用标准 F2L 公式复原 BR 槽，需要 7 步。
* 在 BR 是空槽时，复原 FR 槽的 F2L 实际只需要 5 步。

.. raw:: html
      
   <div class="roofpig-inline-container">
      <div class="roofpig inline" data-config="alg=R' U2' R2 U R2' U R|colored=FR FRD BR BRD D*/e */m|flags=showalg">标准 F2L 公式</div>
      <div class="roofpig inline" data-config="alg=R' U2' R2 U R'|colored=FR FRD D*/e */m|flags=showalg">利用 BR 空槽</div>
   </div>

有一类著名的空槽利用方法，称为\ **钥孔**\ （keyhole）。它是指目标槽中已经有一个块被正确地归位在内了，那么我们可以借助空槽来快速地归位另一个块。下面是例子：

.. raw:: html
      
   <div class="roofpig-inline-container">
      <div class="roofpig inline" data-config="alg=U' R' F' R U R U' R' F|colored=FR FRD D*/e */m|flags=showalg">标准 F2L 公式</div>
      <div class="roofpig inline" data-config="alg=D' R U' R' D|colored=FR FRD D*/e */m|flags=showalg">钥孔归棱：利用 BR 空槽</div>
   </div>

.. raw:: html
   
   <div class="roofpig-inline-container">
      <div class="roofpig inline" data-config="alg=U' R U' R' U2 R U' R'|colored=FR FRD D*/e */m|flags=showalg">标准 F2L 公式</div>
      <div class="roofpig inline" data-config="alg=u R U' R' u'|colored=FR FRD D*/e */m|flags=showalg">钥孔归角：利用 BR 空槽</div>
   </div>


F2L 非标/高级 F2L
^^^^^^^^^^^^^^^^^^^^^

非标的出现与空槽基于同样的原因，那就是 F2L 的标准公式假设了其余槽都以及复原，只专注于 FR 槽的复原。因此在标准公式中，FR 这组 F2L 的棱块与角块只能出现在顶层或者 FR 槽中。而在实际复原中，我们常常遇到另一种情况，那就是 FR 的块位于其他槽中。这些状态是标准公式中不涵盖的，它们称为非标准状态。

要将非标准状态下的 FR 槽复原，有一种显然的方法是将对应的块从非标准槽位中移出，转化为标准状态，然后我们再用标准 F2L 公式解决。直接利用另外开发的公式比转化为标准状态再解可能更快，而这些公式就是非标公式。

一个简单的非标例子：

.. raw:: html
   
   <div class="roofpig-inline-container">
     <div class="roofpig inline" data-config="alg=L' U2 L R U R' U2 R U' R'|setupmoves=L' R U R' L U L' U2 L R U R' U2 R U' R'|colored=DFR FR D*/e */m|flags=showalg">直接移出后解标态</div>
     <div class="roofpig inline" data-config="alg=U' L' R U' R' L|colored=DFR FR D*/e */m|flags=showalg">非标</div>
   </div>


F2L 的标准公式（及多向）
--------------------------

以下是完整的 OLL 公式表，总计有 41 种标准情形。绝大部分情形的多向公式都可以通过镜像直接得到：

* 左右镜像：将入槽位改为 LF，转动 R 层改为转动 L 层，反转 U 层的旋转方向。
* 前后镜像：将入槽位改为 BR，反转转动 R 层与 U 层的旋转方向。

本表将列出的多向情形包括：

* 直接镜像后手法难以实现的情形
* 多向的棱角分离方式与标准公式不同的情形
* 标准公式较为难解的情形

以上情形之外的多向则不会在表中列出。本表中的多向公式主要收录以 RB 槽为目标槽的情况。

在本表中，我用角块、棱块朝上的颜色以及棱块的位置来描述每一种倾向。例如，“角前后棱右”表示角块朝上的颜色与前面（F 面）相同，棱块位于后面（B 面），且朝上的颜色与右面（R 面）相同。

.. note::
   
   一些学习 F2L 之前的注意点：

   1. 比起记忆 F2L 公式，更推荐自己推断直觉 F2L 公式。
   2. 将自己推断的直觉 F2L 公式与标准 F2L 公式对比，对每一种情况使用这二者中更顺手的。
   3. 如果不计起手时的转体，任何正确的 F2L 公式的转体都不会超过一次。如果你自己推断的某个直觉 F2L 公式使用了超过一次的转体，请从下面的标准 F2L 中学习正确的做法！

.. raw:: html
   :file: tools/F2L.html


F2L 扩展阅读
-------------------

.. note::

   本节提到了比普通 CFOP 更高级的方法；它们无需在学习 CFOP 时掌握，这里仅作了解之用。本文也不详细介绍这部分的内容。

F2L 如何与十字（Cross）与顶面（OLL）复原衔接？

* XCross：指在复原底面十字时，顺便做好一组 F2L。类似地，XXCross 表示顺便做好两组，以此类推。这属于十字的高级内容。下面是对同一个十字情形 XCross 的简单例子；XCross 的解法比最优十字多一步，但是它同时复原了一组 F2L。

  .. raw:: html
      
      <div class="roofpig-inline-container">
        <div class="roofpig inline" data-config="alg=R' F R|setupmoves=L F L' U2 R' F R|colored=DFR FR D*/e */m|flags=showalg">最快复原十字</div>
        <div class="roofpig inline" data-config="alg=U2 L F' L'|setupmoves=L F L' U2 U2 L F' L'|colored=DFR FR D*/e */m|flags=showalg">XCross十字</div>
      </div>

* 控棱：指在复原最后一组 F2L 时，通过采用不同的复原方法来控制顶面棱块的朝向，以避免复杂的顶面情况（例如点型 OLL）。下面是对同一个最后一组 F2L 情形，直接还原与控棱的简单对比。

   .. raw:: html
      
      <div class="roofpig-inline-container">
        <div class="roofpig inline" data-config="alg=U R U' R'|setupmoves=F R' F' R U2' F R' F' R2' U2' R'|colored=u- u/e u/m|flags=showalg">直接还原</div>
        <div class="roofpig inline" data-config="alg=R' F R F'|setupmoves=F R' F' R U2' F R' F' R2' U2' R' R U R' U' R' F R F'|colored=u- u/e u/m|flags=showalg">控棱</div>
      </div>
