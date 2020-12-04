---
title: 【bat】Windowsのバッチファイル(*.bat)の書き方自分用まとめ
tags: bat batch バッチ バッチファイル
author: sksmnagisa
slide: false
---
#Windowsのバッチファイル(*.bat)の書き方自分用まとめ
#概要
拡張子が*.batのアレの書き方。よく忘れるのでまとめておく。


#bat実行時にスクリプトの中身をコマンドプロンプトに表示しない
例えば次のようなバッチファイルがあるとする

```bat:exsample.bat
IF 1==1 (
    echo あいうえお
)
```

これを実行すると次のような残念な表示になる

> C:>C:\exsample.bat
>
> C:\>IF 1 == 1 (echo あいうえお )
> あいうえお

ようはスクリプトの中身が表示されてる。これを避けるためにバッチファイルの頭には必ず@echo offを入れるのが定石。

```bat:exsample.bat
@echo off
IF 1==1 (
    echo あいうえお
)
```

実行結果

> C:>C:\exsample.bat
> あいうえお

#コメント
標準だとコメントはremコマンドを利用する

```bat:exsample.bat
@echo off
rem コメントだよ
```

ただし:を使う方法もある。
:はGOTOで飛ぶラベル名なんだけどGOTO無ければ無視できるからコメントに使えるっていう裏ワザ的なアレ。

```bat:exsample.bat
@echo off
: コメントではないけどコメントだよ
```

#スクリプトが置かれている場所をカレントディレクトリにする

```bat
cd /d %~dp0
```

全てのバッチファイルの先頭にこれ書いても良いレベルでよく使う。

```bat
@echo off
cd /d %~dp0
```

大体ここまで常にテンプレな気がする。

#変数(静的変数)
##概要
変数は環境変数を用いる。
また変数は１度定義すると変更が効かない。
これを変更する方法があるにはあるけど、
サブルーチン的な話まで読み進めてもらわないと解説できない程面倒くさい方法なので後回しにする。

##スクリプト実行中のみ有効な環境変数
スクリプト実行中のみ有効な環境変数は次のように定義できる。

```bat
set HENSU=AIUEO
```

##変数の中身を参照する
%で括る。
以下例。変数「HENSU」を定義してechoする。

```bat:exsample.bat
@echo off
set HENSU=AIUEO
echo %HENSU%
```

##環境変数の寿命
スクリプト実行中のみ有効な環境変数は別のバッチファイルを呼び出しても寿命が来ない。
例えば次のような2つのバッチファイルがあるとする。

```bat:exsample.bat
@echo off
call TEIGI_AIUEO.bat
echo %HENSU%
```

```bat:TEIGI_AIUEO.bat
set HENSU_A=AIUEO
```

ここで「exsample.bat」を実行すると実行結果は次のようになる。
尚、未解説のコマンド「call」が出てきてるけど、これは別のバッチファイルを呼び出すコマンド。
「call」無しでそのまま「TEIGI_AIUEO.bat」だけ書いても呼び出せるけど、呼び出し元のバッチファイル(この場合はexsample.bat)に処理が返ってこないので意図した動作にならない可能性がある。

> AIUEO

ようは「TEIGI_AIUEO.bat」で定義された変数が「exsample.bat」で参照できている。
自分は初めてバッチを触ったときそれまでスクリプトというものに触れたことが無かったからとても違和感があった。
シェルスクリプトとか触ってる人にとっては当たり前だろって思うかもね。

#IF文

##構文

```
if 条件 ( 処理 )
```

コーディング規約っぽいのが後述されるんだけど()は次の行に書いた方が良いと思う。

```bat
if 条件 (
    処理1
    処理2
    処理3
) else (
    処理1
    処理2
    処理3
)
```

1行の場合は()省略できる。あんまりやってほしくない。

```
if 条件 処理
```

##条件式：文字列検査
環境変数「Configuration」がDebugになっている場合とか。
VCのビルドイベントでたまに使う。

```bat:exsample.bat
@echo off
set Configuration=Debug
if %Configuration%==Debug (
    echo デバッグビルドだ
) else (
    echo リリースビルドだ
)
```

> [ 実行結果 ]
> デバッグビルドだ

##条件式：ファイルの存在
if の後に exist を付ける。

```bat:exsample.bat
@echo off
cd /d %~dp0
if exist exsample.bat (
    echo exsample.batがカレントディレクトリに存在する
) else (
    echo exsample.batがカレントディレクトリに存在しない
)
```

> [ 実行結果 ]
> exsample.batがカレントディレクトリに存在する

##条件式：否定
ifの後にnotを付ける。

