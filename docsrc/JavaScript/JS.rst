JavaScript 语法
====================

.. note::

   * 本文\ **至少基于 ES6 标准**\ （甚至更新），也即 JavaScript 第二代（Second Major Revision）标准。
   * 本文中的许多写法带有本人的风格化的特征。如果在多种写法中我偏向于特定的某一种，我会作出相应说明。

   总之，本文是一篇或多或少带有个人风格的 JavaScript 语法介绍。如果你想要查看更客观、更详细的介绍，那我向您推荐 Mozilla 的\ `重新介绍 JavaScript <https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Language_Overview>`_\ 。


JavaScript（简称 JS）是一种面向网页的语言。可以说任何精美、复杂的现代网页，都不可能只用纯 HTML/CSS 写就而不涉及 JavaScript。此外，它的名字中虽然带着 Java，但它从强弱类型、编译等方面上来说与 Java 语言并没有什么关系。

除了 JavaScript 初始语法，ECMA_ 还提出了一套称为 ECMAScript（简称 ES）的语法标准。依此，我们一般把 ES5 （2009 年）版本称为第一代标准，ES6（2015 年）称为第二代标准；而早于 ES5 的，大概就不能算现代 JavaScript 了（笑）。在 ES6 之后，ES 标准改为按照年份进行命名，并基本上每年迭代一次。不过需要注意的是，网页浏览器并不是总能及时支持最新的 ES 版本。考虑到网页需要在不同设备、浏览器上呈现，在决定使用较新的语法特性时我们需要特别慎重。


运行环境：执行、加载与调试
---------------------------

执行 JavaScript 的最简单方法是在网页浏览器中。以 Chrome 为例，按 F12 打开开发者工具面板，并选择其中的“控制台”（Console）选项卡，就可以看到交互式的 JavaScript 命令行。例如，输入以下语句并按回车：

.. code-block:: javascript

    alert("Hello, world!")

网页浏览器中就会弹出一个文本窗口，提示你当前页面向你发送了 ``Hello, world!`` 这条信息。你也可以尝试使用 ``console.log()`` 函数，它的作用是向控制台中输出信息：

.. code-block:: javascript

    console.log("Hello, world!")

-----

.. hint:: 

    请注意，将同一段 JavaScript 内容加载在网页文件的不同位置，网页的最终呈现也可能不同——尤其是在使用 JavaScript 操作网页元素的时候。顺序十分重要！
    
    在大多数情况下，复杂的 JavaScript 脚本都会被放在网页的最后进行加载。

加载 JavaScript 的方法十分简单，一般用两种。一种是直接在网页 HTML 中书写内容，将其放在 ``<script>`` 标签内即可：

.. code-block:: html

    <script>
      const a = 1;
      const b = 2;
      // ... 其他 JavaScript 语法内容
    </script>

另一种则是将上述内容（不包含 ``<script>`` 标签）书写在一个扩展名为 ``.js`` 的文件中，并用  ``<script>`` 标签的 ``src`` 属性指定该文件的路径。以加载该网页文件所在文件夹下的 ``example.js`` 为例：

.. code-block:: html

    <script src="./example.js"></script>

-----

调试 JavaScript 也需要先让网页加载你准备的 JavaScript 文件。可以使用上例中的 ``src="./example.js"`` 方法加载。

加载后打开网页，与执行 JavaScript 代码时一样，按 F12 打开开发者工具面板。这次选择“源代码”选项卡，并定位到 ``example.js`` 文件。在右侧的编辑器中，你可以在行号上点击来添加断点。之后按 F5 刷新网页，使网页重新加载该 JavaScript 文件，加载会暂停在断点位置。这时就可以开始调试了。


注释与分号
------------

JavaScript 使用双斜线 ``//`` 来注释本行中该符号右侧的内容，用 ``/* ... */`` 来注释多行内容：

.. code-block:: javascript

    const s = "before inline comment"; // Inline comment
    /* Multi-line
       comment */

