CFOP 方法
=============

.. note::

   如无特殊说明，本文中的魔方在复原过程中，均以白色面为底面、黄色面为顶面。

   * 本文中所有给公式情形的命名大都源于本人的习惯，并不一定是被大众接受的名称。这其中可能还包含了围棋术语。
   * 本文中所有公式的括号（即手法组）都源于本人的复原习惯，请不必拘泥。
   * 淡绿色背景的公式表示对于此情形 *我个人比较推荐* 的公式。
   * 推荐的魔方复原计时练习站点：csTimer_ .


CFOP 方法是由美籍捷克斯诺伐克（现捷克共和国）人 Jessica Fridrich（1964-）于 1981 年左右主导发明的三阶魔方复原方法，因此这种方法也以她的名字命名为 Fridrich 方法。这种方法自 2000 年以来几乎被所有的顶级魔方选手采用。

CFOP 这四个字母是该方法复原魔方所需的四个步骤 (**C**\ ross, **F**\ 2L, **O**\ LL 与 **P**\ LL) 的英文缩写，它们分别指：

* **底面十字**\ （Cross）：指选定一个颜色作为底面，还原该面的 4 个棱块。
* **前两层**\ （First 2 Layers, F2L）：在这一步中，同时复原底层与中层（即 4 个底层角块与 4 个中层棱块）。
* **顶层朝向**\ （Orientation of the Last Layer, OLL）：复原顶面，即令顶层所有块顶面颜色朝上。
* **顶层排列**\ （Permutation of the Last Layer, PLL）：复原整个顶层，也即完成整个魔方的复原。

CFOP 方法通过以上四步完成魔方的复原。理论上它包含了 119 个需要记忆的公式，不过一般认为 F2L 部分的公式不需要全部记忆。对于惧怕记忆公式的学习者来说，好消息是即使只学习到了 F2L 的思路，前两层的速度也会极大提升；如果能背下 OLL 在顶面十字完成后的 7 个公式（即两步 OLL），速度又会有一定提升；如果能背下 PLL 的公式 2 个两棱两角公式、2 个三角公式与 4 个棱换公式（即两步 PLL，以上公式中有 2 个在层先法中已经学习过），速度又会有一定提升。

因此，我个人建议的 CFOP 学习顺序如下：

* 底面十字
* F2L 的核心思路
* OLL 的十字公式（两步 OLL）
* PLL 的基础棱角公式（两步 PLL）
* 剩下的 PLL 公式
* 剩下的 OLL 公式
* 记忆 F2L 中比自己思考出的步骤更巧妙的那些公式
* 剩下的 F2L 公式
* 寻找 FOP 公式的非标准方法（非标），比较它们与标准公式的优缺点
* 精进底面十字
* 不断练习直到达到极限
* 考虑 *是否有必要* 学习更高阶的步骤或方法，比如 XCROSS、WV、ZBLL、COLL 等。

在下文中，我也会大致按照此顺序对 CFOP 进行介绍。但不同的是，我会将一些我认为有价值的非标公式与标准公式一起介绍，不再新设非标章节。


底面十字
----------

底面十字是魔方解法中的一个重要基础。以白色为底面，那么底面十字就是指将白红、白绿、白橙、白蓝这四个棱块还原到到正确的位置与朝向。下面是一个例子（可以用鼠标拖拽来移动视角）。为清晰起见，下例中只保留了中心块与底面棱块的颜色。

.. raw:: html
   
   <div class="roofpig" data-config="alg=L U L R' F' l' D' x'|colored=D*/e */m|flags=showalg">底面十字示例</div>

底面十字是 CFOP 复原法的最基础、最先进行步骤，但并不意味着它是最简单的。专业的魔方选手往往可以在 1 秒中只能做好底面十字（并使底面朝下，便于衔接 CFOP 中的第二步 F2L），这需要专注于思考四个底面棱块的移动方式，并在复位一个棱块的同时尽量兼顾其他棱块，从而减少所需的拧动次数。

一些方法论：

* 熟记各面中心块的相对位置。只要底面十字的四个棱块被还原为相对位置正确的情况，那么通过旋转底层就能还原它们的绝对位置。
* 在观察时，不要思考除了底面中心块、底面棱块这 5 个块以外的任何内容。其他的块不是在十字这一步需要关心的。
* 不要一个一个地还原底面棱块，而是将两个甚至更多的底面棱块作为一组来思考。尝试在还原某个棱块的过程中，兼顾组内的其他棱块。这对于朝向不正确的棱块复原尤其有帮助。
* 如果底面棱块分组不可行或步骤繁琐，请思考新的分组可能。
* 预测在还原第一组后其余底面棱块的位置，并思考复原它们的步骤。这是一气呵成的关键。
* 如果尚有余力，预测第一组 F2L 的两个块的位置。如果有可能，优化十字的手法，顺便完成第一组 F2L.

