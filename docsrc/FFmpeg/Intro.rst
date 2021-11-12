FFmpeg 引言
================

FFmpeg 是一个强大的命令行音视频工具，可以承担转码、混流、嵌挂字幕、剪辑等工作。

本章介绍安装与一些视频的基本概念。

安装
----

*本小节的内容以 Windows 用户为例。*

前往官网提供 `官方的 Windows 版本 build <https://ffmpeg.zeranoe.com/builds/>`_ 进行下载。我一般在下载时选择 Version 有版本号、 Linking 为 Static 的版本进行下载。

下载完成后，将内容解压到你的硬盘某处，例如：\ ``C:\FFmpeg``\ 。如果之前安装过独立的 FFmpeg，可以覆盖到老版本的文件夹。之后，将安装路径添加到系统的 Path 环境变量。

最后，检查是否能从命令行正常启动。打开 PowerShell，输入：

.. code:: shell

   ffmpeg

来查看返回的版本号是否与你下载的一致。

-  如果你的电脑上安装了多个 FFmpeg（有时候其他软件会安装 FFmpeg 作为基础组件，比如 ImageMagick），可以通过 ``which ffmpeg`` 来查看被调用的 FFmpeg 路径，以确认是否调用了希望调用的 FFmpeg。
-  如果 ``ffmpeg`` 命令调用了别处的 FFmpeg，你可以考虑将刚安装的 FFmpeg 的路径移动到 Path 环境变量列表中的靠前的位置，使 Windows 在查找设备上的 FFmpeg 时优先寻到这个版本。


基本视频概念
------------

在介绍 FFmpeg 的工作命令之前，我们首先对视频文件内部的一些概念做一个通俗的说明。注意： *以下的说明可能存在不准确之处，仅作大致理解用* 。

- 流（stream）：通常的视频文件中最易见的是视频流与音频流两个流。部分视频文件（多为 mkv 文件）还有字幕流，即内挂字幕。注意，有的视频将字幕嵌入到了视频流中（内嵌字幕），这类视频没有字幕流，也无法提取出字幕文件。至于数据流，本文不作介绍。

   - 分流/混流（mux/demux）：将多个流从一个视频文件中对应地抽取出来，称为分流。反之，将多个流整理后写入某个文件，称为混流。
   - 容器：可以粗略地理解为某种扩展名类型的视频文件。比如 MP4 是一种容器，MKV 是另一种容器。

- 编码/解码（encode/decode）：将流用某种格式或规范记录下来并存储，称为编码；将编码后的流，根据格式或规范来逆向实现编码的过程，从而将流还原出来，称为解码。我们最经常听到的规范大概是 H.264，最常见到的编码器可能是 libx264。

.. _codec_format:

常用的编码格式
---------------

FFmpeg 支持基本所有的主流编码格式。

常用的视频编码格式有：

* `H.264 <https://trac.ffmpeg.org/wiki/Encode/H.264>`_ 是上一代最广为使用的视频编码格式，始于 2003 年，当之无愧的一代霸主。在 FFmpeg 中可由 ``libx264`` 编码器支持。
* `H.265/HEVC <https://trac.ffmpeg.org/wiki/Encode/H.265>`_ 是 H.264 的接任者，于 2013 年正式面世。它在同等视频质量下提供了相比 H.264 而言可达 50% 的体积缩减。 ``libx265`` 编码器对该编码格式提供了支持。
* `VP9 <https://trac.ffmpeg.org/wiki/Encode/VP9>`_ 经历了从 VP3 起漫长的版本迭代，VP 系列解码器的开发公司 On2 被谷歌收购。谷歌在 2013 年左右推出了取代上一代 VP8 编码的 VP9，主要为旗下的互联网视频平台 Youtube 所采用。 
* `AV1 (AOMedia Video 1) <https://trac.ffmpeg.org/wiki/Encode/AV1>`_ 是 H.265 的免版税竞争者，极大地基于 VP9 的技术，并在 VP9 的基础上提供了惊人的压缩比率。其开发联盟由诸多互联网公司支持，并受到主流浏览器 Chrome 与 Firefox 的积极推动。它在 FFmpeg 中由 ``libaom-av1`` 编码器对该编码格式提供支持。

.. figure:: Compare.png
   :width: 90%
   :align: center
   :target: http://www.compression.ru/video/codec_comparison/hevc_2017/MSU_HEVC_comparison_2017_P5_HQ_encoders.pdf
   
   AV1、x265、VP9 等主流编码器的平均压缩比。
   
图源: CS MSU Graphics & Media Lab, Video Group. MSU Codec Comparison 2017 Part V: High Quality Encoders. 2018. p19.（点击图片跳转）


常用的音频编码格式有：

* `MP3 <https://trac.ffmpeg.org/wiki/Encode/MP3>`_ 时至今日仍最流行的有损编码格式。编码器 ``libmp3lame``\ 。
* `AAC <https://trac.ffmpeg.org/wiki/Encode/AAC>`_ 是 MP3 的接任者，常常作为视频容器 MKV 选用的音频格式，而其作为音频时的容器则通常是是 m4a。编码器有 FFmpeg 原生提供的、针对低码率音频（AAC LC）的 ``aac`` 编码器；此外，需要制作高质量 AAC 时（HE-AAC）可以使用 ``libfdk_aac`` 编码器。
* AC3 杜比数字格式，编码器 ``ac3`` (Dolby Digital) 或者 ``eac3`` (Dolby Digital Plus)。
* FLAC 是较常用的无损音频格式；FFmpeg 对其有原生的编码器 ``flac`` 支持。
* PCM 是 WAV 容器内包含的最常见音频编码格式。FFmpeg 默认使用 ``pcm_s16le`` 编码器来处理 PCM 输出。关于这部分的内容，读者可以参考 `PCM 格式 <https://trac.ffmpeg.org/wiki/audio%20types>`_ 页面。