JavaScript 可以不写分号、自动按照行来分断语句，但在某些场合可能出现问题（比如下一行以左括号开头时）。因此，我不推荐依赖于 JavaScript 的断句机制，而是\ **推荐手动在每个语句结尾添加分号**。

.. code-block:: javascript

    const a = 1;
    const funcA = function(x) { return x; };  // 赋值语句，有分号
    function funcB(x) {  return x;  }  // 块结尾而不是语句结尾，无分号


变量的命名与声明
---------------------

变量命名
^^^^^^^^^^^^^^^

* 合法的变量（包括函数、类）名由英文、数字、下划线 ``_`` 以及美元符 ``$`` 组成，且不能以数字开头。
* 一般地，我们使用驼峰命名法，不带下划线或美元符。
  
  * 变量、一般函数名用 *小写字母* 开头的驼峰，例如 ``catNames``\ , ``document.querySelector()`` 等。
  * 构造函数、类名用 *大写字母* 开头的驼峰，例如 ``FelineAnimals`` 等。

变量声明：const 与 let
^^^^^^^^^^^^^^^^^^^^^^^^

.. note::

    在早期的 JavaScript 中我们使用 ``var`` 关键字声明变量，但这种习惯在 ES6 中引入 ``const/let`` 关键字后发生了变化。我推荐不使用``var`` 关键字，或至少要尽可能少地使用它。

如果变量在声明后就不会再改变，使用 ``const`` 关键字；如果有可能需要改变，那么使用 ``let`` 关键字。

* ``const``\ ：声明之后不可变更值。声明只在当前块（指一对花括号，这也包括函数）内部有效。可以在子块中声明同名的变量，子块中同名变量的变化不会影响到父块。
* ``let``\ ：除了声明之后可以变更值以外，其余特性与 ``const`` 一致。
* ``var``\ （不推荐）：声明之后可以变更值。声明只在当前函数内生效，允许对变量重复声明。该关键字可以视为 ``let`` 的前身。

下面是一个例子。

* 变量 ``x`` 在块内部被重新定义了，但块内新定义的 ``x`` 的值并不会影响到块外部；
* 变量 ``y`` 在块外声明，因此在块内部也可以引用。请注意，在块内对引用的块外变量进行修改，这将影响到块外的该变量。
* 变量 ``s`` 只在块内声明过，因此在块外引用时会产生错误。

.. code-block:: javascript

    const a = 100;
    let x = 1;
    let y = 2;
    {
        let x = 10;
        y = 5;
        let s = x + y;
        console.log(x, y, s);  // 10 5 15    
    }
    console.log(x, y);  // 1 5
    console.log(s);     // Uncaught ReferenceError: s is not defined

变量的类型与结构
--------------------

JavaScript 主要包含数字（Number）、字符串（String）、布尔（Boolean）、符号（Symbol）类型、未定义（Undefined）这些类型。除了以上类型以外的其他对象都可以归为 *对象* （Object）类型，这其中包括了函数（Function）、数组（Array）、错误（Error）、日期（Date）等等。

需要指出的是，符号（Symbol）类型是在 ES6 中被引入的一种为变量产生唯一标识的类型；但我认为它较少被使用，因此本文不多做介绍了。

布尔（Boolean）
^^^^^^^^^^^^^^^^^^^^

JavaScript 中用小写单词 ``true`` 与 ``false`` 表示真或假。

除了判等 ``===`` 以外，大多数布尔比较符都与许多编程语言相同的。\ **请总是使用三连等**\ 判断两个对象是否全等，而不要使用双等号！

.. code-block:: javascript
   
    1 > 1;     // false
    1 <= 1;    // true
    
    1 !== 2;    // true
    // 在判等时，请总是使用三连等！
    1 === "1";   // false
    1 == "1";    // true, 因为 JS 自动执行了类型转换 

在涉及从其他类型向布尔类型的转换时，数字 0 与 ``NaN``\ 、空字符串、\ ``null`` 与 ``undefined`` 会被转换成 ``false``，而其余情况会被转换为 ``true``。

