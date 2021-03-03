# Arduino

この文書では主に、VS CodeでのArduinoの連携方法について紹介します。セットアップ的な部分は、Surfaceではすでに行ってあります。自分のパソコンに入れようと思っているのでなければ、飛ばしてください。セットアップの紹介後、VS Codeでコードを機体に読み込ませる方法などを紹介します。

参考:

* https://qiita.com/narikei/items/847613a8f01a9e1527d7
* https://qiita.com/mmt/items/7dd1a2f312334a6cd600
* https://qiita.com/nori-dev-akg/items/e0811eb26274910cdd0e
* https://another.maple4ever.net/archives/2328/

* https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino
* https://github.com/bfxdev/Arduino/blob/master/VSCode/README.md

詳しいことはこちらを見てください。下の2つは公式によるドキュメントです。英語なのでオススメはしません。

前提として、ArduinoIDEとVS Codeが入っている必要があります。パス名やキーボードショートカットなど、OSによって異なる部分はWindowsのものを記述します。他のOSの方は適宜読み替えるか、調べるかしてください。VS Codeの操作で分からないことは`~\kawamoto\README.md`を見てください。

## 目次

* 拡張機能のインストール
* VS Codeの設定変更
* プロジェクトの準備
* 基本的な使い方
* 終わりに

最初の2つは初期設定についてです。自分のパソコンに入れるのでなければ読み飛ばしてください。

## 拡張機能のインストール

Arduinoという名前の拡張機能です。アイコンにもArduinoとあります。インストールすると、C/C++という拡張機能も自動でインストールされます。これをインストールすることで、VS CodeからArduino関連の操作を手軽に行えるようになります。

## VS Codeの設定変更

まずはVS CodeにArduinoのパスを通します。VS Codeの設定にある、「Arduino: Path」を編集します。
ArduinoIDEのプログラムがあるフォルダーのパスを設定します。Windowsだと(多分)`C:\Program Files (x86)\Arduino`です。

次に、文字化けを予防します。この内容は、Windowsを使っている方のみになります。`C:\Users\<username>\.vscode\extensions\vsciot-vscode.vscode-arduino-<version>\out\src\common\util.js`(`<>`で囲まれた部分は自身の環境に合わせて読み替えてください)を編集します。慣れるためにも、VS Codeで開いて編集することをオススメします。

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

コメントアウトができたら保存して、VS Codeを再起動してください。

## プロジェクトの準備

それでは、実際のプロジェクトを開いて設定します。以降はVS Codeでプロジェクトのフォルダー(以降はメインフォルダーと呼びます)を開いて作業します。

まずはVS Codeの設定にある「C_Cpp: Intelli Sense Engine」を編集します。
※「C_Cpp: Intelli Sense Engine Fallback」ではないです。
**ワークスペースの設定を**「Default」から「Tag Parser」に変換します。ユーザーの設定を変更すると、**ほかのプログラムに影響が出る**からです。「Default」だと本来は存在しないエラーが出ます。「Tag Parser」にすることでそれを回避しています。

次に機体のボードタイプを選択します。コマンドパレットでArduinoと検索し、結果の中から「Arduino: Board Config」を選択し、ボードタイプを選択します。

ここまでの作業でメインフォルダー内に`.vscode`というフォルダーが追加され、その中に`settings.json`、`arduino.json`、`c_cpp_properties.json`の3つのJSONファイル(JSONについては`kawamoto\README.md`を読んでください)が追加されたと思います。各ファイルの役割は、次のようになっています。

* `settings.json` - そのフォルダー内限定の設定情報
* `arduino.json` - Arduinoの設定情報
* `c_cpp_properties.json` - C/C++パーサーの設定情報

となっています。Arduinoの`#include`関係のパスを通すために、`c_cpp_properties.json`を次のように変更します:

```JSON
{
    "env": {
        "PACKAGES_PATH": "C:\\Program Files (x86)\\Arduino",
        "USER_PATH": "C:\\Users\\robo\\Documents\\Arduino"
    },
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}",
                "${env:PACKAGES_PATH}\\hardware\\tools\\avr\\avr\\include",
                "${env:PACKAGES_PATH}\\hardware\\arduino\\avr",
                "${env:PACKAGES_PATH}\\tools"
            ],
            "browse": {
                "path": [
                    "${workspaceFolder}",
                    "${env:PACKAGES_PATH}\\tools",
                    "${env:PACKAGES_PATH}\\hardware",
                    "${env:PACKAGES_PATH}\\libraries",
                    "${env:USER_PATH}\\libraries"
                ]
            },
            "forcedInclude": [
                "${env:PACKAGES_PATH}\\hardware\\arduino\\avr\\cores\\arduino\\Arduino.h"
            ],
            "intelliSenseMode": "msvc-x64",
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
}
```

