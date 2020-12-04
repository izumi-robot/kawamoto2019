# Kawamoto(2019)

<!-- Ctrl+Shift+Vでプレビューを見ることができます。 -->

## 目次

* 自己紹介
* 前置き
* コマンドライン
* VSCodeの使い方
  * ファイル、フォルダを開く
  * 拡張機能
  * コマンドパレット
  * ターミナル
* マークダウンとは
  * 見出し
  * 強調
  * 箇条書き
  * リンク
  * インラインコード
  * ブロックコード
* JSONについて
* 終わりに

## 自己紹介

2019年入学の川本博詔です。ロボ部のSurfaceに[VSCode](https://ja.wikipedia.org/wiki/Visual_Studio_Code)を入れた人です。

## 前置き

ここに書いたことは基本的にググった内容をまとめたものです。参考にしたサイトのリンクを所々に貼っておきます。ここに書いてないことはググれば多分出てきます。
このREADMEではVSCodeを使ってプログラミングをしていく上で避けては通れないところを紹介します。是非参考にして下さい。

## コマンドライン

コマンドラインはシェルとも呼ばれ、文字列を入力してコンピュータと対話(命令を与える)ができます。この対話方式はCUIと呼ばれています。

Windowsでのシェルの開き方は、画面左下の検索ボックスで「pwsh」または「cmd」と入力、returnです。pwshと入力するとPowerShell、cmdと入力するとコマンドプロンプトが開きます。どちらもシェルの一種です。時々「管理者としてPowerShellを開く」という場面があるので、普段からPowerShellを使うことをおすすめします。

Macでのシェルは「ターミナル」というアプリです。

Linuxでは`>_`みたいなアイコンの「端末」というアプリケーションです。

## VSCodeの使い方

参考:
https://www.atmarkit.co.jp/ait/articles/1507/10/news028.html

今ロボ部で使っている機能だけを紹介します。
VSCodeは無料で使えるコードエディタです。「拡張機能」というものを使って様々な機能(シンタックスハイライト等)を追加できます。

### ファイル、フォルダを開く

VSCodeでプログラムを編集するには必ずファイルまたはフォルダを開く必要があります。ここではその方法を紹介します。

* 「ファイル」アプリで編集したいファイルまたはフォルダを右クリックし、「Codeで開く」というオプションを選択する
* VSCodeを開く > 画面左上の「ファイル」メニュー > 「ファイルを開く」または「フォルダーを開く」
* キーボードショートカットも割り当てられています。「ファイルを開く」はCtrl+O、「フォルダーを開く」はCtrl+Kを押してからCtrl+Oです。

ちなみに、ファイルとはソースコードを記述するもの、フォルダはファイルまたはフォルダを集めたものです。

### 設定を変更する

画面左下にある歯車マークのボタン > 「設定」
Arduino、Processingどちらのセットアップを行う場合もVSCodeの設定をいじります。設定の変更方法は覚えておいてください。

### 検索、置換

開いているファイルに対して検索、置換を行う場合、画面上部の「編集メニュー」 > 検索/置換 と進むか、Ctrl+Fで検索、Ctrl+Hで置換ができます。

開いているフォルダが含むファイル全てに対して検索、置換を行う場合、画面左側の検索マーク > 検索/置換 と進むか、Ctrl+Shift+Fで検索、Ctrl+Shift+Hで置換です。

検索には様々なオプションがあり、正規表現というものを使うことができます。興味があったら調べてみて下さい。

### ターミナル

Ctrl+@ またはCtrl+Shift+@ でターミナル(シェル)が開きます。シェルを通して、CUIで様々な操作ができます。使う機能がProcessing、Arduinoのみであれば、ログの出力はここにされますが、何かを入力して操作を行うといったことは多分ないです。ここでは存在の紹介のみとします。

### 拡張機能

VSCodeはインストールした初期段階では様々なプログラミング言語(C言語、Python等)はサポートしていません。日本語もサポートされていません。それらのサポートを追加するのに使うのが拡張機能です。

例として日本語の拡張機能のインストール方法を紹介します。
※ここではオンラインでのインストールのみ紹介します。オフラインでのインストール方法が知りたい方はググってください。

画面左側にある「田」のようなボタンを押して、拡張機能の管理メニューを表示します。
メニューの上にある検索バーに、「japanese」と打ってください。検索にヒットした拡張機能のリストが表示されます。その中から「Japanese Language Pack for VSCode」という名前のものをクリックしてください。地球儀のマークのものが表示されたと思います。「インストール」とある緑のボタンを押してインストールします。インストールが終わると、右下に再起動を促すメッセージが表示されます。クリックして再起動します。再起動後、表示が日本語になっていれば成功です。

プログラミング言語を導入する場合は、VSCodeでの拡張機能のインストールに加えて、その言語専用のコンパイラ等を別にインストールする必要があります。言語ごとに別途ググってください。

現在Surface(2020/09/14)に入っている拡張機能のリストです。

* Arduino
* C/C++
* Debugger for Java
* Japanese Language Pack for VSCode
* Java Extension Pack
* Java Test Runner
* Language Support for Java
* Maven for Java
* Processing Language
* Project Manager for Java
* Python
* Visual Studio IntelliCode

また、SurfaceにはJava(`java`コマンド)、C/C++(`gcc`/`g++`コマンド)のコンパイラがインストールされているため、これらの言語の開発も可能です。Pythonは少し事情が違いますが、実行プログラムはインストールされている(`python`コマンド等)ため、問題なく動かせます。

### コマンドパレット

コマンドパレットとは、拡張機能が提供するアクションを使う方法です。Ctrl+Shift+P、または 画面上部の「表示」メニュー > 「コマンドパレット」 でコマンドパレットを開くことができます。Arduino, Processingどちらを使用する場合にも登場するので覚えておいてください。

## マークダウンとは

参考:
https://qiita.com/Qiita/items/c686397e4a0f4f11683d

この文書はマークダウンで書かれています。マークダウンとは、HTMLを簡易的に書く目的で作られた書式です。ファイル拡張子は`.md`です。プログラムの内容を説明する際などによく使われます。ここでは見出し、強調、箇条書き、リンク、インラインコード、ブロックコードの文法を紹介します。上のサイトを見た方が分かりやすいかもしれません。

### 見出し

`#`はHTMLの`<h1>`タグ、`##`はHTMLの`<h2>`タグ、...といった対応関係があります。`<h6>`までです。
ざっくり言うと、`#`はタイトル、`##`は見出し、`###`は小見出し、...といった感じです。

### 強調

`*`または`_`で囲むことで強調、斜体(イタリック)にできます。1つで囲むと *斜体* 、2つで囲むと **強調** 、3つで囲むと ***強調と斜体*** となります。

### 箇条書き

行頭に`*`、`-`、`+`のいずれかがある場合は箇条書きとなります。これらの記号の代わりに`数字.`を使うこともでき、その場合は1. 2. 3. ...といった番号が振られます。

### リンク

`[リンクテキスト](URL)`

### インラインコード

バッククオート(`` ` ``)1つで囲むとコードとなります。

### ブロックコード

バッククオート3つ(```` ``` ````)で囲むと複数行に渡ってコードを記述できます。

### 引用

文頭に`> `を置くことで引用になります。改行のたびにこの記号を置く必要があります。

## JSONについて

[wikipedia](https://ja.wikipedia.org/wiki/JavaScript_Object_Notation)より引用

> 
> JavaScript Object Notation（JSON、ジェイソン）はデータ記述言語の1つである。軽量なテキストベースのデータ交換用フォーマットでありプログラミング言語を問わず利用できる。名称と構文はJavaScriptにおけるオブジェクトの表記法に由来する。
> 

参考:
https://www.json.org/json-ja.html

VSCodeの各種設定はこのJSONというファイル形式に保存されます。ファイル拡張子は`.json`です。Processing, Arduinoの導入にはどちらもこのJSONをいじる必要があります。(具体的な導入方法は`~/kawamoto/Arduino/README.md`、`~/kawamoto/Processing/README.md`にまとめました。)
何をどういじって導入するかはコピペでもできるようにしてあるはずですが、読めて損はないので書式をまとめておきます。

JSONは1つのファイルに1つのオブジェクトとして表現されます。
オブジェクト(連想配列、辞書)はキー(key)と値(value)のセットで表されます。`{波括弧}`で囲み、`,`で区切って表現します。
リスト(配列)はvalueのリストで表されます。`[角括弧]`で囲み、`,`で区切って表現します。
keyは`"文字列"`、valueは`"文字列"`、数値(`2, 3.14, -256`など)、真偽値(`true`、`false`)、値がないことを示す`null`、オブジェクト、リストのいずれかである必要があります。
オブジェクトがリストを含み、そのリストの中にオブジェクトがあり、そのオブジェクトが... といったように、同じ構造の繰り返しで複雑なものを表現します。
これはJSONの記述例です:

```JSON
{
    "key1": "value1",
    "key2": 256,
    "key3": true,
    "key4": null,
    "root-folder": {
        "name": "kawamoto",
        "files": [
            "README.md",
            "README.pdf"
        ],
        "folders": [
            {
                "name": "Arduino",
                "files": [
                    "README.md"
                ],
                "folders": [
                    ".vscode",
                    "sketch"
                ]
            },
            {
                "name": "Processing",
                "files": [
                    "README.md"
                ],
                "folders": [
                    "sample",
                    "sample1",
                    "sample2",
                    "sample3",
                    "sample4"
                ]
            }
        ]
    }
}
```

例としてこのフォルダ以下の構造を(一部ですが)示しました。この程度が読めれば、VSCodeで作業する分には差し支えないと思います。

## 終わりに

VSCodeはとても便利なコードエディタです。世界標準と言っても過言ではない程度の人気があります。積極的に活用しましょう。

何か分からないことがあったら、まずはググってください。プログラミング関連のことは意外と何でもネットにあります。
VSCodeでArduino、Processing等を動かす方法については別のところに書きます。各言語名のフォルダにある`README.md`をそれぞれ読んでください。

この記事は自由に編集しても構いませんが、誰もが理解できるような内容を心掛けてください。