JavaScript 中的与、或、非运算是短路（Short-circuiting）的，即如果在中途能确定表达式的真假，就会停止检查表达式剩下的内容并直接输出表达式的结果。

.. code-block:: javascript
    
    true && false  // false
    true || false  // true
    !true          // false
    
    // 短路特性
    (2 > 1) && 'yes'  // 'yes', 因为直到最后才确认逻辑与的真假
    (2 > 1) || 'yes'  // true，因为逻辑或中检测到一项为真，停止后续检查


数字（Number）
^^^^^^^^^^^^^^^^^^^^

JavaScript 并不在数字之下再细分整数与小数，它们在内部实际上都用浮点数表示。因此，即使是整数之间的除法也不会出现去尾问题。

.. code-block:: javascript

    1 + 1;   // 2
    1 - 5;   // -4
    2 * 3;   // 6
    7 / 2;   // 3.5

JavaScript 还支持求余、乘方这两种数字运算。

.. code-block:: javascript
    
    7 % 3;   // 1
    2 ** 3;  // 8 (仅限 ES2016 之后)

JavaScript 的标准库 Math，定义了 :math:`e, \pi` 之类的数学常数，以及一些更高等的数学运算：

.. code-block:: javascript
    
    Math.ceil(1.4);         // 2  (向下取整)
    Math.floor(-2.3);       // -3 (向上取整)
    Math.trunc(1.7);        // 1  (去尾取整)
    Math.round(1.4);        // 1  (四舍五入向上取整)
    
    Math.abs(-1);           // 1
    Math.max(-1, 2);        // 2
    Math.exp(1);            // 2.718281828459045
    Math.log(Math.E);       // 1
    Math.tan(Math.PI / 4);  // 0.9999999999999999

JavaScript 支持复合赋值运算（例如 ``+=``\ ）以及自加一/自减一运算（例如 ``++``\ ）：

.. code-block:: javascript

    let x = 0;
    x += 2; 
    console.log(x);  // 2
    x *= 3;
    console.log(x);  // 6
    x++;
    console.log(x);  // 7


要将其他类型转换为数字，使用 ``parseInt()/parseFloat()`` 或者用 ``Number()`` 执行强制转换：

.. code-block:: javascript

    parseInt("1.34");       // 1
    parseFloat("1.34");     // 1.34
    Number("1.34")          // 1.34

    // 注意在类型转换中存在的风险！
    parseFloat("134e-2");   // 1.34 (符合预期)
    parseInt("134e-2");     // 134  (不符合预期)

Javascript 支持数字中的合法标记，比如数字进制。通过使用不同的前缀，可以使用二进制 ``0b``\ 、八进制 ``0o``\ 、十六进制 ``0x`` 字面值；用小写字母 ``e`` 则可以表示科学记数法下的数字。此外，在用 ``toString()`` 或 ``parseInt()`` 在数字与字符串间转换时，也可以指定字符串中使用的进制：

.. code-block:: javascript

    0b110;   // 6 (二进制输入)
    0o17;    // 15 (八进制输入)
    0x1f;    // 31 (十六进制输入)
    1.02e4;  // 10200 (科学记数法输入)
    
    (0o10).toString(2);   // '1000' (八进制数转为二进制字符串)
    parseInt("1000", 2);  // 8 (将二进制字符串转为十进制数)

最后，介绍三种特殊的数字结果：正无穷 ``Infinity``\ 、负无穷 ``-Infinity``\ 、非数 ``NaN``\ （Not a Number）。他们可以用 ``isNaN()`` 或 ``isFinite()`` 函数来检测。

.. code-block:: javascript
    
    0/0;   // NaN
    1/0;   // Infinity
    -1/0;  // -Infinity

    isNaN(NaN);          // true
    isFinite(Infinity);  // false 

