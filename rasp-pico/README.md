<!-- omit in toc -->
# Raspberry Pi Pico

<!-- omit in toc -->
## Table of Contents

- [Pythonでの開発方法](#pythonでの開発方法)
  - [準備するもの](#準備するもの)
  - [やること](#やること)
  - [VSCode以外の方法](#vscode以外の方法)
- [参考](#参考)

## Pythonでの開発方法

### 準備するもの

- VSCode
- Python(使わないけどついでに)

上記のものを用意するにあたって参考になりそうなURL

- https://qiita.com/ayuchiy/items/82d6d2dfcf1acc3bec00

### やること

まずはPico側のセットアップ

1. [Getting Started with RP2040 - Raspberry Pi](https://www.raspberrypi.org/documentation/rp2040/getting-started/#getting-started-with-micropython)を開く
2. 「Download UF2 File」をクリック -> picoのセットアップ用のファイルがダウンロードされる
3. Raspberry Pi PicoのBOOTSELボタン(白いやつ)を押しながらパソコンにつなげる
4. **picoが認識されるまで**押し続けて待つ
5. `2.`でダウンロードしたファイルをpicoにコピペ
6. 自動的にpicoが再起動される

次に、パソコン側のセットアップ

1. 「Pico-Go」という名前の拡張機能をVSCodeに入れる
2. VSCodeを再起動
3. このままだと「Pico-Go」がうるさいので、この拡張機能を無効にする(任意)

拡張機能について参考になりそうなURL

- https://qiita.com/ucan-lab/items/e85931bf8276da43cc97
- https://zenn.dev/karaage0703/books/80b6999d429abc8051bb

プロジェクトを始める方法

1. プロジェクトフォルダをVSCodeで開く
2. 「Pico-Go」の拡張機能を**ワークスペースで**有効にする
   1. 拡張機能を表示する
   2. 緑色の「有効にする」のボタンの右側にある矢印ボタンを押す
   3. 「有効にする(ワークスペース)」を選択する
3. Ctrl + Shift + Pでコマンドパレットを開く
4. Pico-Go > Configure Projectを選択
5. 自動で色々とやってくれる

### VSCode以外の方法

picoのセットアップはVSCodeの場合と同様。[Thonny](https://thonny.org/)というIDEを使う。サイトからインストーラーをダウンロードして、ダウンロードしたものを開いてThonnyをインストールする。インストールが終わったらThonnyを「Regular Mode」で起動する。起動後、左上のメニューからrun > Select Interpreterと進み、MicroPython (Raspberry Pi Pico)を選択。picoが接続されている場合は自動でREPLが開く。

## 参考

- https://blog.boochow.com/article/rpi-pico-upython.html
- https://rikoubou.hatenablog.com/entry/2021/02/05/150631
- https://github.com/raspberrypi/pico-sdk
- https://www.raspberrypi.org/documentation/rp2040/getting-started/