.. raw:: html
   
   <div class="roofpig-inline-container">
     <div class="roofpig inline" data-config="alg=R' U' R' F|colored=FD RD */m|flags=showalg">示例1：RF 两棱一组</div>
     <div class="roofpig inline" data-config="alg=R' D' U' F L R2|colored=FD RD LD */m|flags=showalg">示例2：RFL 三棱一组</div>
     <div class="roofpig inline" data-config="alg=R  D  L2 D2 F  L2|colored=D*/e */m|flags=showalg">示例3：完整的十字示例</div>
   </div>

更多的学习方法，可以参考其他选手撰写的十字教程（例如张砷镓《十字天书》）。也可以慢放比赛录像，根据打乱公式来学习比赛选手的底面十字思路。


F2L 核心思路
---------------


OLL 的十字公式（两步 OLL）
------------------------------

两步 OLL（2 Look OLL）是从层先向标准 OLL 过渡的一种方法。它将顶面还原分为两步：第一步，在顶面搭建十字；第二步，按照 OLL 公式中对带有十字情形的还原方法来还原顶面。

顶面十字
^^^^^^^^^^^^^

先说第一步，顶面十字——这其实在在层先法中我们已经学习过，公式是： ``F(RUR'U')F‘``。我们这里添加一个新的公式，也就是逆做该公式的 ``F(URU'R')F'``\ （不太推荐）或者其变体 ``f(RUR'U')f'``\ （推荐），也都比较顺手。

.. raw:: html

    <div class="roofpig-inline-container">
      <div class="roofpig inline recommend" data-config="alg=F R U R' U' F'|colored=U*/e */m|setupmoves=F R U R' U' F'|flags=showalg">顶面十字</div>
      <div class="roofpig inline" data-config="alg=F U R U' R' F'|colored=U*/e */m|setupmoves=F U R U' R' F'|flags=showalg">顶面逆十字</div>
      <div class="roofpig inline recommend" data-config="alg=f R U R' U' f'|colored=U*/e */m|setupmoves=F U R U' R' F'|flags=showalg">顶面逆十字变体</div>
    </div>

只观察顶面的棱块，我们会发现顶面十字公式的作用也十分明显：它变更了前（UF，图中黄红）、右（UR，图中黄绿）以及后（UB，图中黄橙）三个顶面棱块的位置与朝向。实质上， **十字公式翻转了前、后棱块的朝向**\ ，被翻转朝向的棱块会放在右、前两面。类似地， **逆十字公式翻转了右、前棱块的朝向**，被翻转朝向的棱块会被放在前、后两面（变体则是旋转 180 度的情形）。

明白了这一点后，我们就知道应该如何应用顶面十字公式了：

1. 如果在顶面拼出了“直三”，即有一对相对的棱块顶面朝上，这时候只需将直三横放（将这两个棱块对准左、右两面），然后使用顶面十字公式，就能翻转前、后两个朝向错误的棱块，完成顶面十字。
2. 类似的，如果在顶面拼出了“弯三”，即有两个相邻的棱块顶面朝上，这时候只需将弯三放在左后侧使用逆十字公式（或者放在右前侧，使用逆十字变体），即可完成顶面十字。
3. 当顶面四个棱块朝向均错误时（点型），使用顶面公式会将翻转前、后棱块，使他们顶面朝上，放到右、前两面。因此，会在顶面右前形成一个“弯三”形状。我们可以对顶面 U2，然后像上一种情况一样对弯三做逆十字（或者直接用逆十字变体）。

综上，要完成顶面十字，直三需要用一次正做，弯三需要一次逆做变体，点型则需要一次顺做接一次逆变体。

.. raw:: html

    <div class="roofpig-inline-container">
      <div class="roofpig inline" data-config="alg=F R U R' U' F'|colored=u/me|flags=showalg">直三横放，顺十字</div>
      <div class="roofpig inline" data-config="alg=f R U R' U' f'|colored=u/me|flags=showalg">弯三右下，逆十字变体</div>
      <div class="roofpig inline" data-config="alg=F R U R' U' F' f R U R' U' f'|colored=u/me|flags=showalg">点型，顺接逆变体</div>
    </div>


7 个十字 OLL 公式
^^^^^^^^^^^^^^^^^^^

