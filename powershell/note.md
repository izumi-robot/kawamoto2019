---
title: Windowsバッチまとめ
tags: bat batch バッチ バッチファイル Windows
author: tomotagwork
slide: false
---
# はじめに
Python? PHP?　いやいや、そんなオサレなものではなく、ここで取り上げるのは今そこにあるWindowsバッチです。
たまたま最近Windows Server周りの管理やWindowsを使ったバッチ運用の仕組み作りに携わることがあり、今更ながらWindowsバッチと格闘することになったので、備忘録としてまとめます。
Unix系のシェル・スクリプトに慣れているとWindowsバッチは結構クセがあって使いづらいと思います。VBScriptも今更な感じだし本命はPowerShellなのかなと思いますが、PowerShellはパッと見とっつきにくそうで拒絶反応が出ました。
手軽にグーグル先生に頼れない現場環境であったということもあり、手っ取り早くWindowsバッチを使ってみたという感じです(Windows10だとbashが使えるらしいので早くそういう環境が広がってほしいんですが...)。
情報としては目新しいものは無いですが、細かいところは結構あちこち調べなければならなかったので、この辺押さえておけばある程度のことは出来るでしょう、というのをまとめました。

# 基本
## ファイル名
拡張子 .bat
ex. test.bat
## コメント行
行頭にremを付ける
"rem"自体はコマンドなのでヘルプも見られます。
行末コメントや複数行コメントの仕組みは無いようです。
擬似的にそれらを行うテクニックはあるようですが、条件によっては正しく動作しなかったり混乱の元になりそうなので個人的にはあまり使うべきではないと思います。
(remコマンドの代わりに「::」を使う方法も、ラベルの仕組みを利用した擬似的なコメント記載方法なので同様。)

## 定跡的な(?)使い方
先頭に以下の3行を書いておく。

```bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0
```

バッチを実行すると、デフォルトの挙動としてバッチファイルに記述されている命令文がすべて標準出力に表示されてしまいます。bashとかでデバッグする場合に```sh -x xxx.sh``` のように"-x"オプション付きで実行したりしますが、Windowsバッチではデフォルトがそのような挙動になっちゃってます(うーん、鬱陶しい)。各コマンドの先頭に「@」を付けるとそのコマンドは表示されなくなりますが、それぞれ「@」つけるのは現実的ではないですね。```echo off```というコマンドを使うとこの機能がオフになり、それ以降コマンド自体の出力が抑止されます。```echo off```自体も出力させないために、最初だけ「@」付けて```@echo off```としている訳です。
つまり、最初に```@echo off```を宣言しておくことで、一切命令文の表示がされなくなります(≒shの-xオプション無しの動作)。ま、普通こうしますわな。
```setlocal enabledelayedexpansion```は遅延変数と呼ばれるものを使う場合の指定。変数のセクションで補足します。
```cd %~dp0```は、当該バッチファイルが置かれているディレクトリーをカレントディレクトリーにしています。これも後続のセクションで補足します。

※コメント頂いたので追記します。
複数ドライブがある場合は、```cd /d %~dp0``` というように/dオプションも付けておくと、カレントドライブも変更されるのでベターです。

## 実行方法

* コマンド・プロンプトでバッチファイル名を指定してエンター
* explorerからダブルクリック
* タスクスケジューラーで指定
* スタートアップフォルダーにバッチファイルのショートカットを作成してログイン時に自動実行

このあたりの起動方法を想定してます。
バッチから別のバッチの呼び出しについては別セクションで補足します。

## ヘルプ
困ったらヘルプ参照。
[コマンド] /? でヘルプ参照可能です。

```
C:\>echo /?
メッセージを表示したり、コマンド エコーの ON と OFF を切り替えます。

  ECHO [ON | OFF]
  ECHO [メッセージ]

現在のエコー設定を表示するには、パラメーターを指定せずに ECHO と入力して
ください。
```

## その他
コマンド、変数名について大文字、小文字は基本区別無し。
while文, switch文に相当するものは無さそう。
(それっぽいものはif文とかgoto文を駆使して実装しないといけないようだ。イケてないね。)
関数みたいなものも無さそう。

# 変数
## 変数の設定と参照
```bat:
set var1="abcde"
set var2=abcde
set var3=12345
set var4 = 54321
set /a "var5 = var3 + 1"
set /a "var6 = %var3% + %var4 %"

echo var1: %var1%
echo var2: %var2%
echo var3: %var3%
echo var4: %var4%
echo var4 : %var4 %
echo var5: %var5%
echo var6: %var6%
```

```xxx:実行結果
var1: "abcde"
var2: abcde
var3: 12345
var4:
var4 :  54321
var5: 12346
var6: 66666
```

* 変数への値のセットは```set```コマンドを使用します。
* 変数に値をセットする際、=の前後にブランクを入れないようにします(ブランクを入れるとブランクを含めた変数名、値と認識される: var4の例参照)。
* 変数を参照する際は%で変数名をくくる(```%var1%```)。
* 計算式の結果を変数に代入する場合は```set /a```を使用します。計算式では変数の参照の際は%を付けても付けなくてもOK(ただしブランクは文字区切りと判断されるようです)。

## 遅延変数
ハマリがちなのがコレ。

```bat:
set result=***
set var1=aaa
if %var1%==aaa (
	set result=TRUE
	echo result: %result%
)
```

```xxx:実行結果
result: ***
```

