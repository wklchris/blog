常用编码器与参数
=====================

.. warning::

    依赖于 FFmpeg 的默认操作是不可取的，因为我们不知道 FFmpeg 会在哪一个版本发布时更改其默认操作。除非不在意任何编码细节，否则请显式地指明编码器及其参数。这也是需要了解编码器参数的原因。

本章介绍一些常用编码器的参数使用方法。绝大部分的内容来自于 FFmpeg 的 trac 百科。


libx264（H.264 视频）
--------------------------

:encode:`H.264` 在很长的一段时间内都是最广泛使用的视频编码方式，其编码器 libx264（参考 :wiki:`libx264_002c-libx264rgb`）很可能是 FFmpeg 用户第一个接触的视频编码器。

在输出 mp4 格式的文件时，如果需要对视频流编码但用户未指定编码器，FFmpeg 将自动调用 libx264 并以其默认参数进行编码。

.. code-block:: shell
   
   # 以下命令等于 ffmpeg -i input.mkv -c:v libx264 output.mp4
   ffmpeg -i input.mkv output.mp4

关于 ``libx264`` 的压制与码率详细使用，我们在前文 :ref:`bitrate_control` 一节已有所提及。为了方便起见，这里对前文稍作小结，并加入了。

* 恒定率系数（CRF）：crf 越小，画面质量越好，但文件体积越大。
  
  * 系数 ``-crf``\ ：对于常见的 8 bit 视频， ``-crf`` 参数可以从 0（无损）到 51（最差压缩）取值，而默认值是 23。一般地，我们只选择 17~28 之间的数值：从视觉观感上，17 已经很接近无压缩的结果，更小的 crf 值徒增文件体积罢了。对于 10 bit 视频， ``-crf`` 参数的取值是 0~63。
  * 预案 ``-preset``\ ：指导视频压制的质量。越慢的预案，压缩越好，即输出同等质量的视频所需的文件体积越小。预案从快到慢包括：ultrafast, superfast, veryfast, faster, fast, medium（默认）, slow, slower, veryslow。
  * 风格 ``-tune``\ ：告知输入视频的风格。风格包括：
    
    - animation：动画。提升去块（deblocking）强度与参考帧数量。
    - fastdecode：快速解码。禁用滤镜来加快解码。
    - film：电影。降低去块强度。
    - grain：颗粒。保留旧电影的颗粒感。
    - stillimage：静止图像。适用于相片幻灯片或类似主题的内容。
    - zerolatency：零延迟。适用于快速编码，或者低延迟流媒体内容。

  一个 CRF 的例子：

  .. code:: shell

     ffmpeg -i video.mp4 -c:v libx264 -preset slow -tune film -crf 20 -c:a copy out.mp4

* 定限码率压制：适用于强制要求码率的场合，比如直播。请参考 :ref:`bitrate_constrained` 一节的内容。
* 二压（2Pass）：适用于强制要求文件大小的场合。请参考 :ref:`2pass` 一节的内容。    

libmp3lame（MP3 音频）
--------------------------

:encode:`MP3` 曾经是最为流行的压缩音乐格式。FFmpeg 通过 :wiki:`libmp3lame` 编码器对 MP3 编码提供支持，一般有可变比特率、固定比特率、平均比特率三种质量控制方式。

可变比特率（VBR）
~~~~~~~~~~~~~~~~~~~~

一般地，推荐利用可变比特率（VBR）来编码 MP3 音频：

.. code-block:: shell
   
   ffmpeg -i input.wav -c:a libmp3lame -q:a 2 output.mp3

其中，质量参数 ``-q:a`` （或者其全称 ``-qscale:a``\ ）用于控制 MP3 品质。编码器 libmp3lame 支持 0~9 的质量参数，其中 0 表示最高质量（最高比特率，245 kbps 左右），而默认值是 4。一般认为 0~3 的取值可以达到令人满意的质量。

FFmpeg 比特率参数与实际比特率范围（kbps）有如下对应关系：

.. list-table:: FFmpeg 比特率参数与实际比特率范围对照表
   :widths: 10 10 10
   :header-rows: 1
   :align: center

   * - 参数
     - 平均比特率
     - 比特率范围
   * - -b:a 320k\*
     - 320
     - 320 (CBR)
   * - -q:a 0
     - 245
     - 220 ~ 260
   * - -q:a 1
     - 225
     - 190 ~ 250
   * - -q:a 2
     - 190
     - 170 ~ 210
   * - -q:a 3
     - 175
     - 150 ~ 195
   * - -q:a 4
     - 165
     - 140 ~ 185
   * - -q:a 5
     - 130
     - 120 ~ 150
   * - -q:a 6
     - 115
     - 100 ~ 130
   * - -q:a 7
     - 100
     - 80 ~ 120
   * - -q:a 8
     - 85
     - 70 ~ 105
   * - -q:a 9
     - 65
     - 45 ~ 85

\* *此为 MP3 所支持的最高码率，但在实际应用中并不推荐。详情请参考下文中关于固定比特率（CBR）部分的内容。*

固定比特率（CBR）
~~~~~~~~~~~~~~~~~~~~

除了可变比特率，在网络上分享的 MP3 文件也常常采用固定比特率（CBR）编码，如 128, 192, 256 kbps。编码器 libmp3lame 通过 ``-b:a`` 参数支持一系列固定比特率，分别是 8, 16, 24, 32, 40, 48, 64, 80, 96, 112, 128, 160, 192, 224, 256, 以及 320 kbps。

.. warning::
   
   一般认为在 MP3（或者其他压缩格式上）追求高码率（如 320 kbps） 是没有意义的，因为 VBR 0~3 的质量对压缩格式已经足够好。毕竟无论如何，MP3 都是有损压缩；想要更高的质量，建议转向 FLAC 等无损格式。

下例将音频以 192 kbps 的固定码率输出为 MP3（不要忘记码率数字后面的字母 "k"）：

.. code-block:: shell
   
   ffmpeg -i input.wav -c:a libmp3lame -b:a 192k output.mp3

平均比特率（ABR）
~~~~~~~~~~~~~~~~~~~~

平均比特率（ABR）介于固定与可变之间，可以向参数 ``-abr`` 赋值 ``1`` 来启用。除此之外，libmp3lame 编码器此时仍需要 ``-b:a`` 的码率参数作为指导：

.. code-block:: shell
   
   ffmpeg -i input.wav -c:a libmp3lame -abr 1 -b:a 192k output.mp3

