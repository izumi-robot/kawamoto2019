<!-- omit in toc -->
# C/C++

gccのコンパイラーでインストール方法、VS Codeでの使い方を紹介します。

<!-- omit in toc -->
## 目次

- [インストール方法](#インストール方法)
  - [Windows](#windows)
  - [Mac](#mac)
- [使い方](#使い方)
- [VSCodeとの連携方法](#vscodeとの連携方法)

## インストール方法

`gcc`および`g++`コマンドが動くようになったらインストール成功です。

### Windows

WindowsでC/C++を使う方法はいろいろあるのですが、ここではMSYS2経由でMinGWを入れる方法を紹介します。

1. https://www.msys2.org/ を開く
2. 少しスクロールしたところにある「msys2-x86_64-xxxxxxxx.exe」をクリック
3. インストーラのダウンロードが始まる。ダウンロードしたものを開く
4. Windowsディフェンダーでプログラムの実行がブロックされた場合は、「詳細」を展開して「実行」ボタンを押す
5. インストールのオプションがいろいろと表示されるが、何も変えずに「次へ」を連打
6. インストールが終わったら、「Run MSYS2 now」みたいな感じのオプションにチェックを入れてインストーラを閉じる
7. MSYS2が開く。以下、そのウィンドウでコマンドを入力していく。途中、「`[Y/n]`」の選択が何度かあるが、全て`y`を入力する。途中でMSYS2のウィンドウが勝手に閉じたら、スタートメニューから「MSYS2 64bit > MSYS2 MSYS」を開く
   1. `pacman -Syu`
   2. `pacman -Su`
   3. `pacman -S --needed base-devel mingw-w64-x86_64-toolchain`
8. MSYS2を閉じる。次に、環境変数を設定する<br>※(パスの通し方)[https://www.atmarkit.co.jp/ait/articles/1805/11/news035.html]
9. Windowsの設定で「環境変数」と検索
10. 「システム環境変数の編集」を選ぶ
11. 管理者権限が要求されるので、通す
12. 「環境変数」を選択
13. 下の段の「Path」を選択
14. 「新規」をクリックして、次の2つを追加する
    - 「C:\msys64\mingw\bin\」
    - 「C:\msys64\usr\bin\」
15. 終わり。念のため再起動

### Mac

http://qiita.com/ShinichiOkayama/items/962e55ac7f8920a5f007

## 使い方

C言語の使用例です。

```
$ ls
helloworld.c
$ cat helloworld.c
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}
$ gcc helloworld.c
$ .\a.exe
Hello, world!
$ rm a.exe
```

`gcc [filename].c`でコンパイルします。コンパイル後のファイルの拡張子はWindowsであれば`.exe`、Macであれば`.out`となります。

C++の場合はファイル拡張子が`.c`から`.cpp`、`gcc`が`g++`になります。

## VSCodeとの連携方法

VSCode内での使用方法です。

1. 以下の[C/C++ の拡張機能](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)をインストール ※[拡張機能について](https://futureys.tokyo/how-should-i-manage-extension-in-vscode/)
2. 拡張子`.cpp`でファイル作成
3. 勝手に拡張機能が起動して補完、型チェックなどいろいろとやってくれる
