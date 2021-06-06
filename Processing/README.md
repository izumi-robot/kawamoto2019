<!-- omit in toc -->
# Processing

この文書では主に、VSCodeでのProcessingの使い方について紹介します。

前提として、ProcessingのIDEとVSCodeが入っている必要があります。パス名やキーボードショートカットなど、OSによって異なる部分はWindowsのものを記述します。書いてないことはググってください。

<!-- omit in toc -->
## 目次

- [拡張機能のインストール](#拡張機能のインストール)
- [VSCodeの設定変更](#vscodeの設定変更)
- [プロジェクトの準備](#プロジェクトの準備)
- [参考](#参考)

最初の2つは初期設定についてです。自分のパソコンに入れるのでなければ読み飛ばしてください。

## 拡張機能のインストール

[Processing Language](https://marketplace.visualstudio.com/items?itemName=Tobiah.language-pde)拡張機能です。これをインストールすることで、VSCodeからProcessing関連の操作を手軽に行えるようになります。

## VSCodeの設定変更

1. VSCodeで設定を変更する
   1. VSCodeを開く
   2. Ctrl + ,
2. 「Processing: Path」をProcessingの実行プログラムのパスに設定
   - 私のパソコンでは`C:\Users\<username>\Documents\processing-3.5.4\processing-java`
   - ロボット部のSurfaceだと`C:\Users\robo\Desktop\processing-3.5.4\processing-java`
   - [Processingの導入について](https://qiita.com/greatnekochan/items/010237ab3313757d0b0b)

`processing-<version>`という名前のフォルダーを探して、その中の`processing-java.exe`というファイルのパスを指定してください(拡張子は不要)。

## プロジェクトの準備

以降は実際のプロジェクトでの作業になります。ここでは例として、`root`というフォルダー(親フォルダーとします)内に`sample`という名前のプロジェクトを作る場合の作業を紹介します。

1. まずは、親フォルダー内に`sample`という名前のフォルダー(メインフォルダーとする)を作成
2. メインフォルダーをVSCodeで開き、`sample.pde`というファイルを追加
3. このファイルの中に実行したいプログラム書き込む ※今はしなくていい

ここまでで、ファイル構造は以下のようになっています。

```
root
 |- sample
 |   |- sample.pde
```
次に、ビルドタスクを作成します。

1. Ctrl + Shift + Pでコマンドパレットを開く
2. 「Processing: Create Task File」を選択

メインフォルダー直下に`.vscode`というフォルダーが作成され、そしてそのフォルダーの中には`tasks.json`というファイルがあります。

この時点でのファイル構造はこんな感じです。

```
root
 |- sample
     |- .vscode
     |   |- tasks.json
     |- sample.pde
```

`tasks.json`に記述されているのはビルドタスクの情報です。より具体的に言うと、ターミナルに打つコマンドの情報が記載されています。
ビルドタスクはCtrl+Shift+Bで実行できます。今の時点で`sample.pde`に何か書いてCtrl+Shift+Bを押すとアニメーションを実行できます(アニメーション終了後、コンソールの指示にしたがってパネルを閉じてください)。ですが、実行と同時に`out`というフォルダーが作成され、そこに`sample.pde`のコードがJavaに翻訳されたものが保存されます(このフォルダーは消していいです)。この挙動を消すために、`tasks.json`を編集します。
編集前の`tasks.json`は(Windowsでは)以下のようになっています:

```JSON
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Run Sketch",
      "type": "shell",
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "command": "${config:processing.path}",
      "presentation": {
        "echo": true,
        "reveal": "always",
        "focus": false,
        "panel": "dedicated"
      },
      "args": [
    "--force",
    "--sketch=${workspaceRoot}",
    "--output=${workspaceRoot}/out",
    "--run"
    ],
      "windows": {
        "args": [
          "--force",
          {
            "value": "--sketch=${workspaceRoot}",
            "quoting": "strong"
          },
          {
            "value": "--output=${workspaceRoot}\\out",
            "quoting": "strong"
          },
          "--run"
        ]
      }
    }
  ]
}
```

これを次のように変更します:

```JSON
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Run Sketch",
            "type": "shell",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "command": "${config:processing.path}",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "args": [
                "--force",
                "--sketch=${workspaceRoot}",
                "--run"
            ]
        }
    ]
}
```

具体的に何を変更したかの説明です:

* インデントを2マスから4マスに変更。めっちゃ見やすくなります。
* `presentation`内の`panel`の値を`dedicated`(占有)から`new`(新規)に変更。タスク実行時、ログの出力パネルが新たに作成されます。
* `args`内の`--output=${workspaceRoot}/out`を削除。`out`フォルダーが作成されなくなります。ちなみに、argsとはarguments(引数)の略です。
* `windows`キーを削除。この部分はおそらく`--output=${workspaceRoot}\\out`と指定するためだけにあるので、もう必要ないです。

これで設定は完了です。VSCodeでのProcessingを楽しんでください。

## 参考

* https://qiita.com/jacynthe/items/d31eaa77496295c10556
* https://marketplace.visualstudio.com/items?itemName=Tobiah.language-pde
* https://github.com/TobiahZ/processing-vscode
