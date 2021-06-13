<!--
VSCodeで開いている場合は、このファイルの編集画面上にカーソルを置いてからCtrl + Shift + Vを押してみてください。
-->

<!-- omit in toc -->
# Kawamoto

川本博詔です。ロボ部のSurfaceに次のものを入れた人です。

- Visual Studio Code
- Python 3.8.5
- C/C++ (MSYS2)
- OpenJDK
- Node.js
- .NET
- Git
- Windows Subsystem for Linux (WSL)
- Windows Terminal
- OpenMV

あと、Raspberry Piのデスクトップ化もやりました。

このREADMEには次のものをまとめておきます。

- プログラミングをする上で避けれない前提知識の一部
- 私が入れた各ツールの紹介(公式サイト、インストール時に参考になったサイト)

<!-- omit in toc -->
## Table of Contents

- [ターミナル](#ターミナル)
- [VSCode](#vscode)
- [Arduino](#arduino)
- [Processing](#processing)
- [Python](#python)
- [Anaconda](#anaconda)
- [C/C++](#cc)
- [Java](#java)
- [Node.js](#nodejs)
- [.NET](#net)
- [Git](#git)
- [Windows Subsystem for Linux](#windows-subsystem-for-linux)
- [Windows Terminal](#windows-terminal)
- [OpenMV](#openmv)
- [Raspberry Pi](#raspberry-pi)
- [Raspberry Pi Pico](#raspberry-pi-pico)

## ターミナル

PowerShellとは: https://www.dospara.co.jp/5info/cts_str_pcuse_powershell

シェルとも呼ばれ、文字列を入力してコンピューターと対話(命令を与える)ができます。この対話方式はCUIと呼ばれています。

Windowsでのシェルの開き方は、画面左下の検索ボックスで「pwsh」または「cmd」と入力、returnです。pwshと入力するとPowerShell、cmdと入力するとコマンドプロンプトが開きます。どちらもシェルの一種です。ときどき「管理者としてPowerShellを開く」という場面があるので、普段からPowerShellを使うことをオススメします。

Macでのシェルは「ターミナル」というアプリケーションです。

Linuxでは`>_`みたいなアイコンの「端末」というアプリケーションです。

**「コマンドを実行する」といった文脈があれば、ターミナルに指定された文字列を入力して実行することを意味します。**

## VSCode

- 公式サイト<br>https://code.visualstudio.com/
- VSCode入門で参考になったサイト<br>https://zenn.dev/karaage0703/books/80b6999d429abc8051bb

Surfaceでは`code`コマンドが使えます。あと、エクスプローラー上で「Codeで開く」というオプションからファイル/フォルダーをVSCodeで開くことができます。

## Arduino

- 公式サイト<br>https://www.arduino.cc/
- リファレンス
  - 英語版<br>https://www.arduino.cc/reference/en/
  - 日本語版<br>https://garretlab.web.fc2.com/arduino_reference/
- Arduino入門<br>https://deviceplus.jp/hobby/arduino-listicle-01/

VSCodeとの連携方法、自作ライブラリの作り方は`Arduino/README.md`を参照してください。

## Processing

- 公式サイト<br>https://processing.org
- リファレンス(英語)<br>https://processing.org/reference
- Processing学習ノート(Processing入門で参考になったサイトです)<br>https://www.d-improvement.jp/learning/processing/

VSCodeとの連携方法は`Processing/README.md`を参照してください。

## Python

- 公式サイト<br>https://www.python.org/
- リファレンス<br>https://docs.python.org/ja/3.8/
- インストールからVSCodeで使えるようにするまで<br>https://qiita.com/ayuchiy/items/82d6d2dfcf1acc3bec00

Pythonだけだと弱いので、C++あたりも書けるようになっておくのがオススメです。

## Anaconda

- 公式サイト<br>https://www.anaconda.com/
- インストール方法<br>https://www.python.jp/install/anaconda/
- PythonとAnacondaの違い<br>https://www.python.jp/install/docs/pypi_or_anaconda.html

## C/C++

- リファレンス<br>https://ja.cppreference.com/w/%E3%83%A1%E3%82%A4%E3%83%B3%E3%83%9A%E3%83%BC%E3%82%B8<br>https://cpprefjp.github.io/
- 入門サイト
    - 江添亮のC++入門<br>https://ezoeryou.github.io/cpp-intro/
    - 苦しんで覚えるC言語<br>https://9cguide.appspot.com/
    - AtCoder Programming Guide<br>https://atcoder.jp/contests/APG4b

ロボット部のSurfaceにはMSYS2経由でGNUコンパイラを入れました。コマンドは`gcc`、`g++`です。あと、江添亮のC++入門は聖書です。VSCodeとの連携方法についてはドンピシャな記事がなかったので自分で書きました。`Clang/README.md`を見てください。

## Java

- 公式サイト<br>https://www.oracle.com/jp/java/
- リファレンス<br>https://docs.oracle.com/javase/jp/8/docs/api/overview-summary.html
- インストールからVSCodeで使えるようにするまで<br>https://qiita.com/msakamoto_sf/items/d65947ddf509acbc98cb

Javaは権利関係が複雑なので、正直オススメできないです。

## Node.js

- 公式サイト<br>https://nodejs.org/ja/
- リファレンス<br>https://developer.mozilla.org/ja/docs/Web/JavaScript/Reference<br>https://nodejs.org/ja/docs/
- インストールからVSCodeで使えるようにするまで<br>https://qiita.com/GRGSIBERIA/items/b8cd4a2b3635d1bb0391<br>途中にgitの紹介がありますが飛ばしてください。

JavaScriptを使えると給料が上がるらしいです。

## .NET

- 公式サイトとリファレンス<br>https://docs.microsoft.com/ja-jp/dotnet/
- インストールからVSCodeで使えるようにするまで<br>https://qiita.com/ronkabu/items/e591214c1477a8d8f434

C#が有名ですが、興味があったらF#を触ってみてください。

## Git

- 公式サイト<br>https://git-scm.com/
- ドキュメント<br>https://git-scm.com/book/ja/v2
- インストールからVSCodeで使えるようにするまで<br>https://qiita.com/y-tsutsu/items/2ba96b16b220fb5913be

Surfaceには`git`コマンドをいれてあります。モダンプログラマになるためには必須のツールです。

## Windows Subsystem for Linux

Windows Subsystem for Linux (WSL)はWindows内で動かせるLinuxです。

- ドキュメント<br>https://docs.microsoft.com/ja-jp/windows/wsl/
- インストール方法<br>https://docs.microsoft.com/ja-jp/windows/wsl/install-win10

## Windows Terminal

- 公式サイト<br>https://docs.microsoft.com/ja-jp/windows/terminal/
- tips<br>https://qiita.com/whim0321/items/6a6b11dea54642bd6724

## OpenMV

- 公式サイト<br>https://openmv.io/
- リファレンス<br>https://docs.openmv.io/
- 入門記事<br>https://qiita.com/qmore/items/60d2c776d4a00db5863c

OpenMVは知名度が低すぎて日本語記事がほとんどありません。そのため、最初から公式のリファレンス(上記URL)で探した方が早いです。`openmv/README.md`により詳しい説明があります。

## Raspberry Pi

ラズパイにはC/C++(`gcc`, `g++`), Python3(`python3`, `python`), VSCode, arduinoを入れてあります。

- 公式サイト<br>https://www.raspberrypi.org/
- 入門<br>https://deviceplus.jp/hobby/entry_001/

`raspberrypi/README.md`に色々とまとめました。

## Raspberry Pi Pico

Arduino Nanoの完全上位互換です。

- 公式サイト<br>https://www.raspberrypi.org/documentation/rp2040/getting-started/
- 環境構築
  - C/C++<br>https://qiita.com/iwatake2222/items/33b4cd3a39da5a44dc02
  - MicroPython<br>https://rikoubou.hatenablog.com/entry/2021/02/05/150631
- リファレンス(MicroPython)<br>http://docs.micropython.org/en/latest/

詳しい情報は`rasp-pico`を参照してください。
