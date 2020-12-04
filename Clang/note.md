---
title: Visual Studio Codeを使用したC言語学習の準備
tags: C VisualStudioCode コンパイル 拡張機能 初心者
author: N_Matsukiyo
slide: false
---
コメントいただいた場合など、適宜改善を行なっております。ご留意ください。

# はじめに

ここでは[Visual Studio Code](https://azure.microsoft.com/ja-jp/products/visual-studio-code/)を用いてC言語の学習をするための準備をします。Visual Studio Code(以下、VSCode)は、Microsoftが提供しているフリーのエディタです。初心者にも扱いやすいと思います。また、Mac、Linux、Windowsで使用可能なので大変便利です。
※この記事では主にWindows、Macを主眼において説明します。

# ダウンロード

ダウンロードは[こちら](https://code.visualstudio.com/download)から
各自のOSに合わせてダウンロード、インストールしてください。
インストールが終わったら次の項目へ

# ソースファイルを作成する

プログラムが書き込んであるファイルをソースファイルと呼びます。今回は、初めてプログラムを作成するときによく使われる「Helloworld」のプログラムを例に実行まで説明します。まず、空のソースファイルを作成しましょう。作成には、主に２通りの方法があります。

## 1. エクスプローラから新規ファイルを作成する

### Windows

任意のフォルダで、右クリックをし[新規作成]→[テキスト ドキュメント]を選択しましょう。すると、名前の変更を要求されるので、「Helloworld.c」にしてください。このとき(.txt)は消すようにしてください。
> **拡張子の表示・非表示**
> 拡張子とは、ファイルの種類を識別するための文字列です。ファイル名には必ず拡張子があり、ドット以下に記述されます。普段あまり意識することはないかもしれませんが、プログラムを扱う上では拡張子は重要になります。拡張子が非表示になっている場合には、リンクの記事をご覧ください。
[[Windows]拡張子の表示・非表示](http://qiita.com/NaokiMatsukiyo/items/1e32782f28b0ed89055c)

### Mac

Macでは、標準の設定ではWindowsのように新規にファイルを作成することはできません。「XtraFinder」というソフトを使用すれば、作成できるようになるようです。詳しくは検索してみてください。
[XtraFinder](http://www.trankynam.com/xtrafinder/)

## 2. Visual Studio Codeから新規ファイルを作成する

<img width="500" alt="新規ファイル作成_1" src="https://qiita-image-store.s3.amazonaws.com/0/155265/4ca0b3ae-0ca4-cdcd-b6e5-8a5c096e4cf6.png">

VSCodeのファイルメニューより、新規ファイルを選択します。そうすると、新規ファイルへの記述が可能になります。

<img width="500" alt="新規ファイル作成_2" src="https://qiita-image-store.s3.amazonaws.com/0/155265/23733363-bbdd-c88d-0912-1ece0daa7474.png">

このまま記述しても構わないのですが、ここではファイルの保存を優先したいと思います。

<img width="500" alt="新規ファイル作成_3" src="https://qiita-image-store.s3.amazonaws.com/0/155265/5ffe9b5c-b9d7-fc5e-340d-9e7daf936c2d.png">

[名前をつけて保存]を選択します。このとき、ファイルの拡張子(.c)をつけるのを忘れないでください。

|ショートカットキー|Windows|Mac|
|:--:|:--:|:--:|
|名前をつけて保存...|Ctrl+Shift+S|⇧⌘S|

<img width="500" alt="スクリーンショット 2017-05-01 18.23.33.png" src="https://qiita-image-store.s3.amazonaws.com/0/155265/e088e22d-7889-ed46-20a7-00868e2d7919.png">

保存が完了したら、そのファイルへの記述が可能になります。その後は定期的に保存をするようにしましょう。

|ショートカットキー|Windows|Mac|
|:--:|:--:|:--:|
|保存|Ctrl+S|⌘S|

# 「Helloworld」の記述

「Helloworld」のプログラムは以下の通りです。コピーすることもできますが、せっかくなので手で打ってみることをお勧めします。

```c:Helloworld.c
#include<stdio.h>

int main(void){
  printf("Helloworld\n");

  return 0;
}
```

終わったら保存を忘れずに......

# 拡張機能のインストール

VSCodeには、豊富な拡張機能があります。今回はC言語用の拡張機能をインストールしましょう。

<img width="500" alt="拡張機能_1" src="https://qiita-image-store.s3.amazonaws.com/0/155265/ab6a57ba-6207-6308-3496-b966bd451da1.png">

まず、拡張機能のパネルを表示します。
赤い丸で示されたところをクリックします。

<img width="500" alt="拡張機能_2" src="https://qiita-image-store.s3.amazonaws.com/0/155265/c8a3ddc2-487b-4325-da7e-f0a2d3aa06cc.png">

検索フォームに"C/C++"と入力します。一番上に出てきた拡張機能をインストールします。インストールが終了したら、有効化するために[再度読み込む]をクリックしてください。

以上で、拡張機能のインストールは終了です。

# プログラムの実行

プログラムを実行するにはいくつかの方法がありますが、ここではVisual Studio Code内で実行する方法を紹介します。ここでは、ターミナルというものを使用します。まずは、ターミナルを表示しましょう。

<img width="500" alt="プログラムの実行_1" src="https://qiita-image-store.s3.amazonaws.com/0/155265/7d9ce922-ba53-f6d1-cf5a-c12b97eb08b5.png">

[表示]の[統合ターミナル]を選択します。

## コンパイル

さて、プログラムを実行するにはコンパイルをする必要があります。プログラムをコンパイルして、実行ファイルを作成する必要があるのです。このコンパイルをするためにはパソコンにコンパイラというものをインストールする必要があります。今回は、コンパイラとして[gcc](https://ja.wikipedia.org/wiki/GNU%E3%82%B3%E3%83%B3%E3%83%91%E3%82%A4%E3%83%A9%E3%82%B3%E3%83%AC%E3%82%AF%E3%82%B7%E3%83%A7%E3%83%B3)を使用します。

## コンパイラのインストール

ここからは、WindowsとMacで操作が大きく異なります。
### Windows

#### パッケージ管理ツールのインストール

Windowsでは、[MinGW](https://ja.wikipedia.org/wiki/MinGW)をインストールします。これをインストールすることにより、gccが使用可能になります。
まずは、MinGWを[こちら](http://www.mingw.org/)からダウンロードしてください。

<font color="red">__MinGWの32bit版、64bit版について※2020/5/8__</font>

> コメントにて、MinGWが32bit版であるからうまく動作しないのではないかという意見をいただいております。MinGWはgcc以外に様々なパッケージを扱っているために64bit版であるMinGW-w64が存在しています。しかし、gccそのものはアーキテクチャに依存しないため、32bit版と64bit版のMinGWのどちらでインストールしてもgccは同じものがインストールされます。したがって、記事内の32bit版MinGWでインストールした場合でも64bit版OSで動作すると考えられます。もし間違いがありましたら是非コメントをいただきたいと思います。

**ダウンロード方法が変わっていたので編集しました。※2020/2/25**

<img width="500" alt="スクリーンショット 2020-02-25 15.57.41.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/155265/824c510d-b388-0481-7bbb-5b8e9f0e9b95.png">

右上の[Download]をクリックしてください。

<img width="500" alt="スクリーンショット 2020-02-25 15.58.06.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/155265/8c19a62a-f9fd-0c62-1be6-cf56f610caec.png">

赤い枠のボタンをクリックして、インストーラーをダウンロードしてください。

ダウンロードが終わったら、ダウンロードしたファイルを実行します。

<img width="500" alt="スクリーンショット 2017-05-01 22.24.40.png" src="https://qiita-image-store.s3.amazonaws.com/0/155265/187cfaf7-c2a6-5975-446c-771b80c468eb.png">

このとき特にインストールディレクトリを変更する必要はありません。そのまま、[Continue]をクリックしてください。

#### パッケージのインストール

続いて、C言語をコンパイルするパッケージをインストールします。

<img width="500" alt="mingwgui_setup" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/155265/fdb39495-517f-770c-92f7-cc520b958f57.jpeg">

`mingw32-base-bin`
にチェックを入れてください。
**チェックを2つから1つに変更しました。※2020/5/8**

<img width="500" alt="パッケージ_2" src="https://qiita-image-store.s3.amazonaws.com/0/155265/8c0de58d-75f4-ea7e-f737-120c81ec8e3a.png">

左上の[Installation]から[Apply Changes]を選択します。

<img width="500" alt="パッケージ_3" src="https://qiita-image-store.s3.amazonaws.com/0/155265/6d020ee0-c1ae-a146-9f4d-ea1ab27c615a.png">

[Apply]をクリックして終了です。

#### gccの有無の確認

<font color="red">__新規追加しました。※2020/5/8__</font>
ここまで完了したら、MinGWフォルダが作成されているかを確認してください。C言語をコンパイルするためには、gccが必要です。gcc.exeファイルが存在するかどうかを確認してください。デフォルトでは、`C:¥MinGW¥bin`のフォルダの中に`gcc.exe`が存在しているはずです。

#### 環境変数PATHの設定

<font color="red">__大幅に変更しました。※2020/5/8__</font>
コントロールパネルを起動し、コントロールパネル＞システムとセキュリティ＞システムから「システムの詳細設定」を開きます。

すると、以下のような「システムのプロパティ」が起動します。
一番下の[環境変数]をクリックしてください。

<img width="500" alt="システムのプロパティ" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/155265/407543e4-3616-0670-7940-850ef8f40c4d.jpeg">

その後、「環境変数」が起動します。これからgccへのパスを通してgccを利用できるようにします。下側の「システム環境変数」の変数中から「Path」を探して“選択”して、[編集]をクリックします。

すると、以下のような画面が表示されます。
右上の新規を押し、`C:¥MinGW¥bin`を追加してください。

<img width="500" alt="環境変数の追加" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/155265/14736422-8016-730a-c934-0ef97db8becc.jpeg">

これでgccが利用できるようになります。

**もしもgccが動作しない場合は、Pathの設定がうまくいってないと思われます。**
当記事以外も参考にし、状況を切り分けながら検討していただければと思います。

### Mac

Macに関しては、わかりやすい記事がありましたのでリンクさせていただきます。
[Macにgccをインストールする](http://qiita.com/ShinichiOkayama/items/962e55ac7f8920a5f007)

## ターミナルでの移動

さて、gccが使用可能になったので、先ほど作った「Helloworld.c」をコンパイルし、実行ファイルにしてみたいと思います。

まずはターミナルにて「Helloworld.c」のファイルが保存されている場所まで移動しなくてはいけません。コマンドを利用して各自がソースファイルを保存した場所まで移動してみましょう。なお注意しないといけないのは、いきなり遠くのフォルダには移動できないということです。ターミナルに表示されている場所の1つ上か1つ下でないと動けません。地道に頑張ってみてください。


|コマンド一覧|意味|
|:--:|:--:|
|cd ~~~|~~~の名前のフォルダに移動する|
|cd ..|1つ上の階層に上がる|
|ls|現在の階層にあるファイル(フォルダ)名を表示する|

おそらくこの3つのコマンドさえ使えれば、移動できるはずです。もしわからなければ、検索してみましょう。

では、目的の階層にたどり着いたとします。
コマンドで「ls」と打って、下のように表示されればたどり着いています。

```:Windows
PS C:\Users\user_name>test> ls
Mode          LastWriteTime          Length Name            
----          -------------          ------ ----
-a----    2017/05/01  00:00              79 Helloworld.c
PS C:\Users\user_name>test>
```

```:Mac
MacBook-Pro:test user_name$ls
Helloworld.c
MacBook-Pro:test user_name$
```

## プログラムの実行ファイル作成

さて、ソースファイルの置かれた階層で次のコマンドを入力すると実行ファイルが作成されます。

```:Terminal
PS C:\Users\user_name>test> gcc -o program Helloworld.c

MacBook-Pro:test user_name$gcc -o program Helloworld.c
```

仮にエラーがあった場合は、エラーが表示されますので、エラーをよくみてプログラムを修正してください。
うまく実行ファイルが作成された場合は、何も表示されません。

## 実行ファイルを実行

ついに最後です。上の項目で「-o program」と入力しましたが、これは実行ファイルの名前を指定するコマンドでした。「ls」を入力したら確認できますが、今いる階層に「program」という実行ファイルが作成してあるはずです。
では、最後に実行してみましょう。なお、実行するときにはファイル名の前に「./」をつけるのを忘れないでください。

```:Terminal
PS C:\Users\user_name>test> ./program

MacBook-Pro:test user_name$./program
```

# 終わりに

いかがだったでしょうか。
かなり噛み砕いて説明しているところもあるので、もっと理解したいという人はぜひ検索してみてください。今後検索能力というのはとても重要になってきます。ぜひ自力で解決してみてください。

C言語を1日も早くマスターできることを祈っています。