パッと見、このコードはresult: TRUEと表示されることを期待しますがそうはなりません。
if文は最後の括弧閉じまで(上のソースだと最後4行分)が1つの命令なので、まずその命令実行前に変数解釈が行われます。すなわち、echo文の%result%は、if文が読まれた時点のresultの内容「***」に置き換えられます(変数解釈が行われるタイミングでは```set result=TRUE```はまだ実行されていない)。
これは、```@echo off``` を指定せず(= ```@echo on```で)実行してみると分かりやすいです。

```xxx:echo_onでの実行結果
C:\>set result=***

C:\>set var1=aaa

C:\>if aaa == aaa (
set result=TRUE
 echo result: ***
)
result: ***
```

遅延変数というのを使うと、実行時に変数解釈が行われます。
先ほどのを遅延変数を使って書き換えると...

```bat:
setlocal enabledelayedexpansion

set result=***
set var1=aaa
if %var1%==aaa (
	set result=TRUE
	echo result: !result!
)
```

```xxx:実行結果
result: TRUE
```
先頭に、```setlocal enabledelayedexpansion```を追加し、変数の参照の際%ではなく!で変数名をくくります(```!result!```)。

ifやfor文の中で変数を参照する際はその変数がどのタイミングで設定されているかに注意して、必要に応じて遅延変数を使いましょう。
(Unix系のシェルだとこんなこと無いのでとまどいますね。まったくめんどくさい挙動だ...)

## 日付/時刻
環境変数```date```、```time```で日付、時刻が取得できます。
実行ログをファイルに書き出す際にタイムスタンプ付けたりしたい時に使えます。

```bat:
setlocal enabledelayedexpansion

echo 日付 %date%
echo 時刻 %time%

set var1=aaa
if %var1%==aaa (
	echo %date% %time% --- begin ---
	timeout /t 5 /nobreak
	echo %date% %time% --- end ---
)

if %var1%==aaa (
	echo !date! !time! --- begin ---
	timeout /t 5 /nobreak
	echo !date! !time! --- end ---
)
```

```xxx:実行結果
日付 2016/07/31
時刻 14:04:31.82
2016/07/31 14:04:31.82 --- begin ---

0 秒待っています。終了するには CTRL+C を押してください ...
2016/07/31 14:04:31.82 --- end ---
2016/07/31 14:04:36.11 --- begin ---

0 秒待っています。終了するには CTRL+C を押してください ...
2016/07/31 14:04:41.16 --- end ---
```

```%date%```, ```%time%``` で現在の日付、時刻を取得できます。時刻は10ミリ秒単位での値が取得されます。
if文やfor文の中で時間がかかる処理の前後のタイムスタンプを取得するような場合は注意が必要です。上の例では、if文中に```timeout```コマンドで5秒スリープしており、その前後でタイムスタンプを出力していますが、%で変数参照するとif文読み取り時に変数解釈されるので、1つめのbegin, endペアは同じ時刻が出力されてしまってますね。
2つめの例は!による遅延変数としての参照なので、きちんと```timeout```コマンド前後のタイムスタンプが取れてます。
もう一点、time環境変数についての注意です。なんと、0時～9時の場合、出力結果の桁数が少なくなります！
例: 

* 1時5分のtime環境変数の値 =>  1:05:00.00 (01:05:00.00ではなく先頭に半角スペースが入る)
* 11時5分のtime環境変数の値 => 11:05:00.00

時刻部分について**だけ**は、なぜか桁あわせのために0ではなく半角スペースをぶち込んでくるというなんともひどい仕様になってます。
時刻を文字列として扱いたい場合(ファイル名にタイムスタンプを付ける場合など)、順序性がずれてしまったりするので、この挙動は認識しておかないと痛い目を見ます。

## 変数解釈時の文字列操作

変数に格納されている文字列について、一部分を抽出したり、置換したりすることができます。
### 抽出
基本形はこちらです。
%<変数名>:~<開始位置>,<文字数>%
一部省略や-指定で意味合いが変わります。
開始位置については、先頭文字は0文字目とカウントします。

```bat:
rem 文字列全体
echo ex00: %var1%

rem 3文字目から最後まで
echo ex01: %var1:~3%

rem 3文字目から5文字分
echo ex02: %var1:~3,5%

rem 3文字目から、末尾5文字を除いたもの
echo ex03: %var1:~3,-5%

rem 末尾より数えて8文字目から最後まで
echo ex04: %var1:~-8%

rem 末尾より数えて8文字目から5文字分
echo ex05: %var1:~-8,5%

rem 末尾より数えて8文字目から、末尾5文字を除いたもの
echo ex06: %var1:~-8,-5%
```

```xxx:実行結果
ex00: abcde12345
ex01: de12345
ex02: de123
ex03: de
ex04: cde12345
ex05: cde12
ex06: cde
```

### 置換
基本形はこちらです。
%<変数名>:<置換前文字列>=<置換後文字列>%

```bat:
set var1=aaaaabbbbbcccccaaaaa
echo ex01: %var1:aa=AA%
set var2=abababababababababab
echo ex02: %var2:aba=ABA%
```

```xxx:実行結果
ex01: AAAAabbbbbcccccAAAAa
ex02: ABAbABAbABAbABAbABAb
```

先頭から見ていって都度合致するものを置き換えていく感じでしょうか。

###応用編 (日付/時刻の文字列操作)
日付、時刻の文字列をファイル名に付与してファイル作成したい、といったことがありますね(2016年7月31日 13時14分55秒にエラー・ログファイルを作成 => test_20160731_131455.logみたいな)。
上の方法を使って、%date%, %time%から必要な文字列だけ抜き出すことができます。

