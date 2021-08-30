# HandsOn

出村先生の講習会の宿題についてまとめておきます。

## コマンドライン

宿題を達成する上で避けては通れないのがコマンドラインです。コマンドラインはシェルとも呼ばれ、文字列を入力してコンピュータと対話(命令を与える)ができます。この対話方式はCUIと呼ばれています。

Windowsでのシェルの開き方は、画面左下の検索ボックスで「pwsh」または「cmd」と入力、returnです。pwshと入力するとPowerShell、cmdと入力するとコマンドプロンプトが開きます。どちらもシェルの一種です。途中で「管理者としてPowerShellを開く」という場面があるので、普段からPowerShellを使うことをおすすめします。

Macでのシェルの開き方は、Finderで アプリケーション > ユーティリティ と進み、その中の「ターミナル」というアプリです。

Linuxでの開き方は、`>_`みたいなアイコンのやつです(よくわかってない)。
WSLでは少し事情が違います。それについては後述します。

## Windows Subsystem for Linux (WSL)

参考:
https://docs.microsoft.com/ja-jp/windows/wsl/install-win10
https://docs.microsoft.com/en-us/windows/wsl/wsl2-kernel

Windows Subsystem for Linux(以下WSL)とは、Windows内でLinuxの仮想マシンを動かせるようにする機能です。ここではUbuntuのインストールまで紹介します。
もちろんですが、WSLのインストールはWindowsのみです。MacにLinuxを入れる方法については後述します。

