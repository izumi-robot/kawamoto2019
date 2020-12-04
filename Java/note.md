---
title: VSCodeでJavaプログラミングを始めてみるメモ(2020-04版)
tags: VSCode Java Java入門
author: msakamoto_sf
slide: false
---
VSCode で Java プログラミングを始めるときの、最初の一歩についてメモです。
2020-04 時点で、以下のバージョンで試しています。

- Windows 10 Pro 日本語版
- AdoptOpenJDK 11 (HostSpot版)
- VSCode 1.44.2

## VSCode のインストール

まず VSCode をインストールします。

- https://code.visualstudio.com/

## JDKのインストール

続いてOpenJDK (Java Development Kit) をインストールします。
2020-04時点では Oracle / OpenJDK公式 / AdoptOpenJDK / RedHat / Azul / AWS / BellSoft など複数ベンダーがそれぞれバイナリパッケージを提供しています。
いろいろな意見があると思いますが、自分の場合は AdoptOpenJDK の LTSバージョン を使うのが無難かな～と思います。
AdoptOpenJDKのサイトから 11 (LTS) をダウンロードしてインストールします。

- https://adoptopenjdk.net/

## Java Extension Pack のインストールと java.home の設定

Microsoft 提供の VSCode 拡張「Java Extension Pack」をインストールします。

- https://marketplace.visualstudio.com/items?itemName=vscjava.vscode-java-pack

VSCode の拡張一覧から Java で検索すれば出てくるので、そこからインストールすれば良いでしょう。

"Extension Pack" なので、複数のJava向け拡張が一度にインストールされます。
少し時間がかかりますので、お茶でも飲みつつ気長に待ちましょう。

インストールが終わったら、 VSCode にJDKの場所を登録します。
File -> Preferences -> Settings で User 設定で `java.home` を検索し、インストールしたJDKのディレクトリを設定します。

```
(例)
"java.home": "C:\\work\\jdk\\win-x64\\adopt-openjdk-hs-11.0.6_10",
```

JDKのフォルダはどこまで指定すれば良いのか？ですが、binディレクトリの一つ上を指定すればOKです。ここがいわゆる `JAVA_HOME` として認識されます。

## Java プロジェクトを作ってみる

1. VSCode の Command Palette ( `Ctrl + Shift + P` ) を開き、 "Java: Create Java Project" を選択します。
2. プロジェクトを作るフォルダを選択してプロジェクト名を入力すると、Java プロジェクトが作成されます。
3. `src/app/App.java` がデフォルトで作成されています。main() メソッドの上に "Run|Debug" というオーバーレイが表示されていれば、そこから実行/デバッグを開始できます。App.java を右クリックして Run / Debug をクリックしても実行できるはずです。(試すの忘れた)

## Maven プロジェクトを作ってみる

Java Extension Pack には Maven 用の拡張も含まれています。
Maven をインストールしておけば、既存の Maven プロジェクトを VSCode で開いて作業することができます。

1. Apache Maven をダウンロードしてインストールします。
  - https://maven.apache.org/
  - Binary tar.gz か zip をダウンロードし、お好みの場所に展開します。
2. VSCode に Maven の場所を登録します。
  - File -> Preferences -> Settings で User 設定で `maven.executable.path` を検索し、Mavenの `bin/mvn.cmd` (Win) or `bin/mvn` (lin/mac) をフルパスで設定します。
  - `maven.terminal.useJavaHome` を true に設定します。これにより、Maven実行時に `java.home` で設定したJDKを使うようになります。(もし Maven 実行用のJDKを独立して設定したい場合は、`terminal.integrated.env` などで JAVA_HOME 環境変数を別途指定してください。)
3. VSCode の Command Palette ( `Ctrl + Shift + P` ) を開き、 "Maven: Create Maven Project" を選択します。
4. archetype (Mavenプロジェクトのテンプレート) 候補がプルダウンで表示されるので、 maven-archetype-quickstart を選択します。
5. バージョン選択になりますので、最新バージョンを選択します。
6. プロジェクトを作成するフォルダを選択します。
7. Terminal 上でMavenコマンドが実行され、archetype をもとに実際のプロジェクトを作成します。groupId / artifactId / version / package を適当な文字列・値で入力し、確認のところでYを入力すれば、artifactIdで指定した名前のフォルダ中にMavenプロジェクトが作成されます。
8. `src/main/(package directory)/App.java` を右クリック or main() 上の "Run|Debug" から実行できます。
9. `src/test/(package directory)/AppTest.java` のテストclass/method 上の "Run|Debug" からテストメソッドを実行できます。

## より詳しい情報

- VSCode の Command Palette ( `Ctrl + Shift + P` ) を開き、 "Java: Getting Started" を選択するとチュートリアルが表示されます。
- Java プロジェクトを開くと、Java Overview も表示されます。そこにも色々なリンクや操作への導線がありますので、参考になります。
- VSCode 公式のJavaガイドも参考になります。
    - https://code.visualstudio.com/docs/languages/java
- VSCode 公式でJavaのチュートリアルや各種細かい操作の解説もあるので、本格的に作業するならこちらも参考になります。
    - https://code.visualstudio.com/docs/java/java-tutorial
- 各 Extension のサイトなどを見ると細かい設定も載ってて勉強になります。
    - https://marketplace.visualstudio.com/items?itemName=redhat.java
    - https://marketplace.visualstudio.com/items?itemName=vscjava.vscode-java-test
    - https://marketplace.visualstudio.com/items?itemName=vscjava.vscode-maven

## 感想

- JDKを入れればお手軽に始められるので、勉強・入門向けにおすすめできそう。
- VSCode と拡張の動作も軽快なので、Eclipseなど主要IDEのような重さを感じることはない。
    - Javaコードを開いたときの初回の拡張起動は少し時間がかかる感じもするが、それ以上に VSCode の軽快さがノーストレス。
- Eclipse のコンポーネントをベースとしているので、Java プロジェクト構成時の設定ファイルを見てみると Eclipse プロジェクトそのものになっている。Eclipse での経験があるとトラブルシュートに強くなれるかも。
- 本格的な開発にどこまで使えるかはもう少し調べないとだめかも。
    - 特にソースコードフォーマットについて、 Eclipse の設定地獄をどこまで VSCode で追従できるか。
    - 複数のJDKを切り替えるなど、EclipseであればGUI設定画面で気軽に・確実に変更できる細かい足回りにどこまで追従できるか。
- 複雑なIDEとして使うのではなく、あくまでも「エディタ」と割り切ってシンプルに使うのであればオススメ。


