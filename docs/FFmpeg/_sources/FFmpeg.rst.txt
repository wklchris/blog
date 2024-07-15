FFmpeg 实用命令
==================

FFmpeg的\ `官方文档 <https://ffmpeg.org/ffmpeg.html>`__\ 简洁有力，但它的排版逻辑是技术文档而不是工具书或问答，因此可能并不是一个好的参阅选择。

本文将以实际用例为主。毕竟照搬 FFmpeg 的文档实在没有什么意义。不过例子是由浅入深的，如果读者没有任何的 FFmpeg 使用经验，仍然建议按顺序依次浏览。

在开始之前，先介绍一个全局参数 ``-hide_banner``\ ；它可以阻止 FFmpeg 在每次执行时开头打印的那一堆版本信息文本。例如，在展示 FFmpeg 的许可证时，隐藏这部分默认打印的版本信息：

.. code-block:: shell

    ffmpeg -hide_banner -L


格式转换
-----------

这毫无疑问是最常使用的功能。关于各种常用的视频/音频编码格式或编码器，请参考 :ref:`codec_format` 一节的内容。

转码
~~~~~~

比如将一个 FLV 文件转为 MP4 文件并重编码，FFmpeg 会自动寻找编解码器：

.. code:: shell

   ffmpeg -i video.flv video.mp4

其中，在 ``-i`` 后指定输入文件的文件名，在所有命令的最后指定输出文件的文件名。 **如果文件名带有空格，请用双引号将文件名包裹。** 上述的 ``video.mp4`` 在 ``-i`` 参数之后，称为 **输出参数** ；反之，在 ``-i`` 之前的称为 **输入参数**。

.. important::
   
   转码过程可能较慢。关于快速地进行格式转换，请参阅下文 :ref:`codec-copy` 一节的内容。

用户也可以显式地指定编码器，比如使用 h.264 视频编码器与 flac 音频编码器。

.. code-block:: shell
   
   ffmpeg -i video.flv -c:v libx264 -c:a flac video.mkv

其中 ``-c`` 是 ``-codec`` 的简写。用 ``v`` 表示视频（video）编码器、 ``a`` 表示音频（audio）编码器。

.. _codec-copy:

流复制
~~~~~~~~~~

格式转换还有一种快速的情形。如果两者的所有流都不改动且输出容器支持输入的所有流，那么可以直接向 ``-c`` 传递 ``copy``
以进行流复制。这样省去了重新编码的时间，格式转换将十分迅速：

.. code:: shell

   ffmpeg -i video.avi -c copy video.mp4

其中，``-c`` 是 codec 的简称，表示所有流的编解码器。该命令表示所有流均不进行额外操作，直接复制到新容器中。

提取流（音频、字幕）
~~~~~~~~~~~~~~~~~~~~

有时需要指定流来完成格式转换，比如将一个 MP4 视频文件转为 AAC 音频文件（此处实质上是直接提取）：

.. code:: shell

   ffmpeg -i video.mp4 -c:a copy audio.aac

此处的 ``-c:a`` 表示音频流；视频流 ``-c:v`` 与字幕流 ``-c:s`` 自然也类似。 注意：如果音频流与容器冲突时，你需要将 ``copy`` 改为正确的编解码器（或者删去 ``-c:a copy`` 来让 FFmpeg 自动选择），以执行重编码。

也可以在提取流的时候进行转码：

.. code:: shell
   
   ffmpeg -i video.mkv -c:a libmp3lame -q:a 2 audio.mp3

对于内挂了字幕的视频文件，也可以将其字幕单独提取出来，例如：

.. code:: shell
   
   ffmpeg -i video.mkv -c:s copy subtitle.srt

截取视频
----------

视频文件的截取可以分为截取视频与截取图片两种。

.. _extract_frame:

截取帧为图片
~~~~~~~~~~~~~~~

下例利用 :filter:`select` 过滤器，抽取了视频中的第 105 帧，保存为 extract.png：

.. code:: shell

   ffmpeg -i video.mp4 -vf 'select=eq(n\,105)' -vframes 1 extract.png

.. warning::

   实际上，帧序号是从 0 开始的，因此参数 ``select=eq(n\,105)`` 实际选取的是第 106 帧。但为了避免叙述上的繁琐与混乱，本文并未忠于这一细节。对于确实需要精确到某一帧的读者，请特别注意这一点。

如果不需要特别精确，也可以将帧序号转换为时间戳来截取：

.. code:: shell
   
   # 假如该视频每秒 30 帧
   ffmpeg -ss 00:00:03.50 -i video.mp4 -vframes 1 extract.png

上例中的两个命令，对同一个每秒 30 帧的视频的帧截取结果是等同的。但是，如果时间戳的小数不能除近，则很难准确地选中想要的帧。因此，还是更推荐使用 select 过滤器配合帧序号的方法。

截取视频片段
~~~~~~~~~~~~~~~

下面，以想要截取 video.mp4 视频的第2到第5分钟为例。

对于容易计算片段秒数的截取任务（本例中片段长为 (5-2)*60=180秒），可以使用 ``-t`` 参数，即指定片段长度。

.. code:: shell
   
   ffmpeg -ss 00:02:00 -i video.mp4 -t 180 cut.mp4

其中， ``-ss`` 参数指定了起始的时间戳记，而 ``-t`` 参数指定了片段长度（秒）。传递给 ``-t`` 的片段长度可以写成 ``00:03:00`` 的形式。它也可以带有小数，比如用 180.5 表示 180.5 秒。

或者，用户可以不用 ``-t`` 指定片段长度，而是用 ``-to`` 指定终止时刻。下例中把参数 ``-ss`` 与 ``-to`` 都放在了 ``-i`` 参数之前：

.. code:: shell

   ffmpeg -ss 00:02:00 -to 00:05:00 -i video.mp4 cut.mp4

需要注意，在上面的例子中， **参数** ``-ss`` **均被放在了** ``-i`` **参数之前**，这称为输入（inputing）参数语法；对应的时间戳检索方式称为输入检索（inputing seek）。如果放在 ``-i`` 参数之后，则称为输出（outputing）参数与输出检索。