## 基本的な使い方

コマンドパレットというVS Codeの機能を使って何らかのアクションを行う方法を紹介します。

* `Arduino: Board Manager` - ボード用のパッケージを管理します。サードパーティ製のパッケージを追加できるらしいです。
* `Arduino: Change Baud Rate` - シリアル通信速度を変更します。初期値は9600です。
* `Arduino: Change Board Type` - ボードタイプ、プラットフォームを変更します。
* `Arduino: Close Serial Monitor` - シリアルモニターを閉じます。
* `Arduino: Examples` - スケッチの例を表示します。
* `Arduino: Initialize` - スケッチの雛形を作ります。
* `Arduino: Library Manager` - ライブラリを探索、管理します。
* `Arduino: Open Serial Monitor` - シリアルモニターを開きます。
* `Arduino: Select Serial Port` - シリアルポートを変更します。
* `Arduino: Send Text to Serial Port` - 現在のシリアルポートを介して1行のテキストを送信します。
* `Arduino: Upload` - スケッチをコンパイルおよびアップロードします。
* `Arduino: Upload Using Programmer` - 外部プログラマを使用してアップロードします。
* `Arduino: Verify` - スケッチをコンパイルします。文法エラーなどがないか確認できます。

よく使うものは`Arduino: Board Config`、`Arduino: Select Serial Port`、`Arduino: Upload`です。
`Arduino: Upload`にはAlt+Ctrl+U、`Arduino: Verify`にはAlt+Ctrl+Rのキーボードショートカットが割り当てられています。

紹介しといてなんですが、わざわざコマンドパレットを開くことなく上述のアクションを行うことができます。
画面下部の青いバーには次のショートカットが割り当てられています。

* `<Select Board Type>`、またはArduinoのボード名が書いてあるボタンでArduino: Board Configを実行できます。
* `<Select Serial Port>`というボタンでArduino: Select Serial Portが実行できます。
* これら2つのボタンの間にある電源プラグのボタンを押すとシリアルモニターが開きます。シリアル通信でのログが出力されます。

`.ino`ファイルを編集中、`Arduino: Verify`と`Arduino: Upload`のボタンが画面右上に表示されます。

## 終わりに

VS CodeでのArduinoの使い方の紹介は以上です。これ読んで分からなかったところは調べてください。
Arduinoの入門で参考になったサイトのリンクを載せておきます。

https://deviceplus.jp/hobby/arduino-listicle-01/

## 追記

**VS Codeで編集、ArduinoIDEで実行** (2020/11/12追記)

ここまで長々と書きましたが、正直こっちの方法のほうが簡単です。

まずはArduinoIDEの設定を編集します。Arduinoを開き、ファイル > 環境設定と進みます。「外部エディターを使用する」にチェックを入れます。設定ウィンドウ右下のOKボタンを押すと、コード編集画面が暗くなって編集ができなくなります。

次に、メインフォルダー(プロジェクトのフォルダー)をVS Codeで開きます。ArduinoIDEは閉じないでください。「プロジェクトの準備」節と同様の操作を行います。プログラムを編集し、上書き保存(Ctrl+S)するとプログラムの変更がArduinoIDEにも反映されます。タイトルにもつけましたが、VS Codeでプログラムを編集し、ArduinoIDEを開いて実行という方法が取れます。

**ArduinoIDEの設定をいい感じにする** (2020/11/12追記)

IDEの「環境設定」でもある程度はいじれるのですが、もっと細かい設定は別の場所においてあります。OSごとのそのファイルの場所は次の通りです。
※Windowsは実機で確認しましたが、Mac、Linuxはインターネットの情報が元なので少し異なるかもしれません。

* Windows - `C:\Users\<username>\AppData\Roaming\Arduino\preferences.txt`
* Mac - `/Users/<username>/Library/Arduino15/preferences.txt`
* Linux - `~/.arduino15/preferences.txt`

このファイルは壊すとArduinoIDEが動かなくなるので、コピーを作り、原本を編集してIDEが動かなくなったら元に戻すという形を取りましょう。
このファイルの記述形式は`<key>=<value>`です。例として、`editor.advanced`を`true`に設定してください(すでに設定されている項目がないか探して、なければ適当な所に新しい行を追加して書いてください)。IDEのエディターが少し便利になります。他にも便利な設定がいくつかあります。気になったら下のリンクを参考にしてください。

参考:
https://jumbleat.comk/2018/08/25/customize_ide_preferences_file/
https://garretlab.web.fc2.com/arduino/introduction/preferences/index.html
https://www.arduino.cc/en/hacking/preferences
https://github.com/arduino/Arduino/blob/master/build/shared/lib/preferences.txt