最初に、Windowsのバージョンを最新のものに更新します。[Windows更新アシスタントを入手](https://www.microsoft.com/software-download/windows10)して、更新を行ってください。

"Linux 用Windowsサブシステム" オプション機能を有効にする必要があります。管理者としてPowerShellを開き、以下を実行します。

```
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

次にWSLのバージョンを2に更新します。"仮想マシン プラットフォーム" オプション機能を有効にする必要があります。

```
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

実行後、Windowsを再起動してください。

次にWSL 2で使用するLinuxカーネルをコンピューターにインストールします。最新のWSL2 Linux kernelを[こちら](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)からダウンロードします。リンクを押すとダウンロードが開始します。ダウンロード後にファイルを開きます。色々と許可が求められますが、全部許可してください。

次に、WSLの既定のバージョンを2に変更します。管理者としてPowerShellを開いて次のコマンドを実行します。

```
wsl --set-default-version 2
```

次に、Linuxディストリビューションをインストールします。[Microsoft Store](https://aka.ms/wslstore)を開き、希望するLinuxディストリビューションを選択します。Ubuntu 18.04のリンクを貼っておきます。
https://www.microsoft.com/store/apps/9N9TNGVNDL3Q

インストール後に起動するとコンソールウィンドウが開き、セットアップが自動で行われます。[新しいLinuxディストリビューションのユーザーアカウントとパスワードを作成する](https://docs.microsoft.com/ja-jp/windows/wsl/user-support)必要があります。Ubuntuの場合、ユーザーパスワードを打っても画面には表示されないので注意してください。パスワードはUbuntu内で色々とインストールする際に使います。

※surface内のUbuntuではユーザー名を`robo`、パスワードを`izumissh`にしました。

これでWSL及びUbuntuのインストールは完了です。

次に、Ubuntuに対応するWSLのバージョンを2にします。まずはUbuntuのバージョンを確認します。PowerShellで以下のコマンドを実行します。

```
wsl --list --verbose
```

インストール済みのLinuxディストリビューションとそのステージ、バージョンの一覧が表示されます。`Ubuntu-18.04`のバージョンが`1`となっている場合は以下のコマンドを実行します。

```
wsl --set-version Ubuntu-18.04 2
```

これで準備完了です。念のため一度再起動しておいて下さい。

コマンドラインで`wsl`を実行するとLinuxに接続します。あくまでCUIでの使用になるので、Linuxの実機に触れるときとは全く異なる使用方法になります。

## Linux(Mac)

参考:
https://karaage.hatenadiary.jp/entry/2017/03/30/073000

MacでLinuxを使用するために、仮想マシンをMac内に作成します。
「このアプリを開けません」みたいなアラートが何度か表示されますが、設定を変更するなどして通してあげてください。何度か管理者権限が求められます。全部許可してください。ターミナルでパスワードを打つ場合、どこまで打ったか画面に表示されないので注意してください。

まずは[Homebrew](https://qiita.com/zaburo/items/29fe23c1ceb6056109fd)というパッケージ管理システムをインストールします。ターミナルで以下のコマンドを実行します。

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```

次に、[virtualbox](https://eng-entrance.com/virtualbox-install)というmac内に仮想マシンを作るツールをインストールします。ターミナルで以下のコマンドを実行します。

```
brew cask install virtualbox
```

しばらくコマンドラインではすることがないので、別のインストールをします。次の「Ubuntuのイメージファイルを~」のところに進んでください。
インストールが終わったらコマンドラインで`virtualbox`と実行して、ペンギンみたいなのがいるグラフィックが表示されたらインストール成功です。

次に、Ubuntuのイメージファイルをインストールします。[こちらのサイト](https://www.ubuntu.com/download/alternative-downloads)を開き、少しスクロールしたところにある「Ubuntu 18.04.4 Desktop (64-bit)」を選択、ダウンロードします。`~.iso.torrent`みたいな感じのファイルがダウンロードされます。

次はこれを`~.iso`に変換します。[BitTorrent](https://www.bittorrent.com/ja/)というツールを使用します。上記のサイトを開き、「無料ダウンロード」を選択してダウンロードします。ダウンロードしたものを開き、メニューから「BitTorrent Web」の上にある大きめのアイコンをダブルクリックします。ブラウザが立ち上がって黒基調の画面が表示されます。右上の「トレントを追加」とある紫のボタンを押し、ダウンロードした`~.iso.torrent`のファイルを選択します。`~.iso`への変換が始まります。状態が「シード中」に変わったらダウンロード終了です。

virtualboxのインストール、`~.iso`への変換が完了したら、とうとう仮想マシンを作成します。文字のみの説明となりますが、実際の画面の状態が見たければ、[こちら](https://qiita.com/komakomako/items/1f1fa0e2279895006598)なんかをどうぞ。
コマンドラインで`virtualbox`と実行してvirtualboxを開き、「新規(N)」を選択します。まずは名前とOSを聞かれます。名前は「Ubuntu」、OSはUbuntu(64-bit)とします。次にメモリサイズを聞かれます。デフォルトでは1024MBですが、高速化のため4096MBにします。仮想ハードディスクを追加するか作成するか聞かれます。デフォルトのまま(仮想ハードディスクを作成)でOK。ハードディスクのファイルタイプについて聞かれます。デフォルト。ファイルの場所とサイズについて聞かれます。デフォルト。これで仮想マシンが作成されます。
早速その仮想マシンを起動します。Ubuntuのイメージファイルを聞かれるので、フォルダアイコンをクリックして`~.iso`を選択し、Startボタンを押します。次に、突然アラートっぽい画面が表示されます。「Capture」を選ぶと仮想マシンのウィンドウ内でしか操作ができなくなるので、「Cancel」を選びましょう。
セットアップ画面が登場します。左側にある言語リストから「日本語」を選択します。画面右側の「install Ubuntu」を選択して次に進みます。
次の画面ではノーマルインストールか、ミニマルインストールかを聞かれます(画面のオプション名は忘れました)。目的はrosの使用だけ(らしい)なので、ミニマルインストールの方でも事足ります。容量に不安がある人はそっちを選んでください。
次の画面で「ディスクを削除して~」といったのが出てきますが、これはMacが仮想マシンに割り当てた領域を削除するという意味です。何も変更せずに次に進みます。
住んでいる地域を選びます。「Kanazawa」はないので「Tokyo」にします。
ユーザー名、マシン名、パスワードを聞かれます。好きなように設定してください。パスワードはUbuntu内で色々とインストールする際に使います。
少し待つと再起動が求められるので、再起動します。これでインストールは完了です。

仮想マシン内でシェルを開くには、画面左下の点が並んだアイコンをクリックし、そこから`>_`みたいなアイコンのやつを探してください。見つからない場合は、下の「常用/全て」が「常用」になっていると思います。「全て」に変更してから探してください。

## ROS Melodic

参考:
https://demura.net/robot/16518.html
http://wiki.ros.org/melodic/Installation/Ubuntu

ROSのインストールについて、公式サイトを参考にまとめておきます。基本的に公式サイトの内容をコピペしただけなので、何をしているのか筆者もわかってないところがあります。
以下に示すコマンドは全てUbuntuのコマンドラインで実行してください。

packages.ros.orgからのソフトウェアを受け入れるようにコンピューターをセットアップします。

```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main"> /etc/apt/sources.list.d/ros-latest.list'
```

次に、キーを設定(?)します。

```
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
```

Debianパッケージインデックスが最新であることを確認します。

```
sudo apt update
```

ROSのライブラリ、ツールをインストールします。

```
sudo apt install ros-melodic-desktop-full
```

新しいシェルが起動するたびにROS環境変数がbashセッションに自動的に追加されるようにします。

```
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

色々とインストールします。

```
sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
```

rosdepをインストール、初期化します。

```
sudo apt install python-rosdep
sudo rosdep init
rosdep update
```

終わり。

## Python

参考:
https://www.javadrive.jp/python/install/index1.html

https://www.python.org/
このサイトを開き、Downloadsメニューから使っているパソコンのOSを選択します。バージョンの選択肢が表示されるので、選択肢の上部にある"Latest Python 3 Release - Python 3.8.5"を選択、ダウンロードします。
ダウンロードしたものを開き、セットアップを行います。ウィンドウ下部にある"Add Python 3.8 to PATH"にチェックを入れて下さい(この操作は多分Windowsだけですが、他のOSで似たようなものがあったらチェックを入れて下さい)。
"Install Now"を押して管理者権限を渡したらインストールが行われます。完了したらインストーラは閉じても大丈夫です。

コマンドラインで`python3`(Windowsは`python`)と実行して`>>> `が出てきたらインストール成功です。この機能はREPL(Read Evaluate Print Loop)というもので、簡単なPythonの実験ができます。閉じ方は`exit()`です。

Pythonの入門には[Python tutorial](https://docs.python.org/ja/3/tutorial/index.html)の[3. 形式ばらないPythonの紹介](https://docs.python.org/ja/3.8/tutorial/introduction.html)からがおすすめです。
