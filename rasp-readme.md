# Raspbian Usage

ユーザー名は「pi」、パスワードは「izumissh」。

## 左上のメニュー

左端から順に紹介。

1. ユーティリティ。Windowsで「Win」キーを押すと出るメニューのような感じ。
2. Chrome
3. ファイルマネージャ
4. ターミナル

## 右上のメニュー

左端から順に紹介。

1. 現在の入力モード。
    - 「JA」または「A」: 半角英語
    - 「_A」: おそらく半角英語だが、Enterキーで確定しなければならない。
    - 「あ」: 日本語。
2. Bluetoothの管理。
3. Wi-Fiの管理。
4. 音の大きさの管理。
5. 時刻。クリックするとカレンダーが表示される。

## 日本語入力のやり方

参考: https://www.ratocsystems.com/products/triple_r/blog/?x=entry:entry200521-092107

1. 画面右上の「JA」ボタンを押す。
2. 「日本語 - Mozc」を押す。
3. Caps Lockキーで切り替える。「JA」が「あ」に切り替わったら日本語入力可能。

## 英語入力に戻す方法

1. Caps Lockキーで入力モードを「_A」に切り替える。
2. 半角/全角キーを押す。

## VSCode

### 開き方

1. ターミナルを開く。
2. `code-oss`と入力。エイリアスを設定してあるので、`code`でも可。

### インストール方法

https://qiita.com/optimisuke/items/1cd7440442f7420e6b99

## ログインできない

電源を入れた時にパスワードを求められるが、正しいものを入力してもログインできないときの対処法。

参考: https://www.raspberrypi.org/forums/viewtopic.php?t=180859

1. 「Ctrl + Alt + F1」で仮想ターミナルを開く。以下、書かれているコマンドを入力していく。
2. `sudo chown pi.pi ~pi/.Xauthority`
3. `sudo dpkg-configure lightdm`
4. `reboot`

## Arduino

### 開き方

1. ターミナルを開く。
2. `arduino`

### IDEのインストール方法

参考: https://make.kosakalab.com/make/electronic-work/inst_arduino-ide_raspi/

基本的には上記URLに従う。`./install.sh`を`sudo ./install.sh`に変更するとエラーが出なくなる。
