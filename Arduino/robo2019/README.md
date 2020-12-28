<!-- 必ずVSCodeで開き、Ctrl+Shift+Vでプレビューを開くこと -->

# robo2019

ロボカップ用に作ったArduinoライブラリです。前提条件として、機体のモーターの位置、番号、向き、そしてロボットの中心を原点とした相対座標系について、極形式の角度は次の写真のようになっているものとします。

![machine-info.jpeg](./img/machine-info.jpeg)

`#include <robo2019.h>`でインクルードして下さい。機能は全て`robo`ネームスペースに格納されます。

## util.h

ライブラリ全体で共有するユーティリティを集めました。

`namespace string`

文字列関連の機能群です。Pythonの`str`クラスに似せて作りました。

`String string::rjust(const String &target, uint8_t width, const char &padding)`

`target`に与えられた文字列を長さ`width`に左寄せした文字列を返します。余白には`padding`に与えられた文字が使われます。例: `robo::string::rjust("Hello", 10, '+')`は`"+++++Hello"`を返します。`padding`は`char`型であることに注意して下さい。

## vec2d.h

`Vector2D<T>`

自作のベクトル型です。テンプレート引数の`T`は算術型(`int`, `double`など)である必要があります。

コンストラクタの一覧です。

* Vector2D

演算子の実装は以下の通りです。

## motor


