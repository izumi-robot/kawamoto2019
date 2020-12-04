# Python

Windowsが前提とします。家のWi-Fiにつながった状態で作業を行って下さい。

## 目次

1. 環境構築
    1. インタプリタのインストール
    2. VSCodeのセットアップ
2. 実行方法
    1. REPL
    2. Pythonファイル
3. おまけ: 入門サイト

## 環境構築

ググるとanacondaとかjupyterとかいろいろ出てくるんですけど、ここではコンピュータにPythonコマンドを入れるという方針で紹介します。

### インタプリタのインストール

https://www.python.org/downloads/release/python-385/
このページの下のほうにOSごとのインストーラなどのリンクのリストがあります。ここから`Windows x86-64 executable installer`をダウンロードします。
ダウンロードしたものを開くとインストーラが立ち上がります。「Add Python3.8 to PATH」というオプションにチェックを入れ、後はそのままで進めていきます。インストールが完了したらパソコンを再起動して下さい。
再起動後にコマンドプロンプトを開き、`python`コマンドが問題なく実行出来たらインストールは成功です。

### VSCodeのセットアップ

「Python」という拡張機能をインストールし、画面左下に出てくる指示に従って下さい。指示がなくなったら、Ctrl+@でターミナルを開き、`python -m pip install --upgrade pip`を実行します。

## 実行方法

### REPL

REPL(Read Evaluate Print Loop)とは、コマンドライン上でPythonを簡易的に実行できる機能です。開き方は、`python`コマンドです。実際の出力を載せておきます。

```
PS C:\Users\robo> python
Python 3.8.5 (tags/v3.8.5:580fbb0, Jul 20 2020, 15:57:54) [MSC v.1924 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> print('Hello world!')
Hello world!
>>> exit()
PS C:\Users\robo> 
```

### Pythonファイル

`Python [実行するファイル名].py`です。例えば、`sample.py`というファイルを実行する場合は`python sample.py`です。ファイル名に空白がある場合は"ダブルクオーテーション"で囲って下さい。これも例を載せておきます。

```
PS C:\Users\robo\Desktop\2019\kawamoto\Python> python helloworld.py
Hello world!
PS C:\Users\robo\Desktop\2019\kawamoto\Python>
```

## おまけ: 入門サイト

http://docs.python.org/ja/3/tutorial/index.html
公式のチュートリアルです。ここの「2. 形式ばらないPythonの紹介」からがおすすめです。ほかのプログラミング言語、パソコンのOSに関する記述などのPythonそのものに関係ないものは読み飛ばしても構いません。サンプルコードは全て、何をしているのか理解するようにしましょう。
