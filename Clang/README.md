# C/C++

gccのコンパイラーでインストール方法、VS Codeでの使い方を紹介します。

## Installation

`gcc`および`g++`コマンドが動くようになったらインストール成功です。

### Windows

WindowsではMinGWを入れます。[このページ](http://www.mingw.org/)からMinGWをダウンロードします。
<!-- TODO -->

### Mac

http://qiita.com/ShinichiOkayama/items/962e55ac7f8920a5f007

## Usage

C言語の使用例です。

```PowerShell
PS C:\path\to\directory> cat helloworld.c
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}
PS C:\path\to\directory> gcc helloworld.c
PS C:\path\to\directory> .\a.exe
Hello, world!
PS C:\path:to\directory> rm a.exe
```

`gcc [filename].c`でコンパイルします。コンパイル後のファイルの拡張子はWindowsであれば`.exe`、Macであれば`.out`となります。

C++の場合はファイル拡張子が`.c`から`.c++`、`gcc`が`g++`になります。

## Use in VS Code

VS Code内での使用方法です。<!-- TODO -->

## 参考