* 输入检索根据关键帧来检索，而输出检索是逐帧地检索地。因此输入检索地速度会比输出检索更快。
* 由于关键帧定位的特性，输入检索在执行流复制操作（如 ``-c copy`` ）时定位可能并不精确；在非流复制（即重新编码）并指定了 ``-accurate_seek`` （默认已指定）时，则无此问题。关于为何会造成定位的不精确，请参考本小节末尾的注释。
* 输入检索会提前将 ``-ss`` 参数指定的时间戳设置为 0；因此，如果将 ``-t/-to`` 参数放在 ``-i`` 参数之后（作为输出参数），FFmpeg 都实质将参数值当作一个片段长度（而不是终止时刻）。例如：

  .. code:: shell

      ffmpeg -ss 00:02:00 -i video.mp4 -t 00:05:00 cut.mp4
      ffmpeg -ss 00:02:00 -i video.mp4 -to 00:05:00 cut.mp4  # 意外的结果
  
  这两种命令的结果是一样的，都截取了第 2 到第 7 分钟；这对于使用 ``-to`` 参数的用户来说，可能是不希望看到的。因此，我推荐将 ``-t/-to`` 参数一起都作为输入参数来使用。

* 官方在早期的版本中，还给出了一种使用 ``-copyts`` 参数的方法（参考 `Seeking - FFmpeg <https://trac.ffmpeg.org/wiki/Seeking>`_ ） 来修正上一条提到的 ``-to`` 参数受到影响的问题。

  .. code-block:: shell
     
     ffmpeg -ss 00:02:00 -i video.mp4 -to 00:05:00 -copyts cut.mp4
  
  这种方法虽然会输出第 2 到 5 分钟的视频，但经笔者测试，其输出视频的时间戳会在一些视频播放器上出现问题。笔者 **并不推荐** 使用这种 ``-copyts`` 的修正语法。

这部分 FFmpeg 的语法比较复杂，稍微小结一下：

.. code-block:: shell
    
    # 任务：截取视频的第 2 至 5 分钟。

    # 1. 可接受起始片段前的额外内容，可能长达数秒 —— 方案 A
    # 2. 不可接受上述精度，要求精确到给定时刻最近的关键帧 —— 方案 B 
    # 3. 不可接受上述精度，要求精确到给定时刻最近的帧 —— 方案 C

    # 根据上述问题的回答，选择合适的方案：
    
    # A) 用快速截取（输入参数），配合流复制。该方案截取速度非常快。
    ## 以 -t 参数指定片段长，或以 -to 参数指定终止时间戳
    ffmpeg -ss 00:02:00 -t 00:03:00 -i video.mp4 -c copy cut.mp4
    ffmpeg -ss 00:02:00 -to 00:05:00 -i video.mp4 -c copy cut.mp4

    # B) 用快速截取，但不能使用流复制，片段会被重编码。截取速度近似于编码等长视频的速度。
    ffmpeg -ss 00:02:00 -t 00:03:00 -i video.mp4 cut.mp4
    ffmpeg -ss 00:02:00 -to 00:05:00 -i video.mp4 cut.mp4

    # C) 用慢速截取（输出参数），片段之前的内容也会被重编码。截取速度极慢。
    ffmpeg -i video.mp4 -ss 00:02:00 -t 00:03:00 cut.mp4
    ffmpeg -i video.mp4 -ss 00:02:00 -to 00:05:00 cut.mp4


本小节的扩展阅读：

.. admonition:: 为什么在流复制时使用快速检索，起始时刻会变得不精确？
   :class: warning
   
   流复制操作 ``-c copy`` 与放在 ``-i`` 之前进行的快速检索 ``-ss hh:mm:ss -i video`` 同时使用，会导致不能精确定位起始时刻。例如：

   .. code-block:: shell
          
      ffmpeg -ss 00:02:00 -to 00:05:00 -i video.mp4 -c copy cut.mp4

   这其中的原理是，作为输入参数的 `-ss` 会先快速定位到给定的起始时间戳（如上例的 ``00:02:00`` ）之前的一个位置。然后在视频流编码过程中，将该位置与起始时间之间的多余的这段舍弃。
   
   由于在流复制 ``-c copy`` 时，视频流不会被编码而是直接复制，因此上述提到的多余的视频段就不会被舍弃。这会导致截取的视频将包含指定时间之前的一段视频内容。

   具体的解释请参考 `FFmpeg 官方文档 <https://ffmpeg.org/ffmpeg.html>`_ 中关于 ``-ss`` 参数的说明。


分辨率改变：缩放与裁切
-----------------------

.. note::
   
   缩放与裁切总是会重编码视频，请注意这一点。

分辨率缩放
~~~~~~~~~~~~~

分辨率缩放也是一个常见的需求，这需要使用到 FFmpeg 提供的视频过滤器（或称视频滤镜，video filter），也即 ``-vf`` 参数。由于过滤器的使用过于复杂，在此也不会详细介绍；这里只是针对过滤器中的缩放器（scaler）功能进行说明。缩放器还有许多复杂的用法详情也可以参考官方文档的 `Video filter - Scaler <https://ffmpeg.org/ffmpeg-all.html#scale-1>`_ 章节。

例如，我们要将一个高分辨率视频从 1440p 缩放，那么我们可以使用参数：

.. code-block:: shell
    
    # 输出到1280x720的例子
    ## 直接指定宽1280、高720。选择以下任意一种写法即可
    scale=w=1280:h=720
    scale=1280:720
    scale=1280x720
    ## 可以用-1表示按原视频宽高比自动计算
    scale=1280:-1
    scale=-1:720
    ## 也可以使用倍率的写法，用iw、ih代表输入视频的宽和高
    scale=iw/2:ih/2
    
    # 输出到方形720x720的例子。
    ## 可以用ow、oh代表变换后输出视频的宽和高
    scale=iw/2:ow

这些参数中，使用冒号作为分隔符、等号作为键值对的连接符。

除了分辨率，我们有时候也会用 ``flags`` 参数指定缩放算法（参见官方文档 `Scaler Options <https://ffmpeg.org/ffmpeg-scaler.html#Scaler-Options>`_\ ）。关于视频缩放算法的选择（与图片可能不同），可以参考 StackExchange 上的这一篇回答 `Which resize algorithm to choose for videos? <https://superuser.com/a/375726/1061571>`_ ；简单地说， **该回答建议在降分辨率时使用 Lanczos 或 spline，在升分辨率时使用 bicubic 或 Lanczos** 。

一些分辨率缩放的命令示例：

.. code-block:: shell
    
    # 使用默认的  bicubic 算法缩放到高720并保持原宽高比，并用默认编码格式（H.264）编码
    ffmpeg -i video.mp4 -vf scale=-1:720 out.mp4

    # 指定使用 Lanczos 算法缩放到原视频的宽高的各一半，并用 H.265 格式以默认质量编码
    ffmpeg -i video.mp4 -vf scale=iw/2:ih/2:flags=lanczos -c:v libx265 -c:a copy out.mp4


裁切
~~~~~~~~~

裁切同样使用视频过滤器完成，使用 ``crop`` 字段：