```bat:exsample.bat
@echo off
set Configuration=Debug
if not %Configuration%==Debug (
    echo リリースビルドだ
) else (
    echo デバッグビルドだ
)
```

> [ 実行結果 ]
> デバッグビルドだ

if existの場合もnotをifの直後に付ければ良い。
exist以外にも色々あるんだけどとにかくifの直後にnotを付ける。

```bat:exsample.bat
@echo off
cd /d %~dp0
if not exist exsample.bat (
    echo exsample.batがカレントディレクトリに存在しない
) else (
    echo exsample.batがカレントディレクトリに存在する
)
```

> [ 実行結果 ]
> exsample.batがカレントディレクトリに存在する


#コーディング規約
##大文字か小文字か
開発者が複数いるなら統一した方が良いかもしれない。
１人ならまぁお好きなように。というかこのドキュメント自体大文字小文字ごっちゃごちゃ。

##閉じ括弧
ifとforの閉じ括弧だけは別の行にした方が良いと思う。ifならまだしもforはマジで読みづらい。
後()は1行の場合省略可能なんだけど省略しない方が良い。C言語の悪しき習慣感ある。

```bat:exsample.bat
@echo off
IF 1==1 (
    echo こんな感じで()を離してこんな中にコマンド並べる
    echo コマンドコマンド
    echo マンコマンド
    IF 1==1 (
        echo IFの中にIFが入っても見やすいよ
        IF 1==1 (
            echo 見やすいよ
            IF 1==1 (
                rem デバッグ大変になるからあんまり階層化しないで・・・
            )
        )
    )
)
```

#別のバッチファイルを呼び出す

##呼び出し
callを使う。これ以外の方法だと非同期呼び出しになってしまうので悲惨な事件が起こる。

```bat
call 呼び出したいバッチ.bat 引数1 引数2 引数3 ...
```

##バッチの終了
exitを使う。
尚、callはGOTOみたいなもので特定のラベルに飛ぶ場合にも利用する。
そのラベルから戻る際にもexitを使う。

##戻り値を返す(returnなんてものは無い)
returnなんてものは無い。exitを使う。

```bat
exit 0
```

これでゼロを返せる。

尚文字列は返せない。文字列を返したい場合は別途変数を定義する。

```bat:exsample.bat
@echo off
rem 戻り値を定義
RETURN_VALUE=AIUEO
exit /b 0
```

##バッチファイルだけ終了させる
exitはcmd.exeそのものを終了させるコマンドなので、基本的にそのままは使わないと思う。
例えばcallで呼び出されることが前提のバッチファイルだと、呼び出し元のバッチファイルまで終了させるわけには行かないので、
自分自身だけ終了させる必要がある。

この場合「/b」のオプションを指定する。

```bat
exit /b 0
```

##呼び出したバッチの戻り値を確認する
ERRORLEVEL環境変数を見る。

```bat
call test.bat
if %errorlevel% == 1 (
    echo test.batを実行した結果、戻り値として1が返った
)
```

「if errorlevel 1」とすると「ERRORLEVEL環境変数が1以上の場合」という意味になるので、意図と違った動きになる事が多い。


```bat
call test.bat
if errorlevel 0 (          ※1
    echo test.batを実行した結果、戻り値として0が返った
)
if errorlevel 1 (          ※2
    echo test.batを実行した結果、戻り値として1が返った
)
```

上記のコードは戻り値として1が返ってきても実際は「0以上」と「1以上」の両方の条件を満たすため、※1と※2の両方の条件分岐が実行される。

#関数を呼び出す
##関数なんてものは無い
そんなものはない(画像略)

##何があるの
GOTO

##ラベル定義
:で定義。

```bat
:OreOreRaberu
```

##ラベルに飛ぶ

```bat:exsample.bat
@echo off
call :OreOreRaberu
echo AIUEO

:OreOreRaberu
echo OREORE
exit /b 
```

> [実行結果]
> OREORE
> AIUEO
> OREORE

・・・？？？？
最後のOREOREは何だろうっていうと上から順番に実行されるのでちゃんとexitしないとダメよって話。

```bat:exsample.bat
@echo off
call :OreOreRaberu
echo AIUEO
exit /b

:OreOreRaberu
echo OREORE
exit /b 
```

> [実行結果]
> OREORE
> AIUEO

##引数
call時に引数を渡せる。
関数内では渡された引数の１つ目から順に%1,%2,%3,...と割り当てられる。

```bat:exsample.bat
@echo off
call :OreOreRaberu　HIKISU1　HIKISU2　HIKISU3
exit /b

:OreOreRaberu
echo %1
echo %2
echo %3
exit /b
```

