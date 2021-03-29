# Kawamoto

2019年入学の川本博詔です。ロボ部のSurfaceに次のものを入れた人です。

- Visual Studio Code
- Python 3.8.5
- C/C++(MinGW)
- OpenJDK
- Node.js
- .NET
- Git
- Windows Subsystem for Linux
- Windows Terminal
- OpenMV

あと、Raspberry Piのデスクトップ化もやりました。

このREADMEには次のものをまとめておきます。

- プログラミングをする上で避けれない前提知識の一部
- 私が入れた各ツールの紹介(公式サイト、インストール時に参考になったサイト)

## Table of Contents

<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Table of Contents](#table-of-contents)
- [ターミナル](#ターミナル)
- [VS Code](#vs-code)
- [Python](#python)
- [C/C++](#cc)
- [Java](#java)
- [Node.js](#nodejs)
- [.NET](#net)
- [Git](#git)
- [Windows Subsystem for Linux](#windows-subsystem-for-linux)
- [Windows Terminal](#windows-terminal)
- [OpenMV](#openmv)
- [Raspberry Pi](#raspberry-pi)

<!-- /code_chunk_output -->

## ターミナル

PowerShellとは: https://www.dospara.co.jp/5info/cts_str_pcuse_powershell

シェルとも呼ばれ、文字列を入力してコンピューターと対話(命令を与える)ができます。この対話方式はCUIと呼ばれています。

Windowsでのシェルの開き方は、画面左下の検索ボックスで「pwsh」または「cmd」と入力、returnです。pwshと入力するとPowerShell、cmdと入力するとコマンドプロンプトが開きます。どちらもシェルの一種です。ときどき「管理者としてPowerShellを開く」という場面があるので、普段からPowerShellを使うことをオススメします。

Macでのシェルは「ターミナル」というアプリです。

Linuxでは`>_`みたいなアイコンの「端末」というアプリケーションです。

「コマンドを実行する」といった文脈があれば、ターミナルに指定された文字列を入力して実行することを意味します。

## VS Code

- 公式サイト<br>https://code.visualstudio.com/
- VS Code入門で参考になったサイト<br>https://zenn.dev/karaage0703/books/80b6999d429abc8051bb

Surfaceでは`code`コマンドが使えます。あと、エクスプローラー上で「Codeで開く」というオプションからファイル/フォルダーをVS Codeで開くことができます。

## Python

- 公式サイト<br>https://www.python.org/
- ドキュメント<br>https://docs.python.org/ja/3.8/
- インストールからVS Codeで使えるようにするまで<br>https://qiita.com/ayuchiy/items/82d6d2dfcf1acc3bec00

anacondaも入っているらしいですが、そこの使い方は入れた人に投げます。

## C/C++

- 公式サイト<br>http://mingw-w64.org/doku.php
- ドキュメント<br>https://ja.cppreference.com/w/%E3%83%A1%E3%82%A4%E3%83%B3%E3%83%9A%E3%83%BC%E3%82%B8<br>https://cpprefjp.github.io/
- インストールからVS Codeで使えるようにするまで<br>https://qiita.com/N_Matsukiyo/items/464594d1fd3e6ef576a4

MinGWが提供しているコンパイラを入れました。コマンドは`gcc`、`g++`です。

## Java

- 公式サイト<br>https://www.oracle.com/jp/java/
- ドキュメント<br>https://docs.oracle.com/javase/jp/8/docs/api/overview-summary.html
- インストールからVS Codeで使えるようにするまで<br>https://qiita.com/msakamoto_sf/items/d65947ddf509acbc98cb

Javaは権利関係が複雑なので、正直オススメできないです。

## Node.js

- 公式サイト<br>https://nodejs.org/ja/
- ドキュメント<br>https://developer.mozilla.org/ja/docs/Web/JavaScript/Reference<br>https://nodejs.org/ja/docs/
- インストールからVS Codeで使えるようにするまで<br>https://qiita.com/GRGSIBERIA/items/b8cd4a2b3635d1bb0391 (途中にgitの紹介がありますが飛ばしてください。)

## .NET

- 公式サイトとドキュメント<br>https://docs.microsoft.com/ja-jp/dotnet/
- インストールからVS Codeで使えるようにするまで<br>https://qiita.com/ronkabu/items/e591214c1477a8d8f434

C#が有名ですが、興味があったらF#を触ってみてください。

## Git

- 公式サイト<br>https://git-scm.com/
- ドキュメント<br>https://git-scm.com/doc
- インストールからVS Codeで使えるようにするまで<br>https://qiita.com/y-tsutsu/items/2ba96b16b220fb5913be

## Windows Subsystem for Linux

Windows Subsystem for Linux (WSL)はWindows内で動かせるLinuxです。

- ドキュメント<br>https://docs.microsoft.com/ja-jp/windows/wsl/
- インストール方法<br>https://docs.microsoft.com/ja-jp/windows/wsl/install-win10

## Windows Terminal

- 公式サイト<br>https://docs.microsoft.com/ja-jp/windows/terminal/
- tips<br>https://qiita.com/whim0321/items/6a6b11dea54642bd6724

## OpenMV

- 公式サイト<br>https://openmv.io/
- ドキュメント<br>https://docs.openmv.io/
- 入門記事<br>https://qiita.com/qmore/items/60d2c776d4a00db5863c

TODO: openmv/READMEに詳しく書く

## Raspberry Pi

ラズパイにはC/C++(`gcc`, `g++`), Python3(`python3`, `python`), VS Code, arduinoを入れてあります。

- VS Codeの入れ方<br>https://qiita.com/optimisuke/items/1cd7440442f7420e6b99
- Arduinoの入れ方<br>https://make.kosakalab.com/make/electronic-work/inst_arduino-ide_raspi/
- OpenMVの入れ方<br>https://docs.openmv.io/openmvcam/tutorial/software_setup.html#linux-raspberrypi

## さいごに

Arduino、ProcessingとVS Codeの連携方法については`Arduino/README.md`, `Processing/README.md`を読んでください。
