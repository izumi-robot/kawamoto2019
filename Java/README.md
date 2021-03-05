# Java

## 目次

* Installation
* Usage

## 前置き

例として取り上げるJavaのバージョンは`14.0.2`であるものとします。ここでは本当に基礎的な部分しか紹介しません。

## Installation

Javaのインストール方法です。この節では、パソコンでJavaを使う方法を紹介します。VSCodeで使う方法は別に書きます。

1. https://www.oracle.com/jp/java/ を開く
2. 画面右上の「Javaダウンロード」ボタンを押す
3. 画面真ん中の「JDK Download」を押す
4. パソコンのOSに合った項目を押す
    * Windows - `Windows x64 Installer`
    * Mac - `macOS Installer`
5. ファイルがダウンロードされる。ダウンロードしたものを開く
6. インストーラが開く。画面の指示に従って進み、インストールする。
* Windows版の作業
    1. 設定を開き、検索バーで「path」と調べる
    2. 検索結果から「システム環境変数の編集」を選ぶ(なかったらそれっぽいやつ)。管理者権限が求められた場合は通す。
    3. ウィンドウ右下の「環境変数」ボタンを押す
    4. 「システム環境変数」のリストから変数名が`Path`のものをクリックし、右下にある「編集」を押す
    5. 「新規」を押し、`C:\Program Files\Java\jdk-14.0.2\bin`を追加する
    6. 念のため再起動しておく
7. ちゃんと入ったか確認する
    1. シェルを開く(WindowsはcmdかPowerShell、Macは「ターミナル」)
    2. `java -version`を入力、エンター
    3. 次のような結果が出たら成功(PowerShellでの実行例)

```
PS C:\Users\robo> java -version
java version "14.0.2" 2020-07-14
Java(TM) SE Runtime Environment (build 14.0.2+12-46)
Java HotSpot(TM) 64-Bit Server VM (build 14.0.2+12-46, mixed mode, sharing)
```

## Usage

上の節での作業を全て終えたものとして、シェルでの使用例を紹介します。

* `java <filename>.java` - `<filename>.java`をコンパイル(機械語に翻訳)せずに実行します。
* `javac <filename>.java` - `<filename>.java`をコンパイルします。アウトプットは`<filename>.class`です。コンパイル後の実行方法は`java <filename>`です。

次はPowerShellでの使用例です。

```PowerShell
PS C:\path\to\directory> ls

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        2020/09/13     21:05            126 helloworld.java

PS C:\path\to\directory> cat helloworld.java
public class helloworld {
    public static void main(String[] argv) {
        System.out.println("Hello world!");
    }
}
PS C:\path\to\directory> java helloworld.java
Hello world!
PS C:\path\to\directory> javac helloworld.java
PS C:\path\to\directory> ls

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        2020/10/29     17:11            426 helloworld.class
-a----        2020/09/13     21:05            126 helloworld.java

PS C:\path\to\directory> java helloworld
Hello world!
PS C:\path\to\directory>
```

https://qiita.com/pitan109/items/ba62ac1973f727ba719f
こっちのほうが詳しく書いてあります。

## use in VS Code

VS Code内でのJavaの使用方法です。

まずは拡張機能「Java Extension Pack」をインストールします。名前の通り複数の拡張機能をまとめたものなので、少し時間がかかります。

インストールしたら`Ctrl + ,`で設定を開き、`java.home`をインストールしたJDKがある場所に設定します。`C:\Program Foles(x86)\Java\openjdk-14.0.2\bin\`といった具合です。jdk内の`bin`フォルダーまで指定してください。

これで準備完了です。以降は使い方を説明します。

**プロジェクトを作る**

1. コマンドパレットを開く(`Ctrl + Shift + P`)
2. `Java: Create Java Project`を選択
3. プロジェクトを作るフォルダーを設定

これでプロジェクトが作成できます。プロジェクト内のファイル構造は以下のとおりです。

```
ProjectFolder/
    |- src/
    |- app/
    |   |- App.java
    |- README.md
```

**実行する**

`main`関数は`App.java`内にあります。`Run | Build`のオプションが`main`関数の上に表示されているはずです。

**余談**

実は、こんなに面倒なことをしなくても良かったりします。`main`関数の上には必ず`Run | Build`が表示されます。また、`.java`ファイルを作ると自動でそのファイル名と同じ名前のクラスができます。

## 参考


