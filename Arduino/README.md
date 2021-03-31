# Arduino

この文書では主に、VS CodeでのArduinoの連携方法について紹介します。セットアップ的な部分は、Surfaceではすでに行ってあります。自分のパソコンに入れようと思っているのでなければ、飛ばしてください。セットアップの紹介後、VS Codeでコードを機体に読み込ませる方法などを紹介します。

参考:

* https://qiita.com/narikei/items/847613a8f01a9e1527d7
* https://qiita.com/mmt/items/7dd1a2f312334a6cd600
* https://qiita.com/nori-dev-akg/items/e0811eb26274910cdd0e
* https://another.maple4ever.net/archives/2328/
* https://garretlab.web.fc2.com/arduino/introduction/vscode/
* https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino
* https://github.com/bfxdev/Arduino/blob/master/VSCode/README.md
* https://github.com/microsoft/vscode-arduino

詳しいことはこちらを見てください。下の2つは公式によるドキュメントです。英語なのでオススメはしません。

前提として、ArduinoIDEとVS Codeが入っている必要があります。パス名やキーボードショートカットなど、OSによって異なる部分はWindowsのものを記述します。他のOSの方は適宜読み替えるか、調べるかしてください。VS Codeの操作で分からないことは`~\kawamoto\README.md`を見てください。

## 目次 {ignore=true}

