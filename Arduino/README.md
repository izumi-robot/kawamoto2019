<!-- Ctrl + Shift + V -->

<!-- omit in toc -->
# Arduino

このREADMEに書いてあるのは以下の2つです。

- VSCodeとの連携方法
- ArduinoIDEの設定をいい感じにする
- Arduinoでライブラリを自作する方法

<!-- omit in toc -->
## 目次

- [VSCodeとの連携](#vscodeとの連携)
  - [拡張機能のインストール](#拡張機能のインストール)
  - [VSCodeの設定変更](#vscodeの設定変更)
  - [スケッチの準備](#スケッチの準備)
  - [基本的な使い方](#基本的な使い方)
- [ArduinoIDEの設定をいい感じにする](#arduinoideの設定をいい感じにする)
- [ライブラリを自作する](#ライブラリを自作する)
  - [基本構造](#基本構造)
  - [Arduinoに認識させる](#arduinoに認識させる)
- [終わりに](#終わりに)

最初の2つは初期設定についてです。自分のパソコンに入れるのでなければ読み飛ばしてください。

## VSCodeとの連携

この節では主に、VSCodeでのArduinoの連携方法について紹介します。セットアップ的な部分は、Surfaceではすでに行ってあります。自分のパソコンに入れようと思っているのでなければ、飛ばしてください。セットアップの紹介後、VSCodeでコードを機体に読み込ませる方法などを紹介します。

参考:

1. https://garretlab.web.fc2.com/arduino/introduction/vscode/
2. https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino
3. https://github.com/bfxdev/Arduino/blob/master/VSCode/README.md
4. https://github.com/microsoft/vscode-arduino
5. https://github.com/microsoft/vscode-arduino/issues/808

1番上に全部書いてあります。それ以外は公式によるドキュメントです。英語なのでオススメはしません。

前提として、ArduinoIDEとVSCodeが入っている必要があります。パス名やキーボードショートカットなど、OSによって異なる部分はWindowsのものを記述します。他のOSの方は適宜読み替えるか、調べるかしてください。VSCodeの操作で分からないことは`~\kawamoto\README.md`を見てください。

### 拡張機能のインストール

https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino

Arduinoという名前の拡張機能です。アイコンにもArduinoとあります。インストールすると、C/C++という拡張機能も自動でインストールされます。これをインストールすることで、VSCodeからArduino関連の操作を手軽に行えるようになります。

※[ワークスペースとは](https://www.javadrive.jp/vscode/file/index4.html)

### VSCodeの設定変更

まずはVSCodeにArduinoのパスを通します。VSCodeの設定にある、「Arduino: Path」を編集します。
ArduinoIDEのプログラムがあるフォルダーのパスを設定します。Windowsだと(多分)`C:\Program Files (x86)\Arduino`です。

次に、文字化けを予防します。この内容は、Windowsを使っている方のみになります。`C:\Users\<username>\.vscode\extensions\vsciot-vscode.vscode-arduino-<version>\out\src\common\util.js`(`<>`内の部分は自身の環境に合わせて読み替えてください)を編集します。

215行目あたりにある次の部分をコメントアウトします。

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

コメントアウトができたら`Ctrl + S`で保存して、VSCodeを再起動してください。

### スケッチの準備

それでは、実際のスケッチを開いて設定します。以降はVSCodeでスケッチのフォルダーを開いて作業します。このフォルダーをメインフォルダーと呼ぶことにします。

1. `Ctrl + Shift + P`でコマンドパレットを開く
2. `Arduino: Initialize`を選択
3. `.ino`のプログラムがメインフォルダー内にない場合は新しく`.ino`ファイルを作成
   1. ファイル名が聞かれるので、適当な名前を設定(ArduinoIDEに合わせるために、フォルダー名と同じ名前にしておくことがオススメ)
4. 使用する`.ino`ファイルの候補がいくつかあった場合、どれを使用するか選択
5. ボードタイプ(Arduino Uno, Arduino Megaなど)を選択

ここまででメインフォルダー内は以下のようになっているはずです。

```
sketch
 |- .vscode
 |   |- arduino.json
 |   |- c_cpp_properties.json
 |- sketch.ino
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

編集したら`Ctrl + S`で保存してください。

次に、コード補完の設定を少し改造します。`.vscode/c_cpp_properties.json`を開いて、次のように編集します。

* 5行目にある`"name": "Arduino"`の部分を`"name": "Arduino Specified"`に変更
* 17行目にある`"includePath"`のリストを以下のように変更<br>※`-`の行を削除、`+`の行を追加

```diff
            "includePath": [
                "C:\\Program Files (x86)\\Arduino\\hardware\\arduino\\avr\\cores\\arduino",
                "C:\\Program Files (x86)\\Arduino\\hardware\\arduino\\avr\\variants\\mega",
                "c:\\program files (x86)\\arduino\\hardware\\tools\\avr\\lib\\gcc\\avr\\7.3.0\\include",
                "c:\\program files (x86)\\arduino\\hardware\\tools\\avr\\lib\\gcc\\avr\\7.3.0\\include-fixed",
-                "c:\\program files (x86)\\arduino\\hardware\\tools\\avr\\avr\\include"
+                "c:\\program files (x86)\\arduino\\hardware\\tools\\avr\\avr\\include",
+                "C:\\Program Files (x86)\\Arduino\\hardware\\arduino\\avr\\libraries\\**",
+                "${USERPROFILE}\\Documents\\Arduino\\libraries\\**"
            ],
```

* 29行目にある`"defines"`のリストの先頭に`"USBCON",`を追加<br>※ `,`で区切るのを忘れないこと

これで準備完了です。VSCodeでバリバリ開発しちゃってください。

### 基本的な使い方

コマンドパレットからアクションを行う方法を紹介します。(基本的には https://github.com/microsoft/vscode-arduino の和訳です)

アクション名 | 機能
:- | :-
`Arduino: Board Manager` | ボード用のパッケージを管理します。サードパーティ製のパッケージを追加できるらしいです。
`Arduino: Change Baud Rate` | シリアル通信の速度を変更します。初期値は9600です。
`Arduino: Change Board Type` | ボードタイプ、プラットフォームを変更します。
`Arduino: Close Serial Monitor` | シリアルモニターを閉じます。
`Arduino: Examples` | スケッチの例を表示します。
`Arduino: Initialize` | スケッチの雛形を作ります。
`Arduino: Library Manager` | ライブラリを探索、管理します。
`Arduino: Open Serial Monitor` | シリアルモニターを開きます。
`Arduino: Select Serial Port` | 接続するシリアルポートを変更します。
`Arduino: Send Text to Serial Port` | 現在のシリアルポートから1行のテキストを送信します。
`Arduino: Upload` | スケッチをコンパイルし、Arduinoにアップロードします。
`Arduino: Upload Using Programmer` | 外部のプログラマを使用してアップロードします。
`Arduino: Verify` | スケッチをコンパイルします。文法エラーなどがないか確認できます。
`Arduino: Rebuild IntelliSense Configuration` | IntelliSenseを再設定します。
`Arduino: CLI Upload` | Arduino-CLI限定です。現在のスケッチをコンパイルせずに、コンパイル済みのコードをアップロードします。
`Arduino: CLI Upload Using Programmer` | Arduino-CLI限定です。現在のスケッチをコンパイルせずに、コンパイル済みのコードを外部プログラマを使用してアップロードします。

よく使うものは`Arduino: Board Config`、`Arduino: Select Serial Port`、`Arduino: Upload`です。
キーボードショートカットは次のものがあります。

コマンド名                                     | ショートカットキー
:-                                            | -:
`Arduino: Upload`                             | `Ctrl + Alt + U`
`Arduino: Verify`                             | `Ctrl + Alt + R`
`Arduino: Rebulid IntelliSense Configuration` | `Ctrl + Alt + I`

画面下部のステータスバーには次のショートカットが割り当てられています。

コマンド名 | 場所
:- | :-
`Arduino: Board Config` | Arduinoのボード名が書いてあるボタン (ボードタイプが選択されていない場合は`<Select Board Type>`)
`Arduino: Select Serial Port` | シリアルポートの名前が書いてあるボタン (シリアルポートが選択されていない場合は`<Select Serial Port>`)
`Arduino: Open Serial Monitor` | 電源プラグのボタン (シリアルポートが閉じている場合のみ)
`Arduino: Close Serial Monitor` | ×印のボタン (シリアルポートが開いている場合のみ)

`.ino`ファイルを編集中、`Arduino: Verify`と`Arduino: Upload`のボタンが画面右上に表示されます。

## ArduinoIDEの設定をいい感じにする

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

## ライブラリを自作する

`robo2019`はArduinoで私が自作したライブラリです。おそらくライブラリを自作する強者が後輩にも出てくると思うので、必要最低限にとどめて作り方をまとめておきます。

参考:

- https://arduino.github.io/arduino-cli/latest/library-specification/
- https://stupiddog.jp/note/archives/266

以下、`LEDctrl`という名前のライブラリを作るものとして解説します。このライブラリはLEDのオンオフを管理するためのものです。実際のライブラリフォルダーを作ってあるので、具体的な内容はそちらを参照。

### 基本構造

```
LEDctrl
 |- src
 |   |- LED.h
 |   |- LED.cpp
 |- examples
 |   |- blink
 |   |   |- blink.ino
 |- keywords.txt
 |- library.properties
 |- README.md
```

各フォルダーとファイルの内容について、1つずつ解説していきます。

**`src`**

ライブラリのソースコードを置いておくフォルダーです。`LEDctrl`では`LED.h`と`LED.cpp`があります。拡張子は`.ino`ではなく`.h`と`.cpp`を使ってください。`.h`ファイルにDoxygen準拠でコメントを入れることをオススメします。

- [ヘッダとソースでファイルを分ける](https://qiita.com/agate-pris/items/1b29726935f0b6e75768)
- [Doxygenの書き方](https://qiita.com/wakaba130/items/faa6671bd5c954cb2d02)

**`examples`**

ライブラリの使用例を置いておくフォルダーです。`LEDctrl`では`blink`(Lチカの例)があります。Arduinoのスケッチ形式に沿ったものにしてください。

- [Arduinoのスケッチ構成について](https://www.indoorcorgielec.com/resources/arduinoide%E8%A8%AD%E5%AE%9A/arduino-ide%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E3%81%AE%E5%9F%BA%E7%A4%8E%E3%81%A8%E3%82%B7%E3%83%AA%E3%82%A2%E3%83%AB%E3%83%A2%E3%83%8B%E3%82%BF%E3%83%BC/)

**`library.properties`**

ライブラリの情報を記述するファイルです。形式は`key=value`です。以下、最低限記述できるkeyのリストです。「よくわかってない」のところは書かなくても大丈夫です。詳しくは[Library Specification - Arduino CLI](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format)を参照。

key | value
:- | :-
`name` | ライブラリの名前。名前のルールとして、プログラミングでの変数名で使えるルールに加え、1文字目以外はスペース、ハイフン(`-`)、ドット(`.`)が使える。
`version` | ライブラリのバージョン。`a.b.c`の形式。[semver](http://semver.org/)準拠。ロボ部内での使用にとどめるのであれば、`1.0.0`で固定すればいい。
`author` | 作者の名前。
`maintainer` | ライブラリを管理している人の名前。
`sentence` | ライブラリの簡単な説明。
`paragraph` | `sentence`よりも長い説明。
`category` | ライブラリのカテゴリ。使える値は`Display`, `Communication`, `Signal Input/Output`, `Sensors`, `Device Control`, `Timing`, `Data Storage`, `Data Processing`, `Other`の9個。<br>書かなかった場合は`Uncategorized`になる。
`url` | ソースコードが置いてあるURL。オフラインで管理しているのであれば`https://example.com`でOK。
`architectures` | ライブラリがサポートしているボードのリスト。「`,`」区切り。書かなかった場合は`*`で、すべてのボードをサポートしているとなる。
`includes` | `src`に複数のヘッダファイルがあり、ArduinoIDEの「ライブラリをインクルード」アクションで特定のヘッダファイルのみをインクルードさせたいときに書く。`,`区切り。書かなかった場合は全ての`.h`ファイルがインクルードされる。
`dot_a_linkage` | よくわかってない
`precompiled` | よくわかってない
`Idflags` | よくわかってない

**`keywords.txt`**

ArduinoIDEでハイライト表示させたいキーワードを記述するファイルです。
ハッシュ`#`で始まる行はコメントになります。`keyword[tab]value`の形式で記述します。`[tab]`はタブ文字です。`value`として使えるもののリストは以下になります。

- `KEYWORD1`
- `KEYWORD2`
- `KEYWORD3`
- `LITERAL1`
- `LITERAL2`
- `RESERVED_WORD`
- `RESERVED_WORD2`
- `DATA_TYPE`
- `PREPROCESSOR`

ハイライトは`LITERAL1`が緑色で、その他は橙色らしいです。VSCodeで使うんだったら正直どうでもいいですね。クラス名を`KEYWORD1`にする程度でいいと思います。

**`README.md`**

ライブラリに関する説明を記述するファイルです。形式はMarkdownです。`LEDctrl`には書くことがあまりなかったので、`robo2019`を参考にしてください。

- [Markdownの書き方](https://qiita.com/Qiita/items/c686397e4a0f4f11683d)

### Arduinoに認識させる

作ったライブラリは決められた場所に置かないと使えるようになりません。ライブラリフォルダーを置く場所は以下の通りです。

OS | 場所
:- | -:
Windows | `C:\Users\<username>\Documents\Arduino\libraries\`
Mac | `/Users/<username>/Documents/Arduino/libraries/`
Linux | `/home/<username>/sketchbook/libraries/`

これで準備完了です。作ったライブラリは任意のスケッチで`include`して使うことができます。

## 終わりに

VSCodeでのArduinoの使い方の紹介は以上です。これ読んで分からなかったところは調べてください。
Arduinoの入門で参考になったサイトのリンクを載せておきます。

https://deviceplus.jp/hobby/arduino-listicle-01/