.. admonition:: 不要用 Number.EPSILON 判断浮点数相等！
    :class: danger

    虽然这是一个老生常谈的话题，但我仍然想在这里强调。 ``Number.EPSILON`` 这个内部值是为了浮点表达数字的需要，而不是为了用于判断两个浮点数是否相等。如果你没有接触过编程语言，那么你可能对以下结果感到困惑：

    .. code-block:: javascript

        0.1 + 0.2;           // 0.30000000000000004
        (0.1 + 0.2) === 0.3  // false, 这是由于精度问题

    但我仍然要指出，如果你确实需要判断两个小数是否（在一定精度上）相等，那么你应当自己为这个精度选择一个阈值。依赖 ``Number.EPSILON`` 这个内部值是十分危险的！这是一个很小的值，而且在许多情况下结果无法预测：

    .. code-block:: javascript

        // 一个证明 Number.EPSILON 不可靠的例子
        function unreliableNumberEpsilonEqual(x, y) {
            let absDiff = Math.abs(x - y);
            return absDiff < Number.EPSILON;
        }

        unreliableNumberEpsilonEqual(0.1 + 0.2, 0.3);  // true
        unreliableNumberEpsilonEqual(2.1 + 0.2, 2.3);  // false

字符串（String）
^^^^^^^^^^^^^^^^^^^^^

字符串可以使用单引号或双引号包围，内部的引号可以用单个反斜线 ``\`` 转义。字符串是不可修改的。JavaScript 字符串的常用方法：

.. note::

    字符串的 ``slice()``\ （ES6）在 ``substring()`` 基础上支持负数参数，因此完全取代了后者。

.. code-block:: javascript
    
    let s = 'abcdeabc';
    s[1];              // 访问第2个字符。如果在 ES5 之前，使用 s.charAt(1)
    s.slice(2, -2);    // 返回从第2（包含）到倒数第2（不包含）下标之间的子字符串
    s.slice(3);        // 返回从3到末尾的子字符串
    s.toUpperCase();   // 将字符串s变为全大写
    s.toLowerCase();   // 将字符串s变为全小写
    s.includes('de');  // 检查字符串中是否含有子串
    s.indexOf("abc");  // 搜索"abc"首次在s中出现的位置。若无，返回 -1
    s.startswith('a'); // 检查字符串是否以子串开头
    s.endswith('bc');  // 检查字符串是否以子串结尾

另一个重要的字符串特性是模板字符串，类似 Bash/Powershell 中的模板字符串或者 Python 中的 f-string 特性。Javascript 中的模板字符串使用重音号（键盘上数字1左侧的键）而不是引号，并用 ``${...}`` 来包围需要解析的内容。

.. code-block:: javascript

    let s = "Hello, world!"
    let say = `"${s}" is of length ${s.length}.`
    console.log(say);    // "Hello, world!" is of length 13.

模板字符串也可以支持多行内容，但为了行首缩进带来的可读性，一般不建议这样做。


数组（Array）
^^^^^^^^^^^^^^^^^

数组是对象类型中的一种，使用从 0 开始的数字下标来索引内容。注意，数组的长度是数组的属性而不是方法，因此使用 ``.length`` 而不是 ``.length()``。

.. code-block:: javascript

    let arr = [1, 3, 4, 8];
    console.log(arr[1]);       // 3
    console.log(arr.length);   // 4

.. note::

    在给超出当前数组索引范围的位置赋值时，JavaScript 会自动扩展数组长度到那个位置，并在扩展区域填充 ``undefined``。用 For/of 循环语句遍历时，循环步数将与数组长度一致。

    .. code-block:: javascript

        let arr = [1, 2];
        console.log(arr.length);  // 2
        arr[10] = -1;
        console.log(arr.length);  // 11 (最大索引下标加一)
        console.log(arr[9]);      // undefined

生成或操作数组时的一些常用技巧，利用展开语法 ``...``\ 、\ ``map/filter`` 方法，以及匿名箭头函数：

