# VSCodeでProcessingのPython Modeを使う

参考: https://qiita.com/H1rono_K/items/a340bf60d37e802e906a

まさにそれってことが上のサイトに書いてあります。多分こっち見たほうが早いです。
やることはざっとこんな感じです。

1. フォルダを作る
2. 設定変更
3. ファイルをコピーする
4. スケッチファイルを作る

## 1. フォルダを作る

空のフォルダを1つ作ります。ここでは仮に、`processing-py`というものを作ったとします。以降の作業はVSCodeでこのフォルダを開いた状態で行います。

## 2. 設定変更

VSCode内の設定を開き、ワークスペース内の`Python > Linting: Enabled`のチェックを外します。
※絶対にユーザーの設定は変更しないで下さい!他のファイルに影響が出ます!

こうすることで`processing-py`内に`.vscode`というフォルダが自動で作成され、その中に`settings.json`というものができます。中身はこんな感じです。

```json
{
    "python.linting.enabled": false
}
```

ワークスペース?ナニソレ?ってなってる人は上の`.json`ファイルを手動で追加して下さい。現時点でのファイル構造はこんな感じです。

```
processing-py
    └ .vscode
        └ settings.json
```

`settings.json`の内容は上に示した通りです。

## 3. ファイルをコピーする

スケッチ実行用のバッチファイル`runner.bat`を作成しました。このREADMEが置いてあるのと同じ所にあります。このファイルを`processing-py`内にコピーして下さい。ファイル構造はこうなります。

```
processing-py
    ├ .vscode
    │   └ settings.json
    └ runner.bat
```

一応注意しておきます。このバッチファイルは`C:\Users\robo\Documents\processing.py-3017-windows64\processing-py.jar`を参照しています。参照先のファイルは絶対に動かさないで下さい。

## 4. スケッチファイルを作る

名前は何でもいいです。仮に`sketch.py`というファイルを作成したとします。このコードを実行するには、ターミナルから`.\runner.bat sketch.py`を実行します。試しにこのREADMEがあるフォルダをVSCodeで開き、Ctrl+@でターミナルを開いて実行してみて下さい。数秒してからスケッチウィンドウが開くと思います。

方法としてはこんな感じです。`processing-py`内にはスケッチファイルをいくつも置くことができます。実行方法は`.\runner.bat [filename].py`です。`[filename]`内にスペースがある場合は、`"[filename].py"`のようにダブルクオーテーションで囲って下さい。

# IDEで使う

せっかくなので書いておきます。Processing IDEを開き、右上のモード選択ボタンから使用言語を切り替えます。実行方法などはJavaでの場合と大差ないです。IDEで作った場合はスケッチファイルの拡張子が`.pyde`になりますが、大した違いはないです。