在拼出顶面十字之后，顶面其实只有 7 种情形：两种小鱼（OLL 26、27），两种十字（OLL 21、22），两种由字（OLL 23、24），以及一种梅花七（OLL 25）。

两种小鱼（Sune），这个我们在层先法中就应该很熟悉了。观察三个朝向不正确的角块，如果它们转动到顶面的右前角块的位置时，顶面的颜色朝前，那么它是正小鱼，鱼头朝左前，RU起手；如果顶面的颜色朝右，那么它是反小鱼，鱼头朝右上，RU2起手。口诀：\ **前左U，右后U2**

.. raw:: html

    <div class="roofpig-inline-container">
      <div class="roofpig inline recommend" data-config="alg=R U R' U R U2 R'|colored=u|flags=showalg">OLL 27：正小鱼</div>
      <div class="roofpig inline recommend" data-config="alg=R U2 R' U' R U' R'|colored=u|flags=showalg">OLL 26：反小鱼</div>
    </div>

两种十字型，即顶面所有的角块朝向都不正确。一种是角块的顶色朝向分布在两个侧面的（2+2），需要将这两个侧面放在前后两面，然后做 ``RU2(R'U'RU)R'U'(RU'R')``；或者将它们放在左右两面，然后做变体 ``RU(R'URU')R'U(RU2R')``\ （我觉得这个变体不太顺手）。另一种十字型是角块的顶色朝向分布在三个侧面（1+1+2），旋转顶层使有 2 个顶色的那一面朝左，然后做 ``RU2(R2'U'R2U')(R2'U2R)``。

.. raw:: html

    <div class="roofpig-inline-container">
      <div class="roofpig inline recommend" data-config="alg=R U2 R' U' R U R' U' R U' R'|colored=u|flags=showalg">OLL 21：双对称十字</div>
      <div class="roofpig inline" data-config="alg=R U R' U R U' R' U R U2 R'|colored=u|flags=showalg">OLL 21：双对称十字（变体）</div>
      <div class="roofpig inline recommend" data-config="alg=R U2 R2' U' R2 U' R2' U2 R|colored=u|flags=showalg">OLL 22：单对称十字</div>
    </div>

两种“由”字型，即顶面只有一侧的两个角块朝向不正确。一种是这两个角块的顶色朝向同一个侧面，那么让它们朝向后侧，然后做 ``R2D'(RU2R')D(RU2R)``\ （这可能是这 7 个 OLL 公式里比较难记的一个）。或者，让这两个顶色朝向前侧，然后做镜像变体公式 ``R2D(R'U2R)D'(R'U2R')``。

另一种是这两个角块的顶色朝向两个不同的侧面，那么旋转顶层使两个朝向正确的角块位于右侧，然后做 ``(rUR'U')r'(FRF')``；不过我个人有时候会使用变体 ``(rUR'U')(L'U)(RU')x'``，优点是不用中途更换握持魔方的姿态，缺点是做完以后需要一个翻转魔方的动作。

.. raw:: html

    <div class="roofpig-inline-container">
      <div class="roofpig inline recommend" data-config="alg=R2 D' R U2 R' D R U2 R|colored=u|flags=showalg">OLL 23：同向由字</div>
      <div class="roofpig inline" data-config="alg=R2 D R' U2 R D' R' U2 R'|colored=u|flags=showalg">OLL 23：同向由字（镜像变体）</div>
    </div>

.. raw:: html

    <div class="roofpig-inline-container">
      <div class="roofpig inline recommend" data-config="alg=r U R' U' r' F R F'|colored=u|flags=showalg">OLL 24：对向由字</div>
      <div class="roofpig inline" data-config="alg=r U R' U' L' U R U' x'|colored=u|flags=showalg">OLL 24：对向由字（变体）</div>
    </div>

最后是梅花七型，即顶面只有两个呈对角关系的角块朝向不正确。旋转顶层，直到右下角的角块顶色朝前，然后做 ``F'(rUR' U')(r'FR)``。

.. raw:: html

    <div class="roofpig recommend" data-config="alg=F' r U R' U' r' F R|colored=u|flags=showalg">OLL 25：梅花七</div>

至此，你以及可以用两步 OLL 来完成顶面的复原了！这种方法相比层先法中复原顶面的方法的优势，主要在于归纳了顶面十字的快速搭建方法，并通过 7 个公式加快了复杂情形的解决速度（尤其是由字、梅花七）。


PLL 的基础棱角公式（两步 PLL）
---------------------------------


完整的 PLL
-------------


完整的 OLL
-------------


部分巧妙 F2L 公式
--------------------


完整的 F2L 公式
-------------------



.. _csTimer: https://cstimer.net/