.. code-block:: javascript

    Array(3);  // 长度为3的空数组
    Array.from(Array(3).keys());  // [0, 1, 2]
    
    // Array.map 映射可以接受单参数（数组值）
    [0, 1, 2].map(x => x**2);   // [0, 1, 4]
    // ...或者双参数（值与下标）
    ["a", "b", "c"].map((
        x, i) => `Arr[${i}]=${x}`
    );  // ['Arr[0]=a', 'Arr[1]=b', 'Arr[2]=c']
    
    // 较复杂的 map 嵌套生成
    [3, 4].map(x => [10, 20].map(y => x+y)); // [[13, 23], [14, 24]]
    ['A','B'].map(x => [1, 2].map(
        y => [x,y].join(''))
    ).flat();    // ['A1', 'A2', 'B1', 'B2']
    
    // Array.filter 过滤
    ["a", "bcd", "ef"].filter(x => x.length > 1); // ['bcd', 'ef']
    

Javascript 数组的常用方法：

.. code-block:: javascript
    
    let arr = ['a', 'b', 'c'];
    arr.length;             // 数组长
    arr.slice(0,2);         // 数组[0,2)下标之间的子数组切片
    arr.slice(-2);          // 数组的倒数第二个元素的数组切片
    arr.concat(1, arr2);    // 返回一个组合了数组 arr, 元素 1 与 数组 arr2 的新数组
    arr.push(3, 4);         // 向数组尾添加两个元素 3 和 4
    arr.pop();              // 从数组尾返回元素并将其删除
    arr.shift();            // 从数组头返回元素并将其删除
    arr.unshift(2);         // 向数组头添加元素 2
    arr.splice(1, 2, "a");  // 从下标1处pop两个元素，再插入元素 "a"
    arr.sort();             // 将数组排序（默认升序）
    arr.includes(7);        // 检查数组中是否含有元素
    arr.indexOf(12);        // 搜索数字元素12首次出现的位置
    arr.join(".");          // 用点号依次连接数组元素，返回字符串
    arr.reverse();          // 反转数组

    arr = [0, [1, 2], 3];
    arr.flat();             // 数组展平：[0, 1, 2, 3]

最后，如果利用展开语法 ``...`` （类似 Python 中的 ``*`` 展开），可以简化许多代码。例如，合并两个数组：

.. code-block:: javascript

    let arr = [1, 2];
    let brr = [7, 8];
    arr.push(...brr);
    console.log(arr);  // [1, 2, 7, 8]


对象（Object）
^^^^^^^^^^^^^^^^^

JavaScript 中的对象类型是一种类似键值对的结构，可以类比为 Python 中的字典类型。本文中就取“字典”来称呼。不同的是，JavaScript 字典的键在声明时 *不需要* 添加引号。

.. code-block:: javascript
    
    let x = "id";
    let d = {
        x: 1,
        name: "chris"
    };
    // 要获取键 key 的值，d.key 或者 d["key"] 两种写法是等价的
    console.log(d.name === d["name"]);   // true
    console.log(d["x"]);   // 1
    console.log(d["id"]);  // undefined

在我看来，允许在声明时不向键值添加引号是一种很奇怪的行为，特别是当键名与某个变量名相同时。上例中变量 ``x`` 的值并没有被用作字典 ``d`` 的键，而是 ``x`` 这个字母被用作了字典的键。因此，\ **我更推荐在声明字典的键时加上引号**\ ，以避免理解上的问题。如果要确实使用变量的值作为字典的键，可以使用 ES6 支持的解析语法：

.. code-block:: javascript
    
    let x = "id";
    let d = {
        [x]: 1,    // 注意加上中括号以解析变量值
        "name": "chris"
    };
    console.log(d["x"]);   // undefined
    console.log(d["id"]);  // 1

字典的其他用法。我个人并不推荐 ``Object.assign(x,y)``\ ，而是建议使用剩余展开式语法 ``{...x, ...y}``\ 。