<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [拡張機能のインストール](#拡張機能のインストール)
- [VS Codeの設定変更](#vs-codeの設定変更)
- [スケッチの準備](#スケッチの準備)
- [基本的な使い方](#基本的な使い方)
- [終わりに](#終わりに)
- [追記](#追記)

<!-- /code_chunk_output -->


最初の2つは初期設定についてです。自分のパソコンに入れるのでなければ読み飛ばしてください。

## 拡張機能のインストール

Arduinoという名前の拡張機能です。アイコンにもArduinoとあります。インストールすると、C/C++という拡張機能も自動でインストールされます。これをインストールすることで、VS CodeからArduino関連の操作を手軽に行えるようになります。

## VS Codeの設定変更

まずはVS CodeにArduinoのパスを通します。VS Codeの設定にある、「Arduino: Path」を編集します。
ArduinoIDEのプログラムがあるフォルダーのパスを設定します。Windowsだと(多分)`C:\Program Files (x86)\Arduino`です。

次に、文字化けを予防します。この内容は、Windowsを使っている方のみになります。`C:\Users\<username>\.vscode\extensions\vsciot-vscode.vscode-arduino-<version>\out\src\common\util.js`(`<>`内の部分は自身の環境に合わせて読み替えてください)を編集します。

215行目あたりにある次の部分をコメントアウトします:

```javascript
        if (os.platform() === "win32") {
            try {
                const chcp = childProcess.execSync("chcp.com");
                codepage = chcp.toString().split(":").pop().trim();
            }
            catch (error) {
                outputChannel_1.arduinoChannel.warning(`Defaulting to code page 850 because chcp.com failed.\
                \rEnsure your path includes %SystemRoot%\\system32\r${error.message}`);
                codepage = "850";
            }
        }
```

この部分を以下のように、`/*`と`*/`で囲んでください。ちなみに、今編集しているのはJavaScriptという言語ですが、このコメントアウト方法はC/C++(Arduino)、Java(Processing)でも使えます。

```javascript
/*
        if (os.platform() === "win32") {
            try {
                const chcp = childProcess.execSync("chcp.com");
                codepage = chcp.toString().split(":").pop().trim();
            }
            catch (error) {
                outputChannel_1.arduinoChannel.warning(`Defaulting to code page 850 because chcp.com failed.\
                \rEnsure your path includes %SystemRoot%\\system32\r${error.message}`);
                codepage = "850";
            }
        }
*/
```

コメントアウトができたらCtrl + Sで保存して、VS Codeを再起動してください。

## スケッチの準備

それでは、実際のスケッチを開いて設定します。以降はVS Codeでスケッチのフォルダーを開いて作業します。このフォルダーをメインフォルダーと呼ぶことにします。

Ctrl + Shift + Pでコマンドパレットを開き、`Arduino: Initialize`を選択します。`.ino`のプログラムがメインフォルダー内にない場合、新しく`.ino`ファイルを作成します。ファイル名が聞かれるので、好きな名前に変更します。ArduinoIDEに合わせるために、フォルダー名と同じ名前にしておくことをオススメします。また、使用する`.ino`ファイルの候補がいくつかあった場合、どれを使用するか聞かるので、適するものを選んでください。その次に、ボードタイプ(Arduino Uno, Arduino Megaなど)を聞かれます。使うものを選んでください。

ここまででメインフォルダー内は以下のようになっているはずです。

```
main-folder
 |- .vscode
 |   |- arduino.json
 |   |- c_cpp_properties.json
 |- main.ino
```

次に、コンパイルを高速化するためにアウトプット用のパスを設定します。`.vscode/arduino.json`を開き、末尾に`"output": "./build"`、その1行前の最後に`,`を追加します。例えば、ボードタイプにArduino Megaを選択した場合、このようになります。

```diff
{
    "sketch": "main.ino",
    "configuration": "cpu=atmega2560",
-    "board": "arduino:avr:mega"
+    "board": "arduino:avr:mega",
+    "output": "./build"
}
```

編集したらCtrl+Sで保存してください。

次に、IntelliSenseを少し改造します。`.vscode/c_cpp_properties.json`を開いてください。次のように編集します。

* 5行目にある`"name": "Arduino"`の部分を`"name": "Arduino Specified"`に変更
* 29行目にある`"defines"`のリストの先頭に`"USBCON",`を追加<br>※ `,`で区切ることを忘れないこと

これで準備完了です。VS Codeでバリバリ開発しちゃってください。

## 基本的な使い方

コマンドパレットからアクションを行う方法を紹介します。(基本的には https://github.com/microsoft/vscode-arduino の和訳です)

* `Arduino: Board Manager`<br>ボード用のパッケージを管理します。サードパーティ製のパッケージを追加できるらしいです。
* `Arduino: Change Baud Rate`<br>シリアル通信の速度を変更します。初期値は9600です。
* `Arduino: Change Board Type`<br>ボードタイプ、プラットフォームを変更します。
* `Arduino: Close Serial Monitor`<br>シリアルモニターを閉じます。
* `Arduino: Examples`<br>スケッチの例を表示します。
* `Arduino: Initialize`<br>スケッチの雛形を作ります。
* `Arduino: Library Manager`<br>ライブラリを探索、管理します。
* `Arduino: Open Serial Monitor`<br>シリアルモニターを開きます。
* `Arduino: Select Serial Port`<br>接続するシリアルポートを変更します。
* `Arduino: Send Text to Serial Port`<br>現在のシリアルポートから1行のテキストを送信します。
* `Arduino: Upload`<br>スケッチをコンパイルし、Arduinoにアップロードします。
* `Arduino: Upload Using Programmer`<br>外部のプログラマを使用してアップロードします。
* `Arduino: Verify`<br>スケッチをコンパイルします。文法エラーなどがないか確認できます。
* `Arduino: Rebuild IntelliSense Configuration`<br>強制的/定型的にIntelliSenseを再設定します。Arduinoのビルドアウトプットを見て、それに従ってIntelliSenseの`#include`パス、`#define`、コンパイラの引数を設定します。
* `Arduino: CLI Upload`<br>Arduino-CLI限定です。現在のスケッチをコンパイルせずに、コンパイル済みのコードをアップロードします。
* `Arduino: CLI Upload Using Programmer`<br>Arduino-CLI限定です。現在のスケッチをコンパイルせずに、コンパイル済みのコードを外部プログラマを使用してアップロードします。

よく使うものは`Arduino: Board Config`、`Arduino: Select Serial Port`、`Arduino: Upload`です。
キーボードショートカットは次のものがあります。

* `Arduino: Upload` - Ctrl + Alt + U
* `Arduino: Verify` - Ctrl + Alt + R
* `Arduino: Rebuild IntelliSense Configuration` - Ctrl + Alt + I

画面下部のステータスバーには次のショートカットが割り当てられています。

* `Arduino: Board Config`<br>Arduinoのボード名が書いてあるボタン(ボードタイプが選択されていない場合は`<Select Board Type>`)
* `Arduino: Select Serial Port`<br>シリアルポートの名前が書いてあるボタン(シリアルポートが選択されていない場合は`<Select Serial Port>`)
* `Arduino: Open Serial Monitor`<br>電源プラグのボタン(シリアルポートが閉じている場合のみ)
* `Arduino: Close Serial Monitor`<br>×印のボタン(シリアルポートが開いている場合のみ)

`.ino`ファイルを編集中、`Arduino: Verify`と`Arduino: Upload`のボタンが画面右上に表示されます。

## 終わりに

VS CodeでのArduinoの使い方の紹介は以上です。これ読んで分からなかったところは調べてください。
Arduinoの入門で参考になったサイトのリンクを載せておきます。

https://deviceplus.jp/hobby/arduino-listicle-01/

## 追記

**ArduinoIDEの設定をいい感じにする** (2020/11/12追記)

IDEの「環境設定」でもある程度はいじれるのですが、もっと細かい設定は別の場所においてあります。OSごとのそのファイルの場所は次の通りです。
※Windowsは実機で確認しましたが、Mac、Linuxはインターネットの情報が元なので少し異なるかもしれません。

* Windows - `C:\Users\<username>\AppData\Roaming\Arduino\preferences.txt`
* Mac - `/Users/<username>/Library/Arduino15/preferences.txt`
* Linux - `~/.arduino15/preferences.txt`

このファイルは壊すとArduinoIDEが動かなくなるので、コピーを作り、原本を編集してIDEが動かなくなったら元に戻すという形を取りましょう。
このファイルの記述形式は`<key>=<value>`です。例として、`editor.advanced`を`true`に設定してください(すでに設定されている項目がないか探して、なければ適当な所に新しい行を追加して書いてください)。IDEのエディターが少し便利になります。他にも便利な設定がいくつかあります。気になったら下のリンクを参考にしてください。

* https://jumbleat.comk/2018/08/25/customize_ide_preferences_file/
* https://garretlab.web.fc2.com/arduino/introduction/preferences/index.html
* https://www.arduino.cc/en/hacking/preferences
* https://github.com/arduino/Arduino/blob/master/build/shared/lib/preferences.txt