.. code-block:: shell
    
    # 从原视频距左上角横20、竖30的位置，向右下角裁切一个宽100、高200的矩形
    crop=w=100:h=200:x=20:y=30
    crop=100:200:20:30
    # 在视频的正中央进行裁切
    crop=100:200
    # 也可以使用倍率的写法，用iw、ih代表输入视频的宽和高
    ## 裁切视频的中间 3/5 宽度画面
    crop=3/5*iw:ih:iw/5:0

例子：

.. code-block:: shell
   
   # 裁切 1/6 到 5/6 宽的画面范围，并用 x265 编码器以 CRF 30 的质量来编码
   ffmpeg -i video.mp4 -c:v libx265 -crf 30 -vf "scale=2/3*iw:ih:iw/6:0" -c:a copy out.mp4

FFmpeg 还支持一种自动检测裁切区域的参数 ``cropdetect``\ ，常用于四周有黑色边框的情形：

.. code-block:: shell

   # 自动检测黑色边框来裁切
   ffmpeg -i video.mp4 -vf "cropdetect" -c:a copy out.mp4


设置视频预览图
-----------------

在为视频文件设置预览图（缩略图）之前，我们首先要准备这样一张图片。FFmpeg 支持用 :filter:`thumbnail` 过滤器自动从视频中抽取一张预览图。它会从头到尾以 ``thumbnail=n`` 中的 n （默认为 100）数量的帧为扫描步长来抽取预览图。

.. code:: shell
   
   # 自动选取 1 张预览图，按宽边为 1080 缩放分辨率，然后保存到文件
   ffmpeg -i clip.mp4 -vf thumbnail,scale=-1:1080 -vframes 1 thumb.png
   # 以 30 帧为扫描步长，从视频中自动选取 3 张预览图以供挑选（并在保存时进行三位数编号）
   ffmpeg -i clip.mp4 -vf thumbnail=30,scale=-1:1080 -vframes 3 thumb-%03d.pngs

或者，利用在 :ref:`extract_frame` 一节中提到的帧截取方法，指定截取某一帧作为图片：

.. code:: shell

   # 指定截取视频中的第 100 帧
   ffmpeg -i clip.mp4 -vf 'select=eq(n\,100)' -vframes 1 thumb.png

最后，预览图当然也可以由用户利用 FFmpeg 以外的软件自行准备。甚至，即使图与视频内容无关，在技术上也是能把它设置为预览图的——但还是别了吧。

-----

在预览图文件 ``thumb.png`` 准备完成后，我们就可以将其嵌入到视频文件了。对于 MP4 文件，这需要使用 ``disposition`` 参数：

.. code:: shell

    ffmpeg -i video.mp4 -i thumb.png -map 0 -map 1 -c copy -c:v:1 png -disposition:v:1 attached_pic out.mp4

上例接受了第 1 个输入文件（#0） ``video.mp4`` 与第 2 个输入文件（#1） ``thumb.jpg`` 的所有流数据，然后将输入 #1 设置为预览图。请注意，我们必须像例中一样用 ``-map`` 指明接受两个输入的流数据，否则 ffmpeg 会自动只保留一个视频流。

对于 MKV 文件，我们则需要使用 ``-attach`` 参数来嵌入缩略图（也称 MKV 封面）。

.. important::

   请注意： **MKV 封面图片的文件名必须为 cover**，例如 cover.jpg 或 cover.png。否则，嵌入的封面不能作为预览图被正常地显示。

.. code:: shell
   
   # 如果使用 PNG 文件（cover.png），请相应地将后续参数改为 mimetype=image/png
   ffmpeg -i video.mkv -c copy -attach cover.jpg -metadata:s:t:0 mimetype=image/jpeg out.mkv


更改帧率/速度
---------------

视频变速的一个常见应用场景是帧率减半，例如将 60 帧视频通过变速输出为 30 帧的视频。请注意：这一过程是可以只通过混流、不重新编码就实现的。

需要指出， 通过 FFmpeg 自带的 ``-vf`` 参数的 ``fps`` 或者 ``setpts`` 键，我们可以指定视频帧率。但是，这些方法\ **不是一个无损转换**\ ，因此不推荐使用。下例中， FFmpeg 将输入的 60 帧视频通过每两帧丢弃一帧的方式降为 30 帧：

.. code-block:: shell
   
   # 以下方法会抽帧，均不推荐！
   ffmpeg -i video-60p.mp4 -vf fps=30 video-30p.mp4
   ffmpeg -i video-60p.mp4 -vf "setpts=0.5*PTS" video-30p.mp4

以下是推荐的变速方式，它无损且无需重新编码。原理是将视频输出为不包含时间戳的数据流，然后在重封装时指定变速后的时间戳。

.. code-block:: shell
   
   # 如果是 H265，使用: ... -bsf:v hevc_mp4toannexb raw.h265
   ffmpeg -i video-60p.mp4 -map 0:v -c:v copy -bsf:v h264_mp4toannexb raw.h264
   
   # 只处理视频流
   ffmpeg -fflags +genpts -r 30 -i raw.h264 -c:v copy video-30p.mp4
   
* 如果需要同时对视频、音频进行降速，可以利用 :all:`atempo` 过滤器。将上述第二条命令更换为：

  .. code-block:: shell
     
     ffmpeg -fflags +genpts -r 30 -i raw.h264 -i video-60p.mp4 -map 0:v -c:v copy -map 1:a -af atempo=0.5 output.mp4
  
  其中， atempo 过滤器只支持 0.5 到 100 之间的变速倍率；不过你可以重复调用，例如 ``-af "atempo=0.5,atempo=0.5"`` 将会把音频降速为 0.25 倍。

* 如果需要对加速或减速后的帧之间进行动态插值（运动补偿），可以使用 :filter:`minterpolate` 过滤器。但这就需要对视频重新编码了：

  .. code-block:: shell
   
     ffmpeg -i input.mkv -filter:v "minterpolate='mi_mode=mci:mc_mode=aobmc:vsbmc=1:fps=30'" output.mkv

更多的变速内容，请参考 :wiki:`How to speed up / slow down a video` 一文。


字幕操作
-----------

FFmpeg 可以将字幕内挂到封装容器内，也可以内嵌到视频流中。

一些注意事项：

- 独立的字幕文件请使用 UTF-8 编码。
- Windows 系统可能缺少一个字体接口，需要自己配置一份 ``fonts.conf`` 文件，并放在 ``%FONTCONFIG_PATH%`` 这个环境变量对应的路径下。

  - 如果用户没有该变量，请新建一个；其默认值一般是 ``C:\Users\用户名\`` 。
  - 关于 ``fonts.conf`` 文件，请参考本文的附录 :ref:`appendix-fonts-conf` 。