.. code-block:: javascript
    

    let x = Object.fromEntries([["a", 1], ["b", 2]]);  // (ES2019)
    let y = {"b": -1, "c": 3};

    // 请注意，Object.assign 也会同时更新 x 的值！
    let z1 = Object.assign(x, y);
    console.log(z1);    // {a: 1, b: -1, c: 3}
    console.log(x);     // {a: 1, b: -1, c: 3} (变量 x 也被更新)
    // 因此，我推荐使用 {...} 展开
    let z2 = {...x, ...y};
    console.log(z2);    // {a: 1, b: -1, c: 3} (变量 x 不受影响)
    
    // 利用 Object 类的方法函数
    Object.keys(x);     // ['a', 'b', 'c']
    Object.values(x);   // [1, -1, 3]
    Object.entries(x);  // [['a', 1], ['b', -1], ['c', 3]]
    
    // 其他
    console.log("a" in x);  // true (检查字典中是否含有键)

-----

Javascript 对象支持一些与类十分相似的操作。你可以定义一个函数作为创建键值对象的模板，这实际上与类的构造函数相似：

.. code-block:: javascript

    function Cat(name, color) {
        this.name = name;
        this.color = color;
    }

    let mimi = new Cat("mimi", "orange");
    console.log(mimi);    // Cat {name: 'mimi', color: 'orange'}

再比如，你可以用 ``this`` 绑定的函数作为某个键的值，这与类的方法定义相似；

.. code-block:: javascript

    let circle = {
        "r": 1,
        area() {    // 旧版写法可能更符合直觉： "area": function() {
            return this.r ** 2 * Math.PI;
        }
    };
    console.log(circle.area());  // 3.141592653589793

    circle["r"] = 2;
    console.log(circle.area());  // 12.566370614359172


集合（Set）
^^^^^^^^^^^^^^^

集合是一种内部元素互不重复的变量类型。

.. code-block:: javascript

    let s = new Set([1, 2, 3, 2]);
    console.log(s);  // Set(3) {1, 2, 3}
    
    s.size;          // 集合的元素个数
    s.values();      // 将集合转为一个可迭代对象。与s.keys()结果相同
    s.has(3);        // 检查集合中是否包含某元素
    s.add(4);        // 向集合添加一个元素。如果已存在，则集合不变
    s.delete(1);     // 从集合删除一个元素。如果不存在，则集合不变


哈希（Map）
^^^^^^^^^^^^^^^^^

哈希是 ES6 引入的一种变量类型。哈希与字典很相似，但它的键可以是字符串以外的类型。

.. code-block:: javascript

    let m = new Map([["key1", "val1"], ["key2", "val2"]]);
    console.log(m);  // Map(2) {'key1' => 'val1', 'key2' => 'val2'}

    m.size;         // 2
    m.keys();       // MapIterator {'key1', 'key2'}
    m.values();     // MapIterator {'val1', 'val2'}
    m.entries();    // MapIterator {'key1' => 'val1', 'key2' => 'val2'}

    m.has("val1");  // false (检查键)
    m.set("key3", "val3");
    m.get("key4");  // undefined
    m.delete("key3");

在使用字符串以外的类型作为哈希的键时，需要特别小心！你必须 **精确地引用（内存中的）同一个对象**，而不能创建一个“看起来相同”的字面值并期望得到 ``undefined`` 以外的结果。

.. code-block:: javascript

    let m = new Map();
    const map_key = [0, 1];
    m.set(map_key, "abc");

    console.log(m.get(map_key));  // 'abc'
    console.log(m.get([0, 1]));   // undefined
    
    // 仍然推荐使用字符串作为键，以便使用字面值
    const strKey = map_key.join('');
    m.set(strKey, "def");
    
    console.log(m.get(strKey));  // 'def'
    console.log(m.get("01"));    // 'def'


函数
----------

函数实际上属于 JavaScript 对象中的一种，不过有必要将其放在变量类型之外进行讲解。函数的声明可以使用下面几种语法之一：