> [実行結果]
> HIKISU1
> HIKISU2
> HIKISU3


#動的変数
##正式名称
遅延環境変数。

##nanikore
setによる環境変数の設定は、コマンドプロンプトの実行単位の都合で思った動作にならない場合がある。
例えば次のようなバッチファイル。

```bat:exsample.bat
@echo off
setlocal enabledelayedexpansion
if 1==1 (
	set TEST=AIUEO
	echo %TEST%
	
	set TEST=KAIKUKEKO
	echo %TEST%
)
```

実行する。

> [実行結果]
> ECHO は <OFF> です。
> ECHO は <OFF> です。

「ECHO は <OFF> です。」はechoで何も出力されない場合に表示される。
ようは変数TESTに何も入っていない。
ステートメント単位で実行する影響らしいけど正直よく判らなかった。
とりあえず実行単位の都合で通常のプログラマが想定する期待通りの動作、
すなわちコマンドは1行ずつ解釈され、代入が発生したらそのタイミングで代入した値になるという動作にならないという事。

尚次のように最後にもう一度echoするとKAIKUKEKOと表示される。

```bat:exsample.bat
@echo off
setlocal enabledelayedexpansion
if 1==1 (
	set TEST=AIUEO
	echo %TEST%
	
	set TEST=KAIKUKEKO
	echo %TEST%
)

echo %TEST%
```

実行する。

> [実行結果]
> ECHO は <OFF> です。
> ECHO は <OFF> です。
> KAKIKUKEKO

ステートメントの単位がif全体らしく、ifの中身を全て実行した後にTESTに対する代入が反映されているっぽいけど、
そこまで詳しく知らないしプログラマ的に見て期待通りの動作にならないなら期待通りの動作になる方法を模索した方が有用なので深入りは避けた。

##変数の定義と値変更を期待通りの動作にする遅延環境変数

```bat:exsample.bat
@echo off
setlocal enabledelayedexpansion
if 1==1 (
	set TEST=AIUEO
	echo !TEST!
	
	set TEST=KAIKUKEKO
	echo !TEST!
)
```

実行する。

> [実行結果]
> AIUEO
> KAKIKUKEKO

そうだよ！！これを求めていたんだよ！！

##使い方

> setlocal enabledelayedexpansion

を先頭に記載する。
こうして先頭に記載するテンプレが次のように更新されたのであった...

> @echo off
> cd /d %~dp0
> setlocal enabledelayedexpansion

##遅延環境変数：代入

> set TEST=AIUEO

変わらない

##遅延環境変数：値を参照する

> set TEST=AIUEO
> !TEST!

通常の環境変数は%で括るが、遅延環境変数は!になる。

#ファイルパス操作
##概要
ファイルパスが入っている環境変数からファイル名とか抜いたりする。

##コマンド

> %~nx変数名

この変数名が何か厄介でどうやら引数しかいけないっぽい？ので、例えば次のようなスクリプトは構文エラーになる。

```bat:exsample.bat
@echo off

set FILE_PATH=C:/aaa/bbb.txt
set FILE_NAME=%~nxFILE_PATH%

echo %FILE_PATH%
echo %FILE_NAME%
```

これが色々と不便で、例えばFORループでファイルパスが順番に入ってくるような状況で、
そのファイルパスからファイル名を取得したい場合にどうやってファイル名を取得するのって話になる。

ここで、上記の「%~nx変数名」が引数なら使えることを利用して次のような関数を作る。

```bat:exsample.bat
:basename 
set RESULT_FILENAME=%~nx1
```

これは渡された引数のファイル名を「RESULT_FILENAME」に入れる関数。
これに対してファイルパスを投げつけて、遅延環境変数としてRESULT_FILENAMEにアクセスすればファイル名が取得できる。

#for
##概要
ループ処理。慣れるまですごくつかいづらい

##構文

> for %%１文字の変数名 in (パターン) do (
>     処理1
>     処理2
>     処理3
> )

##動作
1文字変数しか無理。一般的にはiを使うと思う(サンプルがiなので)
Cから入った身としてはiが加算されるのかと思うけどそうではない。

コマンドプロンプトのforはデフォルトの動作としてカレントディレクトリに存在するファイルを全て列挙する。

つまり次のようにすればバッチファイルが存在するディレクトリ内の全てのファイル名をechoする。

```bat:exsample.bat
@echo off
cd /d %~dp0

for %%i in (*) do (
    echo %%i
)
```