```bat:
rem 現在の日時を取得
set thisDate=%date%
set thisTime=%time%

rem 日付の区切りの/を省略 (置換先文字列無し)
set custDate=%thisDate:/=%

rem 時刻の文字列に半角スペースがあった場合0に置換
set custTime_temp=%thisTime: =0%
rem 先頭から8文字分を抽出(ミリ秒単位は省く)
set custTime_temp=%custTime_temp:~0,8%
rem 時刻の区切りの:を省略(置換先文字列無し)
set custTime=%custTime_temp::=%

echo original:   %thisDate% %thisTime%
echo customized: %custDate% %custTime%
```

```xxx:実行結果
original:   2016/07/31  9:32:44.02
customized: 20160731 093244
```

時刻の方は、最初に半角スペースを0に置き換える処理を入れているのがポイントです。先に示した通り、時間部分は一桁の場合に0ではなく半角スペースになってしまいますので、そのために一手間入れています。


## 引数取得用変数(バッチパラメーター)
コマンド・プロンプトからバッチファイルを指定してバッチを実行する際、引数を渡すことができます。
引数の区切り文字としては、ブランク(半角スペース)、カンマ(,)、セミコロン(;)、イコール(=)が使用できます。
渡された引数は、バッチファイル上%1～%9までの変数(バッチパラメーターと呼ぶらしい)で受け取ることができます。%0は実行されたバッチファイルが入ります。
(10個以上の引数渡す場合はどうするの?となりますが、shiftというコマンドを使ってハンドリングします。まぁそこまで使うことはまずないのでここでは割愛。)

```bat:test.bat
@echo off
echo arg0: %0
echo arg1: %1
echo arg2: %2
echo arg2: %~2
echo arg3: %3
echo arg4: %4
```

```xxx:実行結果
c:\temp\batch_test>test.bat aaa "bbb ccc",ddd=eee;fff
arg0: test.bat
arg1: aaa
arg2: "bbb ccc"
arg2: bbb ccc
arg3: ddd
arg4: eee
```

