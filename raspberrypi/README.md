# Raspbian Usage

ユーザー名は「pi」、パスワードは「izumissh1」です。

## 日本語入力のやり方

- https://www.ratocsystems.com/products/triple_r/blog/?x=entry:entry200521-092107
- https://www.indoorcorgielec.com/resources/raspberry-pi/raspberry-pi-input-japanese/

## VSCode

- https://code.visualstudio.com/docs/setup/raspberry-pi

インストール方法は`sudo apt install code`です。`sudo apt upgrade code`で更新がないか確認してください。

## ログインできない

電源を入れた時にパスワードを求められるが、正しいものを入力してもログインできないときに見てください。

参考: https://www.raspberrypi.org/forums/viewtopic.php?t=180859

1. 「Ctrl + Alt + F1」で仮想ターミナルを開き、以下のコマンドを入力していきます。
2. `sudo chown pi.pi ~pi/.Xauthority`
3. `sudo dpkg-configure lightdm`
4. `reboot`

## Arduino

- https://make.kosakalab.com/make/electronic-work/inst_arduino-ide_raspi/
- https://qiita.com/tamamori/items/7d40bfb73b3a5766ce29

インストール方法は上記URLを見てください。`./install.sh`を`sudo ./install.sh`に変更するとエラーが出なくなります。

開き方は`arduino`コマンドです。

## OpenMV

https://docs.openmv.io/openmvcam/tutorial/software_setup.html#linux-raspberrypi

## ピン接続

- https://gpiozero.readthedocs.io/en/stable/

接続方式|Pythonライブラリ
:-|-:
GPIO|gpiozero
I2C|smbus
UART(Serial)|PySerial

## SSH接続

https://qiita.com/NagaokaKenichi/items/edab135b4118a47c821c