##汎用的な利用用途について
/Fオプションを指定する事で、「パターン」に指定された文字列を下位行区切りでforで回してくれる。
これを利用すれば結構いろいろなことが出来る。

例えばこんなんとか。

```bat:exsample.bat
@echo off
cd /d %~dp0

rem ファイル「_temporaryfile」に対してAAA<改行>BBB<改行>CCC<改行>と書き込む
echo AAA > _temporaryfile
echo BBB >>  _temporaryfile
echo CCC >>  _temporaryfile

rem 書き込んだ内容を順に読み込んで表示
for /F %%i in (_temporaryfile) do (
    echo %%i
)
```

> [実行結果]
> AAA
> BBB
> CCC

##コマンドの結果を解析させる
/Fオプションではコマンドの実行結果も渡せる。例えば次のような事が出来る。
コマンドを実行させる場合パターンを「'」で囲む必要がある。

例えばgit statusの実行結果を解析できちゃう。

```bat:exsample.bat
@echo off

for /F %%i in ('git status') do (
    rem １行ずつ取得されるのでここで解析
)
```

ここまで来るとかなり実用的。まぁバッチファイルでこれやらせる必要性が限りなく皆無だけど・・・
（開発体制としてバッチファイルしか使えない場合は仕方なくこれするしかないんだよね・・・）

#gotoとcall
##概要
gotoとcallという似たようなコマンドがある。
どちらもラベルに飛ぶという点は変わらないが、それ以外にいくつか動作が変わる点がある。

##引数
gotoでは引数を渡せない。callは渡せる。

##callの場合はラベルに飛ぶ際にコロンが必要
callはそもそも外部のバッチファイルやexeを叩く等にも利用される為、
バッチファイル内部のラベルに飛ぶ場合にはコロンを付けなければ、ラベルなのかexeを実行したいのか判別できない。

```bat:exsample.bat
@echo off

call :TESTAAA 
exit /b 0

:TESTAAA
echo TESTAAAが呼び出された
exit /b 0
```

> [実行結果]
> TESTAAAが呼び出された

上記の例のように「call :TESTAAA」とラベル名にコロンをつける必要がある。
ここで「call TESTAAA」のようにしてしまうと、「TESTAAAというコマンドが見つからない」と言われてしまう。

対してgotoの場合は用途として「別のラベルに飛ぶ」事が目的なのでコロンを付ける必要が無い。

```bat:exsample.bat
@echo off

goto TESTAAA 
exit /b 0

:TESTAAA
echo TESTAAAが呼び出された
exit /b 0
```

> [実行結果]
> TESTAAAが呼び出された

##exit時の動作の違い
通常のオプション無しのexit、つまり「exit 0」とした場合は、gotoもcallも即座にcmd.exeを終了させる動きになる。
しかし、「/b」オプションを付加した場合は動作が変わる。

callの場合「exit /b 0」するとサブルーチンを抜けるような動作になる。

```bat:exsample.bat
@echo off

call :TESTAAA 
echo TESTAAAから戻ってきた
exit /b 0

:TESTAAA
echo TESTAAAが呼び出された
exit /b 0
```

> [実行結果]
> TESTAAAが呼び出された
> TESTAAAから戻ってきた

しかしgotoの場合は戻って来れない。

```bat:exsample.bat
@echo off

call :TESTAAA 
echo TESTAAAから戻ってきた
exit /b 0

:TESTAAA
echo TESTAAAが呼び出された
exit /b 0
```

> [実行結果]
> TESTAAAが呼び出された

これはgotoがあくまで呼び出しではなく単純な実行する行の移動でしかないことを示している。
バッチファイル内で次に実行する行を変更しただけなのでexit /bした場合そのバッチファイルが終了してしまう。
これがcallの場合は、特定のラベルを別のバッチファイルとして実行しているような動作になる。

戻って来ることが前提の場合call、エラー終了等で飛ばしたまま終了させる場合はgotoといった使い分けになると思う。

#setlocal, endlocal
バッチファイルＡ、バッチファイルＢの２つが存在したとき、
バッチファイルＡからバッチファイルＢを呼び出すと、バッチファイルＢで環境変数がsetされたらバッチファイルＡでもその環境変数を参照できる。

これをできないようにする為に、バッチファイルＢで定義された環境変数をそのバッチファイル内のみ有効にするコマンドが「setlocal」「endlocal」。

Ｃ言語で言えば{}に相当する、ようは変数の寿命。

```bat:exsample.bat
@echo off

setlocal
    rem setlocal、endlocalで挟まれた中で定義した環境変数は、この中でのみ有効
endlocal
```


#その他
ぐぐる。