内挂字幕
~~~~~~~~~~

内挂字幕是一种相对于外挂字幕的称呼。外挂字幕是指将字幕存放在一个独立的字幕文件中，在播放视频时，通过视频播放器来加载这个字幕文件。而内挂字幕，是将这样一个独立的“字幕文件”，封装在了视频文件内部作为独立的字幕数据流。这样既能按需开启或关闭字幕，也免去了字幕文件丢失、匹配等烦恼。

内挂字幕的本质是将字幕文件单独作为字幕流封装，因此不需要对视频流进行编码。因此，将字幕文件内挂到指定的视频一般非常快：

.. code:: shell

   ffmpeg -i input.mp4 -i input.srt -c:v copy -c:a copy -c:s ass output.mkv

在封装时，一般需要选择 ``-c:s ass`` 这个字幕转码器。上例中使用了早年间非常流行的内挂字幕容器 mkv，实际上 mp4 容器也可以进行内挂操作。

要从有字幕流的视频文件中移除字幕，可以使用 ``-sn`` 参数；可以参考本文替换流与删除流部分的内容。


内挂字幕的元数据操作
^^^^^^^^^^^^^^^^^^^^

FFmpeg 支持以元数据（metadata）的形式指定流的信息，这也包括字幕流（内挂字幕）。其中，比较常用的元数据可能是指定字幕的语言。下例向一个无字幕的视频文件中添加了一个 ass 字幕文件，并指定其语言为中文（语言码应遵循 ISO639-2 标准的三位代码，例如英文 eng、日文 jpn）：

.. code:: shell

   ffmpeg -i input.mp4 -i input.ass -c:v copy -c:a copy -c:s ass -metadata:s:s:0 language=chi output.mkv

.. admonition:: 如何将内挂字幕设定为默认加载的字幕？
   :class: important
   
   FFmpeg 支持使用 ``-disposition`` 参数将某个流设定为默认。例如 ``-disposition:s:0 default`` 表示将文件的第一个字幕流设置为默认（default）；要取消将该字幕流设置为默认，请将其值从 ``default`` 设置为 ``0``\ 。

   一个常见的批处理操作是将文件夹内的所有字幕文件批量内挂到同名的视频文件中。下面以使用 Powershell 命令向 mkv 中内挂 ass 字幕为例，该命令在内挂字幕的同时将字幕语言标记为中文、并设置为默认字幕：

   .. code:: powershell
      
      (Get-ChildItem *.mkv).Basename | ForEach-Object { ffmpeg -i "${_}.mkv" -i "${_}.ass" -y -c:v copy -c:a copy -c:s ass -metadata:s:s:0 language=chi -disposition:s:0 default "${_}-output.mkv"}
   
   上例的输出结果在 VLC 播放器中识别通过，播放时该字幕会自动启用；而不指定 `-disposition default` 的输出文件则需要手动启用内挂字幕。

内嵌字幕
~~~~~~~~~~

内嵌字幕（或称硬字幕）是指将字幕与原视频图像混叠的一种字幕，它直接嵌入到图像中，因此无法关闭，也无法调整字幕的大小、字体等样式。内嵌字幕的本质是将字幕作为图像输出，因此需要对视频流进行编码，往往速度慢：

.. code:: shell
   
   ffmpeg -i input.mp4 -vf subtitles=input.srt output.mp4

如果字幕以字幕流的形式存在于另一个视频文件中，可以直接调用，无需将字幕流先提取成文件：

.. code:: shell
   
   ffmpeg -i input.mkv -vf subtitles=input.mkv output.mp4


合并视频
------------

最简单的视频合并方法，是将所有待合并的视频文件路径，依次列在一个 txt 文件中，然后让 FFmpeg 读取它。

假设我们已经将所有待合并的 mp4 文件放在当前文件夹中，并且按照合并的顺序进行了命名。那么，用户可以在该文件夹中用 Shift + 鼠标右键打开 PowerShell 控制台，然后依次输入以下命令：

.. code:: shell
   
   ls eg-*.mp4 | % Name | foreach { "file '${_}'" } > mylist.txt
   ffmpeg -f concat -i mylist.txt -c copy output.mp4

.. note::
   
   以上命令第一行中的操作需要 **不低于 6.0 版本** 的 Powershell（Windows 10/11 自带的是 5.x 版本），读者可以前往 Powershell 的 Github 开发仓库页面 `选择版本进行下载 <https://github.com/PowerShell/PowerShell#get-powershell>`_\ 。这是因为低于 Powershell 6.0 的版本会在写入文本文件时包含 BOM，而包含 BOM 的文本文件并不能正确地被 FFmpeg 所识别；而从 6.0 版本开始，Powershell 新增并默认使用了 ``-Encoding utf8NoBOM`` 选项。

   用户可以输入 ``get-host | select-object Version`` 来查看当前运行的 Powershell 版本。
      

如果用户对于通配符 ``*`` 语法有所了解，应当可以理解上例中 ``eg-*.mp4`` 通配了所有以 ``eg-`` 开头、以扩展名 mp4 结尾的文件，比如 ``eg-01.mp4``\ , ``eg=02.mp4``\ ……Powershell 的管道（pipeline）操作符 ``|`` 选择了输出结果的 Name 字段（即文件名），然后将其逐行添加前缀与后缀，最后写入到一个 txt 文件（本例命名为 mylist.txt）中：

.. code-block:: none
   
   file 'eg-01.mp4'
   file 'eg-02.mp4'
   ...

当然，如果视频文件数量不多，用户也可以自行创建这样一个 ``mylist.txt`` 文件。在执行完第二行的 ffmpeg 指令进行视频合并后，用户可以删除文件夹中的 ``mylist.txt`` 文件。


替换或删除流
---------------------

除了格式转换中提到的提取流的操作，删除或替换也是常见的选择。

删除流
~~~~~~

删除流有两种操作方法：一是利用 ``-vn/-an/sn/-dn`` 参数，跳过视频/音频/字幕/数据流，并手动指定保留哪些流；二是利用 ``-map`` 参数，反选要删除的流并保留其他所有流。

参数 ``-vn/-an/sn/-dn`` 的功能局限一些，但很好理解。比如从文件中删除音频：

.. code:: shell

   ffmpeg -i video.mp4 -c:v copy -an VideoWithoutAudio.mp4

上例中的 ``-c:v`` 是传递视频编解码器， ``copy`` 表示不进行编解码操作而是直接拷贝。因此，上述命令保留了原文件的视频、删除了音频，并将结果输出。请注意，音频、视频以外的流都被抛弃了。

-----

有时候，视频文件中包含了多个流，我们只想删除其中的一个，而保留其他所有的流。这时候可以用 ``-map`` 参数来反选：