.. code-block:: javascript
    
    // 函数块语法，结尾无分号
    function sumA(x, y) {
        return x + y;
    }  

    // 本质是声明语句，结尾有分号
    let sumB = function(x, y) { return x + y; };  

类似于 Python 的 ``*args`` 未知个数的参数列表，JavaScript 也支持用 ``...args`` 的语法，传入未知数量的参数：

.. code-block:: javascript

    function sumC(x, y, ...args) {
        let s = x + y;
        for (const num of args) {
            s += num;
        }
        return s;
    }

    console.log(sumC(1, 2));         // 3
    console.log(sumC(1, 2, 3, 4));   // 10

如果在声明时不指定函数名称，那么就会得到一个匿名函数。这多用于临时需要使用一个函数、“用后即抛”的情形。匿名函数有一种简洁的箭头式语法，在 ``=>`` 箭头的左侧书写参数（多参数仍需要用圆括号扩起）、右侧书写返回值（多语句则仍需要花括号与 return 关键字）即可。

.. code-block:: javascript
    
    // 两种匿名函数写法等价
    function (x, y) { return x + y; }
    (x, y) => x + y;
    
    function (x) { return Math.abs(x); }
    x => Math.abs(x);
    
    // 体会以下几种声明函数的方式
    function sumD(x, y) { return x + y; }
    let sumE = function (x, y) { return x + y; };
    let sumF = (x, y) => x + y;



控制语句：条件与循环
---------------------

JavaScript 中的控制语句主要包括判断语句 if（以及三元操作符）、循环语句 for 与 while，还有选择语句 switch。

If 判断与三元操作符
^^^^^^^^^^^^^^^^^^^^^^

If 语句的用法十分简明，而且也可以配合 else 使用：

.. code-block:: javascript
    
    // 输出结果： 1 <= x < 10
    let x = 5;
    if (x < 1) {
        console.log("x < 1");
    } else if (x < 10) {
        console.log("1 <= x < 10");
    } else {
        console.log("x >= 10");
    }

三元操作符可以看成是一种单行的 if-else 语句。如果条件（问号之前的表达式）为真，执行第一个语句（冒号之前）；否则，执行第二个语句（冒号之后）。

.. code-block:: javascript
    
    let x = (2 !== 1) ? "yes" : "no";
    console.log(x);  // yes


Switch 选择
^^^^^^^^^^^^^^^^^

与许多其他语言不同，JavaScript 中的 Switch 选择语句需要在 **每一个分支** 结束前加上 break 语句，以终止当前分支。否则，该分支会继续执行之后分支的语句。在 Switch 语句的最后，支持加入一个可选的 default 分支，来应对所有分支都不匹配的情况。

.. code-block:: javascript

    switch(1 + 1) {
        case 1:
            console.log(1);
            break;
        case 2:
            console.log(2);  // 本例执行的分支
            break;
        default:
            console.log("No matched case.");
    }


For 循环：For, For/of 与 ForEach
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

最基础的 For 循环语句与 Java/C 语言类似，在圆括号内的三个部分依次是循环变量初始值、终止条件、步进方式。下例用 For 循环计算了从 1 加到 4 的值：

.. code-block:: javascript
    
    let s = 0;
    //如果使用 var 关键字，那么循环变量 i 在循环后仍可以使用
    for (let i = 1; i < 5; i++) {
        s += i;
    }
    console.log(s);  // 10

JavaScript 在循环中也可以使用 ``break`` 关键字终止循环，或者 ``continue`` 关键字跳过当前循环步：

.. code-block:: javascript
    
    let s = 0;
    for (let i = 1; i <= 10; i++) {
        console.log(`i=${i}`);    
        if (i % 2 === 1) {
            continue;
        }
        console.log(`Add i = ${i} to s.`)
        s += i;
        if (s > 1) {
            console.log(`s=${s}`);
            break;
        }
    }
    /* 输出：
       i=1
       i=2
       Add i = 2 to s.
       s=2
    */

