# Installation

この記事ではVSCode, Arduinoなどのインストール方法について紹介します。

## 目次

* VSCode
* Arduino
* Processing
* Windows Subsystem for Linux (WSL)
* Linux(Mac)
* Python

Linuxのインストール(WSL, Mac)ではUbuntuを入れます。

## VSCode



## Arduino

## Processing

## Windows Subsystem for Linux (WSL)

参考: 
https://docs.microsoft.com/ja-jp/windows/wsl/install-win10
https://docs.microsoft.com/en-us/windows/wsl/wsl2-kernel

Windows Subsystem for Linux(以下WSL)とは、Windows内でLinuxの仮想マシンを動かせるようにする機能です。ここではUbuntuのインストールまで紹介します。

まずは"Linux 用Windowsサブシステム" オプション機能を有効にする必要があります。管理者としてPowerShellを開き、以下を実行します。

```PowerShell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

次にWSLのバージョンを2に更新します。[最新のWindowsバージョンに更新](ms-settings:windowsupdate)してください。[Windows更新アシスタントを入手する](https://www.microsoft.com/software-download/windows10)。"仮想マシン プラットフォーム" オプション機能を有効にする必要があります。管理者としてPowerShellを開き、以下を実行します。

```PowerShell
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

実行後、Windowsを再起動してください。

次にWSL 2で使用するLinuxカーネルをコンピューターにインストールします。最新のWSL2 Linux kernelを[こちら](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)からダウンロードします。リンクを押すとダウンロードが開始します。リンクが古くなっている可能性があるので、 https://docs.microsoft.com/en-us/windows/wsl/wsl2-kernel を確認してください。最終更新日: 2020年8月9日
ダウンロード後にファイルを開きます。色々と許可が求められますが、全部許可してください。

次に、WSLの既定のバージョンを2に変更します。管理者としてPowerShellを開いて次のコマンドを実行します。

```PowerShell
wsl --set-default-version 2
```

次に、Linuxディストリビューションをインストールします。[Microsoft Store](https://aka.ms/wslstore)を開き、希望するLinuxディストリビューションを選択します。Ubuntu 18.04のリンクを貼っておきます。
https://www.microsoft.com/store/apps/9N9TNGVNDL3Q

インストール後に起動するとコンソールウィンドウが開き、セットアップが自動で行われます。[新しいLinuxディストリビューションのユーザーアカウントとパスワードを作成する](https://docs.microsoft.com/ja-jp/windows/wsl/user-support)必要があります。Ubuntuの場合、ユーザーパスワードを打っても画面には表示されないので注意してください。

これでWSL及びUbuntuのインストールは完了です。使い方は適当にググって下さい。

## Linux(Mac)

参考:
https://karaage.hatenadiary.jp/entry/2017/03/30/073000

基本的にターミナルで作業を行います。ターミナルの開き方は ファインダー > 「ターミナル」と検索 です。「このアプリを開けません」みたいなアラートが何度か表示されますが、設定を変更するなどして通してあげてください。何度か管理者権限が求められます。全部許可してください。ターミナルでパスワードを打つ場合、どこまで打ったか画面に表示されないので注意してください。

まずは[Homebrew](https://qiita.com/zaburo/items/29fe23c1ceb6056109fd)というパッケージ管理システムをインストールします。ターミナルで以下のコマンドを実行します。

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```

次に、[virtualbox](https://eng-entrance.com/virtualbox-install)というmac内に仮想マシンを作るツールをインストールします。ターミナルで以下のコマンドを実行します。

```
brew cask install virtualbox
```



## Python

参考:
https://www.javadrive.jp/python/install/index1.html

https://www.python.org/
このサイトを開き、Downloadsメニューから使っているパソコンのOSを選択します。バージョンの選択肢が表示されるので、選択肢の上部にある"Latest Python 3 Release - Python 3.8.5"を選択、ダウンロードします。
ダウンロードしたものを開き、セットアップを行います。ウィンドウ下部にある"Add Python 3.8 to PATH"にチェックを入れて下さい(この操作は多分Windowsだけですが、他のOSで似たようなものがあったらチェックを入れて下さい)。
"Install Now"を押して管理者権限を渡したらインストールが行われます。