区切り文字を含む文字列を引数で渡したい場合ダブルクォーテーション(")で括ります。ただし、その場合ダブルクォーテーションも含めた文字列が渡されます。
```%~2```というように間に「~」を指定すると、ダブルクォーテーションが削除された文字列が取得できます。
このように、バッチパラメーターの%と数字の間にオプションを指定することで、取得される値を加工することができます。
これはcallコマンドのヘルプを見ると詳細が載っています。

```
c:\>call /?
バッチ プログラムを別のバッチ プログラムから呼び出します。

(略)

    バッチ パラメーター (%n) の置換は拡張されました。次のオプション構文
    を使うことができます:

        %~1         - すべての引用句 (") を削除して、%1 を展開します。
        %~f1        - %1 を完全修飾パス名に展開します。
        %~d1        - %1 をドライブ文字だけに展開します。
        %~p1        - %1 をパスだけに展開します。
        %~n1        - %1 をファイル名だけに展開します。
        %~x1        - %1 をファイル拡張子だけに展開します。
        %~s1        - 展開されたパスは、短い名前だけを含みます。
        %~a1        - %1 をファイル属性に展開します。
        %~t1        - %1 をファイルの日付/時刻に展開します。
        %~z1        - %1 をファイルのサイズに展開します。
        %~$PATH:1   - PATH 環境変数に指定されているディレクトリを検索し、
                       最初に見つかった完全修飾名に %1 を展開します。
                       環境変数名が定義されていない場合、または
                       検索してもファイルが見つからなかった場合は、
                       この修飾子を指定すると空の文字列に展開されます。

    修飾子を組み合わせて、複合結果を得ることもできます:

        %~dp1       - %1 をドライブ文字とパスだけに展開します。
        %~nx1       - %1 をファイル名と拡張子だけに展開します。
        %~dp$PATH:1 - PATH 環境変数に指定されているディレクトリを
                       検索して %1 を探し、最初に見つかったファイル
                       のドライブ文字とパスだけに展開します。
        %~ftza1     - %1 を DIR の出力行のように展開します。

    上の例の %1 と PATH は、他の有効な値で置き換えることができ
    ます。%~ 構文は有効な引数の数によって区切られます。%~ 修飾子
    は %* と同時には使用できません。
```

これを参考に、%0 (バッチファイル)についての各種情報を取得してみると...

```bat:
echo ex01: %~f0
echo ex02: %~d0
echo ex03: %~p0
echo ex04: %~n0
echo ex05: %~x0
echo ex06: %~s0
echo ex07: %~a0
echo ex08: %~t0
echo ex09: %~z0
echo ex10: %~dp0
echo ex11: %~nx0
echo ex12: %~ftza0
```

```xxx:実行結果
ex01: c:\temp\batch_test\test.bat
ex02: c:
ex03: \temp\batch_test\
ex04: test
ex05: .bat
ex06: c:\temp\BATCH_~1\test.bat
ex07: --a------
ex08: 2016/08/04 15:16
ex09: 1165
ex10: c:\temp\batch_test\
ex11: test.bat
ex12: --a------ 2016/08/04 15:16 1165 c:\temp\batch_test\test.bat
```

ex10で示される通り```%~dp0```は、当該バッチが配置されているディレクトリのフルパスを示します。
バッチと同じディレクトリにあるファイルを呼んだり、同じところにログファイルを出力したりしたいことが多いので、バッチの先頭で```cd %~dp0```としておくと、バッチがどこで実行されてもOKということになります。

※コメント頂いたので追記します。
複数ドライブがある場合は、```cd /d %~dp0``` というように/dオプションも付けておくと、カレントドライブも変更されるのでこちらの方がおすすめです。

## エラー用変数

```bat:
rem 存在しないコマンドを実行
aaaaa
echo err01: %errorlevel%

rem copyコマンドで存在しないファイルを指定
copy aaa bbb
echo err02: %errorlevel%

rem copyコマンドで正しいファイルを指定
copy test.bat test_temp.bat
echo err03: %errorlevel%
```

```xxx:実行結果
'aaaaa' は、内部コマンドまたは外部コマンド、
操作可能なプログラムまたはバッチ ファイルとして認識されていません。
err01: 9009
指定されたファイルが見つかりません。
err02: 1
        1 個のファイルをコピーしました。
err03: 0
```

コマンドが終了コードを設定した場合や、存在しないコマンドを実行した場合、環境変数errorlevelに終了コードがセットされます。
通常、正常終了の場合0、なんらかのエラーになった場合は1以上の値がセットされます。
バッチの最後に自分でエラーコードをセットしたい場合は終了時に```exit 0```というようにexitコマンドでセットします。
errorlevelの判定については後述の条件分岐のセクションにて記述します。


# フロー制御
##条件分岐 (if文)
### 文字列/数値比較
基本形
IF [NOT] 文字列1 比較演算子 文字列2 コマンド

```bat:
set str1=aaa
set num1=123


rem 文字列比較
if "%str1%" == "aaa" (
	echo str1: TRUE
) else (
	echo str1: FALSE
)

rem 文字列比較 (否定)
if not "%str1%" == "aaa" (
	echo str1: TRUE
) else (
	echo str1: FALSE
)

rem 数値比較
rem 比較演算子: equ(==) neq(!=) lss(<) leq(<=) gtr(>) geq(>=)
if %num1% gtr 10 (
	echo num1: TRUE
) else (
	echo num1: FALSE
)
```

```xxx:実行結果
str1: TRUE
str1: FALSE
num1: TRUE
```

条件式の所で比較対象をダブルクォーテーションで括っているのは、変数名に値がセットされていない場合でも対応できるようにするためです。
条件に使用されている変数が定義されていないと...
ダブルクォーテーションで括らない場合: ```if == aaa```という文を処理しようとして構文エラーになってしまいます。
ダブルクォーテーションで括っている場合: ```if "" == "aaa"```という文を処理することになり、ifの構文として正しくなります(条件式としては偽になるのでELSEの処理に進む)。
(数値の比較については、実際にはこれも文字列比較を行っているらしいような記述もみかけるのだが、どうも正確なところが不明。こちらもダブルクォーテーションで括るほうがよいと思ったのだが、ダブルクォーテーションありと無しで挙動が異なるケースがあった。)

### ファイル存在有無
基本形
IF [NOT] EXIST ファイル名 コマンド

```bat:
cd %~dp0
rem ファイル or ディレクトリ存在有無
set target01=test
if not exist "%target01%" (
	echo %target01% : not found
) else (
	echo %target01% : found
)

rem ディレクトリ存在有無 (末尾に\を付ける)
set dir01=c:\temp\
if not exist "%dir01%"  (
	echo %dir01% : not found
) else (
	echo %dir01% : found
)

rem ファイル/ディレクトリ判定
set target02=c:\temp\test
if exist "%target02%" (
	if exist "%target02%\" (
		echo ディレクトリ %target02%  は存在します
	) else (
		echo ファイル %target02% は存在します
	)
) else (
	echo %target02% は存在しません
)
```

```xxx:実行結果
test : not found
c:\temp\ : found
ファイル c:\temp\test は存在します
```

相対パス、絶対パスの指定が可能です。
existでの判定は、判定対象の文字列の末尾に「\」を指定すると明示的にディレクトリ(フォルダ)として判断されますが、末尾に「\」が無い場合、ファイル/ディレクトリの区別をしません。
すなわち、末尾に「\」が無い文字列の判定を行う際、存在したと判断された場合にがファイルなのかフォルダなのかそれだけでは判断できません(どちらかが存在するということが分かるだけ)。
厳密にファイルが存在するかどうかを判定するには3つ目の例のように2段階で判断をする必要があります。
まぁtest.batのように拡張子をつけて存在確認を行うことが多いと思うのであまりそこまでやる必要はないかもしれませんが、test.batというディレクトリが誤って作成されているとおかしなことになったりします。

### エラー判定
基本形
if [NOT] ERRORLEVEL 番号 コマンド

```bat:
echo ----------------
rem 存在しないコマンドを実行
aaaaa
echo err01: %errorlevel%
if not errorlevel 1 (
	echo ***正常終了***
) else if %errorlevel% equ 9009 (
	echo ***存在しないコマンド***
) else (
	echo ***その他のエラー***
)

echo ----------------
rem copyコマンドで存在しないファイルを指定
copy aaa bbb
echo err02: %errorlevel%
if not errorlevel 1 (
	echo ***正常終了***
) else if %errorlevel% equ 9009 (
	echo ***存在しないコマンド***
) else (
	echo ***その他のエラー***
)

echo ----------------
rem copyコマンドで正しいファイルを指定
copy test.bat test_temp.bat
echo err03: %errorlevel%
if not errorlevel 1 (
	echo ***正常終了***
) else if %errorlevel% equ 9009 (
	echo ***存在しないコマンド***
) else (
	echo ***その他のエラー***
)
```

```xxx:実行結果
----------------
'aaaaa' は、内部コマンドまたは外部コマンド、
操作可能なプログラムまたはバッチ ファイルとして認識されていません。
err01: 9009
***存在しないコマンド***
----------------
指定されたファイルが見つかりません。
err02: 1
***その他のエラー***
----------------
        1 個のファイルをコピーしました。
err03: 0
***正常終了***
```

```if errorlevel 番号```という構文は、「errorlevelが指定した番号**以上**だったら真になる」という非常に混乱を招きやすい仕様となっています。これもひどい仕様ですなぁ。
最初ハマりました。
故に、上の例では、```if not errorlevel 1```(「1以上でなければ」=「0だったら」)という指定にしてます。
2つめの判定```else if %errorlevel% equ 9009```の部分は、「if errorlevel」の構文ではなく、前の文字列/数値比較のセクションで示した構文に従ってerrorlevelという環境変数の値を比較しております(そのため、こっちは%が付いている)。
分かりにくいから、この「if errorlevel 番号」という構文は使わずに%errorlevel%を参照して比較するやり方で統一するのがよいかもしれないですね。 

## 繰り返し処理
ループ処理を行う場合は、JavaとかCとかbashとかだとwhileとかforを使うことになると思います。
ですがバッチにはwhile相当のものは無いようです。

### for文
ここでは一応他の言語っぽい使い方のforを取り上げます。
(Windowsバッチのforは上のような言語で使われるforとは若干使い勝手が異なります。主たる利用目的はファイルやディレクトリを扱うことと捉えたほうがよさそうですが、その使い方は別セクションで補足します。)

基本形:
for /l %%<変数> in (<開始値>,<増分>,<終了値>) do コマンド
※変数はアルファベット一文字

```bat:
@echo off
setlocal enabledelayedexpansion
cd %~dp0

for /l %%i in (0,1,9) do (
	set /a "var1 = %%i * 10"
	echo var1: !var1!
)
```

```xxx:実行結果
var1: 0
var1: 10
var1: 20
var1: 30
var1: 40
var1: 50
var1: 60
var1: 70
var1: 80
var1: 90
```

for文の変数名はなぜか"%%"を付けて利用します。
上の例では0からはじめて1ずつ増やして10まで繰り返すという感じです。
(繰り返し対象の命令文では無駄に10倍して結果を出力させてますが実質的な意味は無いです。for文使うときの変数は遅延変数使わないといけないので注意！)


### goto文/ラベル
「goto文≒悪」みたいな認識のもとに育ってきた身としてはちと受け入れがたいですが、whileが無いので仕方ないですね。Windowsバッチの世界ではまぁまぁよく使われるようです。


```bat:
set /a index=1
set /a loop_count=10
set /a "end_condition = %index% + %loop_count% - 1"

:loop

	rem ループさせたい処理
	echo count: %index% / %loop_count%

	

if %index% geq %end_condition% (
	goto end
	
) else (
	set /a index+=1
	goto loop
)

:end
exit /b 0

```

```xxx:実行結果
count: 1 / 10
count: 2 / 10
count: 3 / 10
count: 4 / 10
count: 5 / 10
count: 6 / 10
count: 7 / 10
count: 8 / 10
count: 9 / 10
count: 10 / 10
```

## バッチから別のバッチの呼び出し
バッチの中から別なバッチを呼び出す方法は、いくつかバリエーションがあるようです。
制御の戻り方、変数の引継ぎ、引数渡し、プロセスという辺りの差異を見ながら試してみました。

### バッチファイル直接指定

```bat:test_main.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set var_main=aaa
set var_sub=

echo ---invoke bat file
test_sub.bat xxx yyy
echo err: %errorlevel%
echo var_main: %var_main%
echo var_sub:  %var_sub%
echo ---end
```

```bat:test_sub.bat
echo ***begin test_sub***
set var_sub=bbb

echo var_main: %var_main%
echo var_sub:  %var_sub%

echo arg1: %1
echo arg2: %2

timeout /t 5 /nobreak
echo ***end test_sub***
```

```xxx:test_main.bat実行結果
c:\temp\batch_test>test_main.bat
---invoke bat file
***begin test_sub***
var_main: aaa
var_sub:  bbb
arg1: xxx
arg2: yyy

0 秒待っています。終了するには CTRL+C を押してください ...
***end test_sub***
```

親も子も同一プロセスで実行され、制御は親に戻ってこない。
これはあんまり使いどころが無さそうです。

### call

```bat:test_main.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set var_main=aaa
set var_sub=

echo ---call
call test_sub.bat xxx yyy 
echo err: %errorlevel%
echo var_main: %var_main%
echo var_sub:  %var_sub%
echo ---end
```

```bat:test_sub.bat
echo ***begin test_sub***
set var_sub=bbb

echo var_main: %var_main%
echo var_sub:  %var_sub%

echo arg1: %1
echo arg2: %2

timeout /t 5 /nobreak
echo ***end test_sub***

exit /b 2
```

```xxx:test_main.bat実行結果
---call
***begin test_sub***
var_main: aaa
var_sub:  bbb
arg1: xxx
arg2: yyy

0 秒待っています。終了するには CTRL+C を押してください ...
***end test_sub***
err: 2
var_main: aaa
var_sub:  bbb
---end
```

親と子は同一プロセスで実行される。
制御は親に返り、errorlevelでの終了コード判定が可能。
子(test_sub.bat)の最後で、/bオプション無しでexitを発行すると、その時点でプロセス(cmd.exe)が終了してしまうので注意。

### cmd

```bat:test_main.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set var_main=aaa
set var_sub=

echo ---cmd
cmd /c test_sub.bat xxx yyy
echo err: %errorlevel%
echo var_main: %var_main%
echo var_sub:  %var_sub%
echo ---end
```

```bat:test_sub.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

echo ***begin test_sub***
set var_sub=bbb

echo var_main: %var_main%
echo var_sub:  %var_sub%

echo arg1: %1
echo arg2: %2

timeout /t 5 /nobreak
echo ***end test_sub***

exit /b 2
```

```xxx:test_main.bat実行結果
---cmd
***begin test_sub***
var_main: aaa
var_sub:  bbb
arg1: xxx
arg2: yyy

0 秒待っています。終了するには CTRL+C を押してください ...
***end test_sub***
err: 2
var_main: aaa
var_sub:
---end
```

親と子は別プロセスで実行される。
親で設定した変数は子に引き継がれるが、子で設定した変数は親に引き継がれない。
親で指定した@echo offは子に引き継がれないので、子でも@echo offを指定する必要がある。
制御は親に返り、errorlevelでの終了コード判定が可能。
子の最後で、/bオプション無しでexitを発行しても挙動は同じ。

### start

```bat:test_main.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set var_main=aaa
set var_sub=

echo ---start
start test_sub.bat xxx yyy
echo err: %errorlevel%
echo var_main: %var_main%
echo var_sub:  %var_sub%
echo ---end
```

```bat:test_sub.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

echo ***begin test_sub***
set var_sub=bbb

echo var_main: %var_main%
echo var_sub:  %var_sub%

echo arg1: %1
echo arg2: %2

timeout /t 5 /nobreak
echo ***end test_sub***

exit 2
```

```xxx:test_main.bat実行結果
---start
err: 0
var_main: aaa
var_sub:
---end
```

```xxx:test_main.bat実行結果(別ウィンドウ)
***begin test_sub***
var_main: aaa
var_sub:  bbb
arg1: xxx
arg2: yyy

0 秒待っています。終了するには CTRL+C を押してください ...
***end test_sub***
```

親と子は別プロセスで実行される。
親で設定した変数は子に引き継がれるが、子で設定した変数は親に引き継がれない。
親で指定した@echo offは子に引き継がれないので、子でも@echo offを指定する必要がある。
callやcmdとは異なり、非同期で子のバッチが実行される。親のバッチは子の終了を待たずに後続処理を実行する。そのため子の結果は親に戻らない。
子の最後で、/bオプション付きでexitを発行すると、派生した別ウィンドウ(cmd.exeプロセス)が残り続けてしまう。/bオプション無しでexitを発行すると子ウィンドウ(子プロセス)も終了する。

###start /b

```bat:test_main.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set var_main=aaa
set var_sub=

echo ---start
start /b test_sub.bat xxx yyy
echo err: %errorlevel%
echo var_main: %var_main%
echo var_sub:  %var_sub%
echo ---end
```

```bat:test_sub.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

echo ***begin test_sub***
set var_sub=bbb

echo var_main: %var_main%
echo var_sub:  %var_sub%

echo arg1: %1
echo arg2: %2

timeout /t 5 /nobreak
echo ***end test_sub***

exit 2
```

```xxx:test_main.bat実行結果
c:\temp\batch_test>test_main.bat
---start /b
err: 0
var_main: aaa
var_sub:
---end
c:\temp\batch_test>***begin test_sub***
var_main: aaa
var_sub:  bbb
arg1: xxx
arg2: yyy

0 秒待っています。終了するには CTRL+C を押してください ...
***end test_sub***
```

別ウィンドウが開かないだけで、start(/bオプション無し)と挙動は同じ。
親と子は別プロセスで実行される。
親で設定した変数は子に引き継がれるが、子で設定した変数は親に引き継がれない。
親で指定した@echo offは子に引き継がれないので、子でも@echo offを指定する必要がある。
callやcmdとは異なり、非同期で子のバッチが実行される。親のバッチは子の終了を待たずに後続処理を実行する。そのため子の結果は親に戻らない。
子の最後で、/bオプション付きでexitを発行すると、派生した別cmd.exeプロセスが残り続けてしまう。/bオプション無しでexitを発行すると子プロセスも終了する。

### バッチ呼び出しのまとめ
<同期的な呼び出し>
親子とも同一プロセスで実行させたい場合: call
親子でプロセスを分けて実行させたい場合: cmd

<非同期的な呼び出し>
start /b
(プロセスは親子で分かれる)

<注意>
子バッチは、呼び出し方に応じて終了のさせ方(exitの/bオプション有無)を意識しておかないと、意図せずプロセスが終了したりあるいはゴミプロセスが残ってしまったりします。
どんな呼び出し方法でもOKなように汎用的に作れるといいのだが、どうも無理そうなんだよなぁ(調べるの疲れたからあきらめた)。


## サブルーチン・コール
call文と使うと同一バッチ・ファイル内のラベルを呼び出すことができます。

```bat:test_main.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set var_main=aaa
set var_sub=

echo ---call label
call :label01 xxx yyy
echo err: %errorlevel%
echo var_main: %var_main%
echo var_sub:  %var_sub%
echo ---end

goto end


:label01
	echo ***begin test_sub***
	set var_sub=bbb

	echo var_main: %var_main%
	echo var_sub:  %var_sub%

	echo arg0: %0
	echo arg1: %1
	echo arg2: %2
	echo arg3: %3

	timeout /t 5 /nobreak
	echo ***end test_sub***
	
	exit /b 2

:end
```

```xxx:実行結果
c:\temp\batch_test>.\test_main.bat 111 222 333
---call label
***begin test_sub***
var_main: aaa
var_sub:  bbb
arg0: :label01
arg1: xxx
arg2: yyy
arg3:

0 秒待っています。終了するには CTRL+C を押してください ...
***end test_sub***
err: 2
var_main: aaa
var_sub:  bbb
---end
```

引数も渡せるし、サブルーチンのようにラベルを呼び出すことができました。
親を実行する時の引数と、callでサブルーチンを呼ぶ時の引数もきちんと区別されてます。

# ファイル操作
## for文
繰り返し処理の所でも書きましたが、Windowsバッチのfor文はどちらかというとファイル操作で扱うことを主目的としているような感じがします。for文のバリエーションはいくつかありますが、ここでは以下の2ケースについて記載します。

### 特定フォルダにあるファイル名を取得
特定のディレクトリ下にあるファイル全てに対してなんらかの処理を行う、というような場合に利用できます。

基本形:
for %%<変数> in (<ファイルセット>) do コマンド
※変数はアルファベット一文字
※ファイルセットは対象とするファイル名(ワイルドカード使用可)
※/rオプションを指定すると、特定のディレクトリを指定可能となり(省略時はカレント・ディレクトリ)、サブ・ディレクトリ以下のファイルも操作対象となる。また、変数に返される結果はフルパスとなる(先に示したバッチパラメーターの指定(~nxみたいなやつ)が可能)。

```bat:
echo --- all files in current dir ---
for %%i in (*) do (
	echo %%i
)
echo --- bat files in current dir ---
for %%i in (*.bat) do (
	echo %%i
)
echo --- bat files in current dir and sub dir ---
for /r %%i in (*.bat) do (
	echo %%i
)
echo --- all files in specific folder ---
for /r .\folder01 %%i in (*) do (
	echo %%~nxi
)
```

```xxx:実行結果
--- all files in current dir ---
memo.txt
test.bat
test2.bat
test3.bat
test_main.bat
test_sub.bat
--- bat files in current dir ---
test.bat
test2.bat
test3.bat
test_main.bat
test_sub.bat
--- bat files in current dir and sub dir ---
c:\temp\batch_test\test.bat
c:\temp\batch_test\test2.bat
c:\temp\batch_test\test3.bat
c:\temp\batch_test\test_main.bat
c:\temp\batch_test\test_sub.bat
c:\temp\batch_test\folder01\aaa.bat
--- all files in specific folder ---
aaa.bat
test.txt
```


### ファイルの中身を読み込む

ファイルの中身を読んで、各行毎に繰り返し処理を行うような場合に利用できます。

基本形:
for /f <オプション> %%<変数> in (<ファイル名>) do コマンド
※変数はアルファベット一文字
※ファイルセットは対象とするファイル名(ワイルドカード使用可)


```csv:list.csv
Name,DeptCode,Birthday,Phone,address
Tanaka Ichro,A001,1980/03/04,1111,Tokyo
Suzuki Jiro,B002,1990/10/20,2222,Chiba
Satoh Saburo,C003,1985/05/15,3333,Kanagawa
```

```bat:
for /f "skip=1 delims=, tokens=1,2,3* usebackq" %%a in ("list.csv") do (
	echo -----
	echo Name: %%a
	echo DeptCode: %%b
	echo Birthday: %%c
	echo etc: %%d
)
```

```xxx:実行結果
-----
Name: Tanaka Ichro
DeptCode: A001
Birthday: 1980/03/04
etc: 1111,Tokyo
-----
Name: Suzuki Jiro
DeptCode: B002
Birthday: 1990/10/20
etc: 2222,Chiba
-----
Name: Satoh Saburo
DeptCode: C003
Birthday: 1985/05/15
etc: 3333,Kanagawa
```

オプション補足

* skip: スキップする行数(上の例では読み込み対象のcsvファイルの先頭行がヘッダー行なので1行読み飛ばしている)
* delims: 区切り文字(デリミッタ)。上の例ではcsv形式を想定しているのでカンマ(,)を区切り文字として指定。(省略時はブランクorTabが区切り文字となる)
* tokens: 区切り文字で区切られた列のうち、どの列を取得するかを指定。上の例では、1,2,3列目(元のcsvが3列想定なので全列相当)を取得します。各列は変数に指定されたアルファベットから順番に割り当てられます(1列目=>%%a, 2列目=>%%b, 3列目=>%%c)。末尾にアスタリスクを指定すると、それ以降はまるごと1つの列として次の変数に返されます(4列目以降=>%%d)。
* usebackq: ファイル名をダブルクォーテーションでくくることができます。ブランクを含むディレクトリー名/ファイル名を想定した場合、このオプションを指定しておくと汎用性が高まります。

## ファイルへのリダイレクト
これは他のプラットフォームとほぼ同様で分かりやすい。

標準出力のリダイレクト/新規作成 
(既存ファイルがあれば内容はクリアされて新たに作成される)

```
コマンド > ファイル名
```

標準出力のリダイレクト/追記
(既存ファイルがあれば追記。なければ新規作成)

```
コマンド >> ファイル名
```

標準エラー出力のリダイレクト/新規作成

```
コマンド 2> ファイル名
```

標準エラー出力のリダイレクト/追記

```
コマンド 2>> ファイル名
```

標準出力&標準エラー出力のリダイレクト

```
コマンド > ファイル名1 2> ファイル名2
```

標準出力&標準エラー出力の同一ファイルへのリダイレクト

```
コマンド >> ファイル名 2>&1
```

例:


```bat:
set logfile=test.log
echo %date% %time% --- begin --- > %logfile%
aaa >> %logfile% 2>&1
echo %date% %time% --- end --- >> %logfile%
```

```xxx:実行結果(test.log)
2016/08/13 20:59:09.72 --- begin ---
'aaa' は、内部コマンドまたは外部コマンド、
操作可能なプログラムまたはバッチ ファイルとして認識されていません。
2016/08/13 20:59:09.74 --- end ---
```

# コマンド実行結果の変数への代入
バッチ中でコマンド実行結果を変数に代入したい場合、for文を利用した方法が使えます。
上のファイル操作で実施したfor文でファイル名を指定している部分にコマンドを指定してあげると、ファイルを読み取る場合と同じように結果を1行ごとに変数で受取れます。
一旦コマンド結果をファイルに書き出してそれをfor文で読む、ということでもよいですが、それをファイルを介さずに一発でできるイメージです。

基本形:
for /f <オプション> %%<変数> in (\`コマンド\`) do ...
※変数はアルファベット一文字
※結果を取得したいコマンドはバッククウォートでくくります

コマンド結果が1行しかない場合の例:

```bat:getHostname.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

set myHostName=

for /f "usebackq" %%a in (`hostname`) do (
    set myHostName=%%a
)

echo myHostName: %myHostName%
```

```xxx:実行結果
c:\tmp\batch>getHostname.bat
myHostName: piyo
```
ここでは`hostname`コマンドの結果をmyHostNameにセットしています。


コマンド結果が複数行ある場合の例:
例えばtasklist /vコマンドの結果を取得することを想定します。


```xxx:tasklist出力例
c:\tmp\batch>tasklist /v
イメージ名                     PID セッション名     セッション# メモリ使用量 状態            ユーザー名                                             CPU 時間 ウィンドウ タイトル
========================= ======== ================ =========== ============ =============== ================================================== ============ ========================================================================
System Idle Process              0 Services                   0         24 K Unknown         NT AUTHORITY\SYSTEM                                  6254:33:30 N/A
System                           4 Services                   0      4,160 K Unknown         N/A                                                     1:03:07 N/A
smss.exe                       428 Services                   0        960 K Unknown         NT AUTHORITY\SYSTEM                                     0:00:00 N/A
csrss.exe                      496 Services                   0      8,380 K Unknown         NT AUTHORITY\SYSTEM                                     0:02:06 N/A
wininit.exe                    540 Services                   0      5,296 K Unknown         NT AUTHORITY\SYSTEM                                     0:00:00 N/A
csrss.exe                      552 RDP-Tcp#0                  1     17,736 K Not Responding  NT AUTHORITY\SYSTEM                                     0:00:13 N/A
services.exe                   588 Services                   0      9,932 K Unknown         NT AUTHORITY\SYSTEM                                     0:30:02 N/A

...

notepad.exe                   3284 RDP-Tcp#0                  1      9,308 K Running         PIYO\Administrator                                      0:00:00 test01.txt - メモ帳
notepad.exe                   4244 RDP-Tcp#0                  1      9,324 K Running         PIYO\Administrator                                      0:00:00 test02.txt - メモ帳
WmiPrvSE.exe                  4272 Services                   0      8,448 K Unknown         NT AUTHORITY\NETWORK SERVICE                            0:00:00 N/A
tasklist.exe                  4676 RDP-Tcp#0                  1      6,456 K Unknown         PIYO\Administrator                                      0:00:00 N/A
```

このうち、notepad.exeの部分だけを抽出すると...

```xxx:tasklistからnotepad.exe部分のみ抽出
c:\tmp\batch>tasklist /v | find "notepad.exe"
notepad.exe                   3284 RDP-Tcp#0                  1      9,308 K Running         PIYO\Administrator                                      0:00:00 test01.txt - メモ帳
notepad.exe                   4244 RDP-Tcp#0                  1      9,332 K Running         PIYO\Administrator                                      0:00:00 test02.txt - メモ帳
```

この結果をバッチでハンドリングしてみます。

```bat:getNotepadProcessInfo.bat
@echo off
setlocal enabledelayedexpansion
cd %~dp0

for /f "usebackq tokens=1,2,3,4,5,6,7,8,9*" %%a in (`tasklist /v ^| find "notepad.exe"`) do (
	set ImageName=%%a
	set PID=%%b
	set SessionName=%%c
	set SessionNumber=%%d
	set MemorySize=%%e
	set MemoryUnit=%%f
	set Status=%%g
	set UserName=%%h
	set CPUTime=%%i
	set WindowTitle=%%j

	echo ImageName: !ImageName! / PID: !PID! / WindowTitle: !WindowTitle!

)
```

```xxx:実行結果
c:\tmp\batch>getNotepadProcessInfo.bat
ImageName: notepad.exe / PID: 3284 / WindowTitle: test01.txt - メモ帳
ImageName: notepad.exe / PID: 4244 / WindowTitle: test02.txt - メモ帳
```

ここでは、単純な例として必要なフィールドのみ出力させています。
バッチ中のtasklistコマンドで、パイプ(|)を指定していますが、これはエスケープさせる必要があるので直前にキャレット(^)を挿入しています。


# おまけ
[Windowsバッチまとめ 補足: バッチで出来ないことを他の仕組みで補う](http://qiita.com/tomotagwork/items/5a0e418ceca9b816df51)
[Excelマクロをバッチから実行する](http://qiita.com/tomotagwork/items/4a5927142ee4b939c4cd)