.. note::

    在早期的 JavaScript 中我们使用 For/in 循环遍历字典的键，但现在已不推荐。在 ES2017 或更新的版本中，请使用 For/of 循环配合 ``Object.entries()`` 代替。

For/of 则是在 ES6 中引入的 For 循环语句的另一种常用形式，它可以依次访问一个\ **可迭代对象**\ 中的所有值。可迭代对象包括数组、字符串、哈希以及集合。

.. code-block:: javascript

    let a = [1, 3, 5, 7];
    let c = "abcdefg";
    let m = new Map([["a", 1], ["b", 4]]);
    let s = new Set([1, 2, 5, 7]);
    
    for (const iterObj of [a, c, m, s]) {
        for (const data of iterObj) {
           console.log(data);
        }
    }

注意，字典（键值对）并不是可迭代对象，不过可以使用 ``Object.entries()``\ （ES2017）来访问它的键值。下例循环打印了一个字典对象的键值。

.. code-block:: javascript
    
    let d = {x: 1, y: 2};
    for (const [key, val] of Object.entries(d)) {
        console.log(key, val);  //  x  1 \n y  2
    }

利用 ForEach 方法也可以遍历可迭代对象，例如：

.. code-block:: javascript

    let a = [1, 3, 5, 7];
    a.forEach(function(element, index, array) {
        console.log(`Arr[${index}] = ${element}`);
    });
    /* 
       输出：
       Arr[0] = 1
       Arr[1] = 3
       Arr[2] = 5
       Arr[3] = 7
    */

While 循环
^^^^^^^^^^^^^^

While 循环没有太多值得强调的地方。JavaScript 也支持 Do-while 语句，它的不同在于至少会执行一遍循环块，不过我认为并不常用。

.. code-block:: javascript

    let s = 0;
    let k = 1;
    while (k <= 100) {
        s += k;
        k++;
    }
    console.log(s);  // 5050


高级特性：解构
----------------

解构（Destructuring）语法，这一特性在 Python 中也有应用。解构也可以配合展开符/剩余符 ``...`` 使用。

.. code-block:: javascript

    // 解构字典：花括号
    // 赋值到与键值相同的变量名：d.a 到 a, d.b 到 b
    const d = {"a": 3, "b": 4};
    let {a, b} = d;
    console.log(a, b);     // 3 4
    // 赋值到与键值不同的变量名：d.a 到 p, d.b 到 q
    let {a: p, b: q} = d;
    console.log(p, q);     // 3 4
    // 赋值的同时指定无键名时的默认值
    let {a: p, b: q, c: r=10} = d;
    console.log(p, q, r);  // 3 4 10

    // 解构数组：中括号
    const arr = [1, 2, 3];
    let [x, ...others] = arr;
    console.log(x, others);  // 1 [2, 3]
    // 跳过特定值
    let [x, , z] = arr;
    console.log(x, z);    // 1 3
    // 值交换
    [x, z] = [z, x];
    console.log(x, z);    // 3 1

    // 如在非声明语句中对字面值使用解构，可能需要添加额外的圆括号
    {a, b} = {a: 14, b: 17};    // Uncaught SyntaxError: Unexpected token '='
    ({a, b} = {a: 14, b: 17});  // (Successfully executed)

解构的一种高级用法是在函数定义时使用，可以将传入参数的对应键/索引值解构声明为函数内的变量。

.. code-block:: javascript
    
    // 将传入参数的 arg.name 声明给变量 catname, arg.color 声明给 color
    //    如果该参数 arg 没有 color 属性，将默认值 "black" 声明给 color
    function introCat({ name: catname, color="black" }) {
        let s = `${catname} is a cat in ${color} .`;
        console.log(s);
    }

    let cat1 = {"name": "Mimi", "color": "orange"};
    introCat(cat1);  // Mimi is a cat in orange.

    let cat2 = {"name": "Huahua"};
    introCat(cat2);  // Huahua is a cat in black.