.. code:: shell
   
   ffmpeg -i video.mp4 -map 0 -map -0:a EverythingButAudio.mp4

上例中， ``-map 0`` 表示接受第 1 个输入文件（即 video.mp4）的所有流；接着，用减号指定 ``-`` 要丢弃的流为 ``0:a``\ ，即第 1 个输入文件的音频流。


替换流
~~~~~~~

替换流的常用场景是将一段音频替换原视频中的音频流：

.. code:: shell

   ffmpeg -i video.mp4 -i audio.mp3 -c:v copy -map 0:v:0 -map 1:a:0 out.mp4
   # 或者省略第二冒号
   ffmpeg -i video.mp4 -i audio.mp3 -c:v copy -map 0:v -map 1:a out.mp4

这里输入了两个文件。视频流将直接复制。复制对象由 ``-map`` 手动指定了，其后的 ``0:v:0`` 表示指定第0个输入文件（即 video.mp4）的视频流，在处理后作为输出文件的第0个视频流（单个文件可以有多个视频流）。类似地，``-map 1:a:0`` 表示指定第1个输入文件（即 audio.mp3）的音频流，在处理后作为输出文件的第0个音频流。由于此例中输出的视频不存在多个同类流，因此第二个冒号可以省略。

不使用 ``-map`` 手动指定时，FFmpeg 会自动选择：

- 输入文件的所有视频流（一个文件可能有多个流）中分辨率最高的。
- 输入文件的所有音频流中声道数最多的。
- 输入文件的所有字幕流中最靠前的。注意：如果字幕流是图像型而不是文字型的，需要显式地指定 ``c:s`` 参数。比如，如果 ``video.mkv`` 的字幕流是图像型的，那么下例中的 ``out1.mkv`` 不含字幕流（因为默认的 MKV 字幕流编码器只接受文字型字幕流），而 ``out2.mkv`` 则包含字幕流（因为 dvdsub 用于图形型字幕流）：

  .. code:: shell

     ffmpeg -i video.mkv out1.mkv -c:s dvdsub out2.mkv


.. _bitrate_control:

压制与码率
-------------

.. note:: 
   
   在大多数压制场合，CRF都是更受欢迎的，也是保持画面质量的一选。如果要严格限制文件大小，那么就使用二压；如果要严格限制视频码率，才会考虑使用定限码率压制（或者二压）。

.. important::

   本节以下的例子将以 libx264 编码器为例，并只是进行了粗略的介绍。关于编码器的更多详细内容，请参考 :doc:`Codecs` 一节。

视频的压制主要有 CRF（Constant Rate Factor，恒定率系数）与二压（2Pass）两种常用的方法，以及定限码率压制这种相对不常用的方法（不太推荐）： 

- **在编码器 libx264/libx265 中（vp9等其他编码器中的情形并不同）** ，CRF（Constant Rate Factor）指定一个 0~51 的数值作为视频质量标准值（FFmpeg 中，libx264 默认 23，常用范围是 17~28；libx265 默认 28）。CRF 的数值越小，恒定率系数越好，压缩率也越低。恒定律系数的视频码率是根据画面动态调整的，与恒定码率（CBR）恰好是对立的。
  
  * CRF 为 0 表示无损，51 表示 FFmpeg 所能达到的最差效果。
  * 如果设置一个小于默认值 23 的值，那么输出视频的画面会（从视觉观感上）保留较好的效果，但同时文件的体积也较大；如果设置一个大于 23 的值，那么输出的视频大小会被压缩，但会在画面观感上有一定损失。
  * 对于 H.264 编码，CRF 在 17 左右时，输出的视频损失就非常小了，因此选择比 17 更小的 CRF 意义不大；类似地，CRF 如果低于 28，其效果相比于原视频可能就会出现明显的损失，因此通常也不建议选择大于 28 的数值，

- 二压（2Pass）是需要生成固定大小文件时的压制方法，顾名思义，需要编码两次（因此较慢）。用户可能需要自行计算视频码率限值。
- 定限码率（Limited bitrate）压制是仅在网络上传有严苛要求时才使用的方法，并不是画面质量的第一选择。

恒定率系数（CRF）
~~~~~~~~~~~~~~~~~~~~~~

除 ``-crf`` 外，CRF 的压制中还有一个参数，称为预案 ``-preset`` 。较慢的预案能够更好地发挥压制的效果，按压制后质量从低到高分为 ``ultrafast`` , ``superfast`` , ``veryfast`` , ``faster`` , ``fast`` , ``medium`` , ``slow`` , ``slower`` , ``veryslow`` 这9种。预案越慢，压缩效果（指视频质量与文件体积之比）越好，或者说同等视频质量下输出文件的体积越小。

下例中使用了 ``slow`` 预案来进行压制，即期望得到较好的压缩效果。视频编解码器设置为 libx264，设定了一个恒定率系数优于默认的 CRF 值（设定的20比默认的23小，即效果优于默认转码），并对音频流进行复制：

.. code:: shell

   ffmpeg -i video.mp4 -c:v libx264 -preset slow -crf 20 -c:a copy out.mp4

编码器 ``libx264`` 还提供了一个 ``-qp`` 参数，即量化参数（Quantization Parameter）。它可以取 -1 以上的整数值（默认值 -1 表示自动）。简单地理解，CRF 就是自动根据画面中运动的多与少来调整 QP ，来达到好的压缩效果。通常情况下，用户都应当选择 CRF，而不是 QP 参数。 


.. _2pass:

二压（2Pass）
~~~~~~~~~~~~~

.. note::

   通常只在强制要求文件大小时使用二压。

设想一个二压的应用场景（本例取自 `FFmpeg
Wiki <https://trac.ffmpeg.org/wiki/Encode/H.264>`_ ）：需要将一个10分钟（600秒）长的视频压制到200MB，并保持音频码率在
128 kbps。

首先计算压制后视频流的比特率值。1 MB = 8192 kbit，下式的第一项即为总文件的比特率值，减去第二项音频流的比特率值，就得到了视频流的比特率值：

.. math::

   \frac{200 \times 8192}{600} - 128 \approx 2730 - 128 = 2602 \,\mathrm{kbit/s}.

在上式的 2602 kbit/s 的基础上留一定余量，设置为 2600 kbit/s：

.. warning::

   如果 first pass 后的文件出现了问题，请使用 ``-vsync cfr`` 代替 ``-an``\ 。

