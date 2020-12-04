# Processing

この文書では主に、VSCodeでのProcessingの使い方について紹介します。

参考:

* https://qiita.com/jacynthe/items/d31eaa77496295c10556

* https://marketplace.visualstudio.com/items?itemName=Tobiah.language-pde
* https://github.com/TobiahZ/processing-vscode

詳しいことはこちらを見てください。下の2つは公式によるドキュメントです。英語なのでおすすめはしません。

前提として、ProcessingのIDEとVSCodeが入っている必要があります。パス名やキーボードショートカットなど、OSによって異なる部分はWindowsのものを記述します。他のOSの方は適宜読み替えるか、調べるかしてください。VSCodeの操作で分からないことは`~\kawamoto\README.md`を見てください。下の2つのURLは公式のドキュメントです。英語なのでおすすめはしません。

## 目次

* 拡張機能のインストール
* VSCodeの設定変更
* プロジェクトの準備
* 終わりに

最初の2つは初期設定についてです。自分のパソコンに入れるのでなければ読み飛ばしてください。

## 拡張機能のインストール

Processing Languageという名前の拡張機能です。これをインストールすることで、VSCodeからProcessing関連の操作を手軽に行えるようになります。

## VSCodeの設定変更

VSCodeを開いて「Processing: Path」を編集します。
Processingの実行プログラムのパスを設定します。筆者のパソコンでは`C:\Users\<username>\Documents\processing-3.5.4\processing-java`でした。ロボット部のSurfaceだと`C:\Users\robo\Desktop\processing-3.5.4\processing-java`です。`processing-<version>`という名前のフォルダを探して、その中の`processing-java.exe`というファイルのパスを指定してください(拡張子はいらないです)。

## プロジェクトの準備

以降は実際のプロジェクトでの作業になります。ここでは例として、`C:\Users\robo\Desktop\2019\kawamoto\Processing\`のフォルダ(親フォルダとします)内に`sample`という名前のプロジェクトを作る場合の作業を紹介します。

まずは、親フォルダ内に`sample`という名前のフォルダ(メインフォルダとします)を作成します。メインフォルダをVSCodeで開き、`sample.pde`というファイルを追加します。このファイルの中に実行したいプログラム書き込みます。今はしなくていいです。

ここまでで、ファイル構造は以下のようになっています:

```
C:\Users\robo\Desktop\2019\kawamoto\Processing
    └ sample
        └ sample.pde
```

次に、Ctrl+Shift+Pでコマンドパレットを開き、「Processing」と検索します。検索結果の中から「Processing: Create Task File」を選択します。メインフォルダ直下に`.vscode`というフォルダが作成され、そしてそのフォルダの中には`tasks.json`というファイルがあります。

この時点でのファイル構造はこんな感じです。

```
C:\Users\robo\Desktop\2019\kawamoto\Processing
    └ sample
        ├ .vscode
        │   └ tasks.json
        └ sample.pde
```

`tasks.json`に記述されているのはビルドタスクの情報です。より具体的に言うと、ターミナルに打つコマンドの情報が記載されています。
ビルドタスクはCtrl+Shift+Bで実行できます。今の時点で`sample.pde`に何か書いてCtrl+Shift+Bを押すとアニメーションを実行できます(アニメーション終了後、コンソールの指示に従ってパネルを閉じてください)。ですが、実行と同時に`out`というフォルダが作成され、そこに`sample.pde`のコードがJavaに翻訳されたものが保存されます(このフォルダは消していいです)。この挙動を消すために、`tasks.json`を編集します。
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
                "panel": "new"
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
* `args`内の`--output=${workspaceRoot}/out`を削除。`out`フォルダが作成されなくなります。ちなみに、argsとはarguments(引数)の略です。
* `windows`キーを削除。この部分はおそらく`--output=${workspaceRoot}\\out`と指定するためだけにあるので、もう必要ないです。

これで設定は完了です。VSCodeでのProcessingを楽しんでください。

## 終わりに

この記事ではVSCodeでProcessing使用する方法についてまとめました。このフォルダ内にある`sample`で始まる名前のプロジェクトには、筆者が1年下の後輩にProcessingを教える際に使ったサンプルコードがあります。各フォルダ内の`README.md`にコードの解説を書く予定です。よかったら活用してください。

ちなみに、ファイル構造を表す書式は[こちら](https://qiita.com/paty-fakename/items/c82ed27b4070feeceff6)を参考にしました。