.. code:: shell
   
   # 对于 H.264 二压，使用 -pass 参数。请注意首行行尾的续行。
   ffmpeg -y -i video.mp4 -c:v libx264 -b:v 2600k -pass 1 -an -f null NUL && `
   ffmpeg -i video.mp4 -c:v libx264 -b:v 2600k -pass 2 -c:a aac -b:a 128k out.mp4
   
   # 对于 H.265 二压，则应使用 -x265-params 参数。同样，请注意首行行尾的续行。
   ffmpeg -y -i video.mp4 -c:v libx265 -b:v 2600k -x265-params pass=1 -an -f null NUL && `
   ffmpeg -i video.mp4 -c:v libx265 -b:v 2600k -pass 2 -c:a aac -b:a 128k out.mp4

大部分参数比较好理解，需要说明的是这几个参数： 

- ``-y`` 是一个全局参数，表示覆盖文件时不询问。
- ``NUL`` 表示二压的第一步不输出，而行尾的符号表示续行。
  
  - 如果使用 CMD 而不是 Powershell，请使用 ``^`` 代替首行行尾的续行符。
  - 在 Linux 系统上，请使用 ``/dev/null`` 代替 ``NUL``，并使用 ``\`` 代替首行行尾的续行符。
  
- ``-an`` 表示忽略音频流。同理还有 ``-vn/sn/dn``\ 。


.. _bitrate_constrained:

定限码率压制
~~~~~~~~~~~~~~

定限码率压制并不考虑文件大小，而是只限制文件码率；这多见于网络上传视频（或者流媒体传输受到网络条件限制）的场合（参考 :wiki:`Limiting the output bitrate`）。以 libx264/libx265 编码器为例，有以下几种码率限制参数：

- ``-b:v`` 目标平均码率，也即希望得到的输出文件的平均码率（单位 bit/s）。该参数也在二压中被使用。
  
  值得说明的是，输出视频的码率总是大于指定的平均码率的。这是由于容器本身还需要记录元数据等内容（可能占用数百 KB），因此我们总是需要对传入码率参数进行调低。这个码率超出问题在压制短时长视频压制时比较明显，请特别注意。

- ``-maxrate`` 最大码率，需要与 ``-bufsize`` 参数同时使用。
- ``-minrate`` 最小码率。这个较少使用。

只给定平均码率 ``-b:v`` 是一种比较粗糙的码率控制方法。正如上面所说，它会使得输出文件的码率总是略高于指定值。

.. code:: shell

   ffmpeg -i input -c:v libx264 -b:v 8M output.mp4
   
相对的，利用最大码率参数 ``-maxrate`` 与缓冲区参数 ``-bufsize`` 可以更严格地控制码率上限。它会完成一段缓冲区大小就检验一次码率是否符合要求，因此在缓冲区设置上也存在一些技巧。通常，我们将缓冲区设置为与码率值相同。你也可以增大缓冲区，直到发现码率输出开始大幅度高于或低于目标值的临界点，然后以略低于该临界点的值作为缓冲区大小；当然，这需要更多的时间去尝试。

.. code:: shell

   ffmpeg -i input -c:v libx264 -b:v 8M -maxrate 8M -bufsize 8M output.mp4

.. admonition:: 码率选择：如何兼顾质量与文件体积？
   :class: important

   很难对“合适”的码率作出一个精确的定义。在这里，我只简单引用一下 `Youtube 码率建议表 <https://support.google.com/youtube/answer/1722171?hl=en#zippy=%2Cbitrate>`_\ 供大家参考：
   
   * 表中码率的推荐值基于 H.264 编码。
   * 表中推荐高帧率视频使用同规格低帧率 1.5 倍的码率，而 HDR 使用 SDR 1.25 倍的码率。 

   ============= ======= ================== =================== 
   规格           帧率     推荐码率（SDR）      推荐码率（HDR）        
   ============= ======= ================== =================== 
   8K            24~30   80 - 160 Mbps      100 - 200 Mbps   
   \             48~60   120 - 240 Mbps     150 - 300 Mbps
   4K (2160p)    24~30   35 - 45 Mbps       44 - 56 Mbps
   \             48~60   53 - 68 Mbps       66 - 85 Mbps      
   2K (1440p)    24~30   16 Mbps            20 Mbps
   \             48~60   24 Mbps            30 Mbps    
   1080p         24~30   8 Mbps             10 Mbps
   \             48~60   12 Mbps            15 Mbps           
   720p          24~30   5 Mbps             6.5 Mbps
   \             48~60   7.5 Mbps           9.5 Mbps               
   ============= ======= ================== ===================
   
   Youtube 的音频码率推荐则为单声道 128 Kbps、环绕声 384 Kbps 以及 5.1 声道 512 Kbps. 


元数据：添加章节信息
-----------------------

FFmpeg 支持在混流时向视频文件中写入元数据（metadata）；这其中最实用的大概是章节（chapter）跳转的元数据，它得到了许多主流播放器的支持（例如 MPV）。

元数据需要存放在一个外部文件中，并遵循类似 ``ini`` 文件的格式。下面是官方文档 `Metadata - FFmpeg <https://ffmpeg.org/ffmpeg-formats.html#Metadata-1>`_ 页面给出的例子：

.. code-block:: ini

    ;FFMETADATA1
    title=bike\\shed
    ;this is a comment
    artist=FFmpeg troll team

    [CHAPTER]
    TIMEBASE=1/1000
    START=0
    #chapter ends at 0:01:00
    END=60000
    title=chapter \#1
    
    [CHAPTER]
    TIMEBASE=1/1000
    START=60000
    #chapter ends at 0:02:00
    END=120000
    title=chapter \#2
    
    [STREAM]
    title=multi\
    line

* 文件一般在首行含有标记头，以分号开启。上例中的标记头是 ``FFMETADATA``\ ，版本是 1
* 元数据以键值对 ``key=value`` 的形式书写，每对占一行。注意，等号两侧的空格会被保留，因此不推荐留空格。
* 特殊字符

  * 文件中的行如果以 ``;`` 或 ``#`` 开头，则表示注释。
  * 如果键值对中的值含有字符等号 ``=``\ ，反斜线 ``\``\ ，或者注释符号 ``;`` 或 ``#``\ ，那么必须在它们前面加上一个额外的反斜线来转义。

* 元数据可以按章（chapter）或者流（stream）分节，每一节的名称需要 **大写** 且放在中括号内。在第一节之前的键值对，表示全局元数据。
* 每一节内可以指定一个 ``TIMEBASE=n1/n2`` 键，表示章节起止时刻的时间单位，其中 ``n1`` 与 ``n2`` 都必须是正整数。上例中的 ``1/1000`` 表示千分之一秒（即毫秒），因而 ``END=60000`` 表示第一章在第 60000 毫秒也即第 60 秒处结束。如果未指定 ``TIMEBASE`` 键的值，那么会默认使用纳秒（十亿分之一秒，即 :math:`10^{-9}` 秒）。

要将上述元数据（例如存储在 ``FFMETA.ini`` 中）写入到视频文件，使用：

.. code-block:: shell

    ffmpeg -i video.mp4 -i FFMETA.ini -map_metadata 1 -c copy out.mp4

其中的 ``1`` 表示将第二个（因为从0开始索引）输入文件，即第二个 ``-i`` 之后的参数值 ``FFMETA.ini`` 映射为元数据。


元数据：清除元数据
----------------------

通过向 ``-map_metadata`` 参数传递值 ``-1`` 可以清除元数据。我们常用 ``:g`` 后缀来指定清除全局元数据（这不包括其他数据流比如字幕流内部的元数据）。通常，我们想要清除的元数据都是全局元数据：

.. code-block:: shell

   ffmpeg -i video.mp4 -map_metadata:g -1 -c copy out.mp4

如果要尽可能地清除所有元数据（包括编码信息在内），则可以使用比特流过滤器 ``filter_units``\ ；但是，该参数仅支持 H264、VP9、H265、AV1 等部分格式作为输出。下例选自 FFmpeg 文档，它将只保留 NAL 1-5 （也即 VCL）的元数据信息。其中， ``pass_types`` 指定了仅要保留的 NAL 单元信息；与此相反，也可以使用 ``remove_types`` 来指定要清除的 NAL 单元信息。

.. code-block:: shell

   ffmpeg -i video.mp4 -map_metadata -1 -bsf:v 'filter_units=pass_types=1-5' -c copy out.mp4

对于不受 ``-bsf:v filter_units`` 支持的输出格式，我们可以使用一种更老式的方法清除元数据。下例给出了将视频的音频转为 MP3 时，尽可能地清除所有元数据（包括编码信息）：

.. code-block:: shell

   ffmpeg -i video.mp4 -c:a libmp3lame -map_metadata:g -1 -fflags +bitexact -q:a 0 audio.mp3

有时候我们也会再额外添加 ``-flags:v +bitexact`` 与 ``-flags:a +bitexact`` 参数作为补充。


网络视频优化：快速加载
-----------------------

使用 ``-movflags +faststart`` 参数，可以在输出时让视频文件将一些数据前置，从而实现在网络视频未被全部下载时就能够开始播放。


视频稳定/去抖动*
------------------

FFmpeg 支持通过二次处理（2 Pass）的方式进行去抖动：先用 :filter:`vidstabdetect` 过滤器检测并生成一个 ``trf`` 文件，再用 :filter:`vidstabtransform` 根据该文件以及用户给出的去抖动参数，完成图像变换（并通常配合 :filter:`unsharp` 过滤器进行适量锐化）。

以下是一个向 clip.mp4 应用去抖动的例子：

.. code-block:: powershell

   ffmpeg -i clip.mp4 -vf vidstabdetect -f null NUL && `
   ffmpeg -i clip.mp4 -vf vidstabtransform,unsharp=5:5:0.8:3:3:0.4 -crf 17 clip-stablized.mp4

* 第一行行末的 NUL 之后的内容是 Powershell 的换行记号，为了能够一次执行整个过程。如果愿意分两次输入命令，则换行记号不是必须的。
* ``-f null NUL`` 表示 Pass 1 不输出视频文件。尽管如此，Pass 1 会默认生成一个 transform.trf 文件。
* Pass 2 中的过滤器也接受其他参数。常用的是用 ``smoothing`` 指定平滑半径所用的帧数量（默认 10，表示查看前后 10 帧共 21 帧），以及用 ``input`` 指定接受的变换文件的文件名（默认 transform.trf）：
  
  ``-vf vidstabtransform=smoothing=10:input=transform.trf``

* **总是推荐在使用 vidstabtransform 过滤器的同时，也使用 unsharp 过滤器**。本例中 unsharp 过滤器的参数来自官方 FFmpeg 文档的例子。
* 上例中使用了 CRF=17 的高品质输出。在实际中，应按需设置视频质量参数。


像素格式：色深度*
--------------------

为了设置像素格式，例如 YUV 4:2:0、10 bit 色深度，FFmpeg 提供了 ``-pix_fmt`` 参数。用户可以使用 ``ffmpeg -pix_fmts`` 查看支持的像素格式，例如 ``yuv420p10le``\ 。

下例将视频转换为 10bit 色深 420 结果：

.. code-block:: powershell

   ffmpeg -i input.mp4 -pix_fmt yuv420p10le output.mp4


更正色彩空间*
--------------------

以我们最常用的 BT.709 色彩空间为例，许多视频播放器必须检测到色彩空间的元数据信息为 BT.709 才能正常地播放，否则可能引起偏色等问题。如果一个视频在播放时发生了色彩异常（通常发生于在不同设备、屏幕上播放时），那么我们需要检查视频的色彩空间信息并进行修正。

要检查一个视频的现有色彩空间信息，可以使用 FFmpeg 安装时附带的 ``ffprobe`` 工具：

.. code-block:: shell
   
    ffprobe -v quiet -show_streams -select_streams v:0 -i video.mp4 | select-string "color"

以上是 Windows 平台 Powershell 的示例，在 Mac/Linux 平台可以将 ``select-string`` 换为 ``grep`` 命令。上述命令会返回类似的输出结果：

.. code-block:: shell
    
    color_range=tv
    color_space=bt709
    color_transfer=unknown
    color_primaries=bt709

以普通的 SDR 视频为例，上述就是一个正常的输出（因为 ``color_transfer`` 默认跟随了其他两项设置；如果是 HDR 视频，则该参数取值可能不同）。其中， ``color_range`` 也可能是 tv/limited 或者 pc/full。一般而言，只要视频中的 ``color_space`` 与 ``color_primaries`` 已赋值（即不是 unknown），那么视频在播放时就能够正常地还原色彩。

如果发现上述值有较多 unknown，可以在重新编码视频的过程中指定正确的色彩空间。下例对视频用 H.265 进行了重编码并指定 BT.709 色彩空间，建议指定一个 CRF 值或者码率（此处为 8Mb/s）：

.. code-block:: shell
    
    ffmpeg -i "video.mp4" -colorspace bt709 -color_trc bt709 -color_primaries bt709 -c:v libx265 -b:v 8M -c:a copy "colorspace.mp4"

关于更多色彩空间的参数信息，可以参考 FFmpeg 官方文档的 `setparams <https://ffmpeg.org/ffmpeg-all.html#setparams-1>`_ 这一节。


显卡硬件加速*
-------------------

FFmpeg 支持显卡硬件加速；本节主要以 Nvidia 的显卡与 H.264 编码方式为例展示一些用法。

硬件支持
~~~~~~~~~~~~~~~~~~~~~~

关于用户当前的显卡支持哪些编码格式的硬件加速，可以参考 Nvidia 给出的一张表格： `Video Encode and Decode GPU Support Matrix <https://developer.nvidia.com/video-encode-decode-gpu-support-matrix>`_\ 。简要来说，大概是：

* 大多 Maxwell 一代显卡（GTX 745/850/850M/960M 及同代更高型号）支持完整的 H.264 编码硬件加速
* Maxwell 二代（GTX 750/950/965M 及同代更高型号）还支持 4K YUV 4:2:0 的 H.265 编码硬件加速
* 大多 Pascal 显卡（GTX 1050 及同代更高型号）及之后架构的显卡，都支持完整的 H.265 编码硬件加速
* 较新的显卡对于其他主流的编码格式，如 VP9 等，也有硬件加速支持

FFmpeg 支持
~~~~~~~~~~~~~~~~~~~~~~

.. important::

    由于 FFmpeg 存在众多的编译版本，用户正使用的不一定包含了硬件加速功能。但官方提供的预编译版本均涵盖了该功能，本文也不再对如何在编译时引入硬件加速支持进行介绍。

显卡加速使用特殊的编码器（而不是 CPU 编码时的标准编码器），它们通常以 ``nvenc`` （或者 ``cuvid`` ）结尾。用户可以使用 ``-codec`` 来查找当前安装的 FFmpeg 是否在编译时添加了这些编码器的支持。下面是我的古董级 GTX 960M 机器返回的信息，例中可以看到对 H.264 解码器支持 ``h264_cuvid`` 、编码器支持 ``h264_nvenc``。

.. code-block:: shell
   
    # Windows Powershell 用户：ffmpeg -codecs | select-string nvenc
    ffmpeg -codecs | grep nvenc
    ...
    DEV.LS h264                 H.264 / AVC / MPEG-4 AVC / MPEG-4 part 10 (decoders: h264 h264_qsv h264_cuvid ) (encoders: libx264 libx264rgb h264_amf h264_mf h264_nvenc h264_qsv nvenc nvenc_h264 )
    DEV.L. hevc                 H.265 / HEVC (High Efficiency Video Coding) (decoders: hevc hevc_qsv evc_cuvid ) (encoders: libx265 nvenc_hevc hevc_amf hevc_mf hevc_nvenc hevc_qsv )

以 ``h264_nvenc`` 编码器为例，说明几个注意点：

* 编码器 ``h264_nvenc`` 使用与常规编码器 ``libx264`` 不同的 ``-preset`` 参数选项，可以通过如 ``ffmpeg -h encoder=h264_nvenc`` 的命令查看。
* 编码器 ``h264_nvenc`` **不支持 CRF 参数控制压制质量**\ ，用户需要使用其他的参数，比如粗糙的 ``-qp`` 参数，或者 ``-rc`` 参数来指定码率控制模式并配合其他参数（例如 ``-b:v`` 参数）。
* 关于该编码器的详细帮助，可以参考 ``ffmpeg -h encoder=h264_nvenc`` 命令给出的参数列表。

硬件加速命令
~~~~~~~~~~~~~~~~~~~~~~

硬件加速有混合模式（CPU 与 GPU 共同工作）与独占模式（完全 GPU 工作）两种。

混合模式直接指定编码器为支持硬件加速的编码器即可，比如 ``h264_nvenc``\ ：

.. code-block:: shell

    # CPU+GPU 混合模式
    ffmpeg -i video.mp4 -c:v h264_nvenc -c:a copy out.mp4

独占模式需要指定额外的输入参数 ``-hwaccel`` 与 ``-hwaccel_output_format`` 的值为 ``cuda``\ ，表示启用 cuvid 解码器与 nvenc 编码器。

.. code-block:: shell

    # GPU 独占模式
    ffmpeg -hwaccel cuda -hwaccel_output_format cuda -i video.mp4 -c:v h264_nvenc -c:a copy out.mp4

上述命令会自动以 2000 kbps（即 2Mbps）左右的总文件比特率（视频、音频多轨综合，因此单独看视频码率可能会略高于 2M ）来压缩视频。

硬件加速下的质量控制
~~~~~~~~~~~~~~~~~~~~~~

由于 ``h264_nvenc`` 编码器不支持 CRF 参数，我个人的习惯是通过 ``-rc`` 参数来设置 ``vbr_hq`` 可变码率模式，并手动指定 ``-b:v`` 视频码率的数值。例如下述命令使用可变码率模式，并将视频设置在 2Mbps 附近：

.. code-block:: shell

    ffmpeg -hwaccel cuda -hwaccel_output_format cuda -i video.mp4 -c:v h264_nvenc -rc vbr_hq -b:v 2M -c:a copy out.mp4

在此基础上，用户还可以配合 ``-maxrate`` 来限制最大码率、用 ``-bufsize`` 来调整缓冲区大小（缓冲区越小，码率波动越小）、用 ``rc_lookahead`` 来设定前览帧数等。用户可以参考 `FFmpeg Wiki - Limiting the output bitrate <https://trac.ffmpeg.org/wiki/Limiting%20the%20output%20bitrate>`_ 页面。

另一种方式是使用 ``-cq`` 参数。默认的硬件加速结果 q 值（据笔者测试）大约在 25 左右，用户可以通过稍微调高该值来获得压缩效果，例如：

.. code-block:: shell

    ffmpeg -hwaccel cuda -hwaccel_output_format cuda -i video.mp4 -c:v h264_nvenc -rc vbr_hq -cq 28 -qmin 28 -c:a copy out.mp4

其中 ``-qmin`` 参数能够限制最小的 q 值（控制质量上限，减小文件体积）；类似的还有 ``-qmax`` 参数，只不过作用相反。作为参考，笔者使用该命令来转码一个 2250Kbps 视频码率、时长6分钟的 99M 大小的视频文件，得到了 1814Kbps 的大小为 80M 的输出结果。

要查看更多 FFmpeg 硬件加速的内容，比如对 AMD 等硬件的支持，请查看 `HWAccelIntro <https://trac.ffmpeg.org/wiki/HWAccelIntro>`_ 页面。


.. _appendix-fonts-conf:

附录：fonts.conf
-------------------

本文件来源于 `FiveYellowMice/how-to-convert-videos-with-ffmpeg-zh <https://github.com/FiveYellowMice/how-to-convert-videos-with-ffmpeg-zh/blob/master/etc/fontconfig-windows/fonts.conf>`_ 仓库。

.. literalinclude:: fonts.conf
   :language: xml
   :linenos: