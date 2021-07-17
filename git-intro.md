<!-- omit in toc -->
# Gitの使い方

<!-- Press Ctrl + K, V -->

<!-- omit in toc -->
## Table of Contents

- [最初にやること](#最初にやること)
  - [GitHubのアカウントを作成](#githubのアカウントを作成)
  - [インストール](#インストール)
  - [初期設定](#初期設定)
  - [SSH接続を設定](#ssh接続を設定)
- [初めてのリポジトリ](#初めてのリポジトリ)
  - [リポジトリを作る](#リポジトリを作る)
  - [ローカルにコピーする](#ローカルにコピーする)
  - [編集してみる](#編集してみる)
  - [コミット](#コミット)
  - [プッシュ](#プッシュ)
  - [プル](#プル)
- [終わりに](#終わりに)

## 最初にやること

### GitHubのアカウントを作成

https://github.com/

このページの「Sign up for GitHub」を押してアカウントを作ります。

### インストール

https://git-scm.com/book/ja/v2/%E4%BD%BF%E3%81%84%E5%A7%8B%E3%82%81%E3%82%8B-Git%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB

`git --version`でバージョンが表示されたらインストール成功です。

### 初期設定

まずはユーザー名とメールアドレスです。以下のコマンドを実行します。行の最初にある`$`は入力プロンプトです。

```
$ git config --global user.name <ユーザー名>
$ git config --global user.email <メールアドレス>
```

`<>`の部分には先程GitHubに登録したものを設定します。空白が含まれている場合は`"`で囲んでください。

[ロボット部のアカウント](https://github.com/izumi-robot/)の場合はこのようになります。

```
$ git config --global "izumi robot"
$ git config --global izumi.robot@gmail.com
```

次に、gitで使用するエディターを設定します。これはしなくても問題ありません。

```
$ git config --global core.editor <エディター起動コマンド>
```

`<>`にはVS Codeを使用する場合は`"code --wait"`、vimを使う場合は`vim`が当てはまります。

### SSH接続を設定

SSHとは、ざっくり言うとインターネット通信方式の一種です。HTTPSと同類です。より詳しい仕組みは[インフラエンジニアじゃなくても押さえておきたいSSHの基礎知識 - Qiita](https://qiita.com/tag1216/items/5d06bad7468f731f590e)を見てください。GitHubと通信するのに使います。

まずはSSHを使うためのツールをインストールします。といっても、Windows、Macには標準でインストールされています。Linuxの場合は`sudo apt-get install ssh`です。`ssh -V`でバージョンが表示されたらインストールされていることになります。

```
$ ssh -V
OpenSSH_for_Windows_7.7p1, LibreSSL 2.6.5
```

SSHで通信するのためには「鍵」が必要となります。`ssh-keygen -t rsa`を実行して鍵を作成します。以下、鍵の作成例です。

```
$ ssh-keygen -t rsa
Generating public/private rsa key pair.
Enter file in which to save the key (C:\Users\your-username/.ssh/id_rsa):
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in C:\Users\your-username/.ssh/id_rsa.
Your public key has been saved in C:\Users\your-username/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:6KCVP9WVp3jGFXsMRxJUBPxj5AK6cDLova39WPentew your-username@pc-information
The key's randomart image is:
+---[RSA 2048]----+
|             oB*=|
|           . ..O |
|      .   . + *.o|
|     o = + + = =.|
|    = o S + = o .|
|   o = o . o     |
|  .   + o  . .  .|
|       o..o . o.o|
|       ..o..  oE.|
+----[SHA256]-----+
```

ファイル名とパスワードを求められますが、何も入力しなくても大丈夫です。鍵ができたか確認します。

```
$ cat ~/.ssh/id_rsa.pub
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCkuXDeUKiBdkhZENYEuZAxRfXQEWasZATPuybSSqjf5B1ZPTkZ/taddTqIRbUmXqSixqpiVpRxAo3ehJ9KwplVkndhgL3DoM0CpDVybSW5c+pm8kqMqWWXmICOGQGYtl9UonTBWi4rn9/1FOmbQLxxX84+M1QbrAoS385d9hTzyvYSSKkYAv0P46/LeeWfjbmC4SBbIO60057m214OeUM2zX4ImtF8b9xc+D+pn6BVoVkLm0hM27qiYlsx5/tqsgrUaaT3APyWL4ubFKf0RAFOTHrNY4SGn+z8/fhEZXWXcPQRDI6YXQM8cQNWUox8bbLeTiveQhQ50hlTJcpjNVQN your-username@pc-information
```

出てきた文字列はコピーしておいてください。後で使います。

次はその鍵をGitHubに登録します。https://github.com/ を開いてログインし、画面右上のユーザーアイコンにマウスを置いて出てくるメニューから「Settings」を選択します。「SSH and GPG keys」の項に移動し、「New SSH key」のボタンを押します。「Title」に鍵のタイトル、「Key」に先程コピーしたものを入力します。鍵のタイトルは何でもいいです。「Surface」など、鍵を作成したパソコンの機種名にしておくのがオススメです。「Add SSH Key」を押して鍵の登録が完了したら、鍵が追加されたというメールが来ます。

それでは、鍵が登録できたか確認してみましょう。`ssh -T git@github.com`を実行します。よく分からんwarningが出ますが気にしないでください。何かしらの許可を求められた場合は通してください。`Hi <ユーザー名>! ...`と出てきたら登録成功です。

```
$ ssh -T git@github.com
Hi <ユーザー名>! You've successfully authenticated, but GitHub does not provide shell access.
```

## 初めてのリポジトリ

### リポジトリを作る

再びGitHubを開きます。画面右上の「+」ボタンにマウスを合わせ、「New Repository」を押します。Title、descriptionを設定してから「Add a README file」にチェックを入れ、「create repository」を押してリポジトリを作成します。このリポジトリを示すURLは`https://github.com//<ユーザーid>/<リポジトリ名>`となっています。`<ユーザーid>`と`<リポジトリ名>`は後で使うので、覚えておいてください。

### ローカルにコピーする

`cd`でリポジトリを置くフォルダーに移動してから`git clone ssh://git@github.com/<ユーザーid>/<リポジトリ名>.git`です。`<リポジトリ名>`のフォルダーが作られ、その中にクローンしたリポジトリの内容が格納されます。

```
$ git clone ssh://git@github.com/<ユーザーid>/<リポジトリ名>.git
Cloning into '<リポジトリ名>'...
remote: Enumerating objects: 125, done.
remote: Counting objects: 100% (125/125), done.
remote: Compressing objects: 100% (94/94), done.
remote: Total 125 (delta 39), reused 43 (delta 11), pack-reused 0R
Receiving objects: 100% (125/125), 13.90 MiB | 565.00 KiB/s, done.
Resolving deltas: 100% (39/39), done.
```

基本的には、クローンされたリポジトリを編集して、その変更点をサーバー上のリポジトリに反映させていく、という方法で開発を進めていきます。

### 編集してみる

編集前に、gitが正しく機能しているか確認します。リポジトリ内にターミナルで移動し、`git status`を実行します。次のようになれば正しく機能していることになります。

```
$ git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

それでは、リポジトリを編集してみましょう。先ほど作成したフォルダー内に何かテキストファイルを追加してください。ここでは仮に`helloworld.py`を追加します。

```Python
# helloworld.py
print("Hello, world!")
```

もう一度`git status`を実行すると、次のように表示されます。

```
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        helloworld.py

nothing added to commit but untracked files present (use "git add" to track)
```

### コミット

それでは、`helloworld.py`を変更として記録していきます。

```
$ git add helloworld.py
$ git commit -m "Add helloworld.py"
[main 0af4b69] Add helloworld.py
 1 file changed, 1 insertion(+)
 create mode 100644 helloworld.py
```

`git add`で指定したファイルは「ステージングエリア」に上げられます。ステージングエリアには小さな変更をまとめていきます。ある程度の変更がたまったところで「コミット」を行います。`git commit`でステージングエリアにたまった変更をまとめて記録します。コミットには「コミットメッセージ」というものが必要です。コミットメッセージには、このコミットでの変更点の要約を書き込みます。`-m "コミットメッセージ"`とすることでコミットメッセージを指定できますが、そうしなかった場合は指定されたエディターが開き、コミットメッセージを書くように要求されます。

### プッシュ

「プッシュ」とは、パソコン内にあるローカルリポジトリでの変更点をサーバー上にあるリモートリポジトリに反映させることです。サーバーには、今回の場合はGitHubが該当します。コマンドは`git push`です。

```
$ git push
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 305 bytes | 152.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
To ssh://github.com/<ユーザーid>/sample.git
   6496bc0..0af4b69  main -> main
```

これでローカルリポジトリをリモートリポジトリに反映させることができました。

### プル

リモートリポジトリに他の人がプッシュした場合、ローカルリポジトリをリモートリポジトリと同期させる必要があります。この同期方法が「プル」です。コマンドは`git pull`です。

リポジトリが最新の場合はこのようになります。

```
$ git pull
Already up to date.
```

リポジトリが最新でない場合はこのようになります。

```
$ git pull
remote: Enumerating objects: 5, done.
remote: Counting objects: 100% (5/5), done.
remote: Compressing objects: 100% (1/1), done.
remote: Total 3 (delta 2), reused 3 (delta 2), pack-reused 0
Unpacking objects: 100% (3/3), 611 bytes | 50.00 KiB/s, done.
From ssh://github.com/<ユーザーid>/sample
   00a8813..4219b84  main       -> origin/main
Updating 00a8813..4219b84
Fast-forward
 helloworld.py | 47 +++++++++++++++++++++++++++++++----------------
 1 file changed, 31 insertions(+), 16 deletions(-)
```

## 終わりに

ここまで、gitの使い方を紹介しました。より詳しい情報は[Git Book](https://git-scm.com/book/ja/v2)を読んでください。[今さらだけどGitを基本から分かりやすくまとめてみた - Qiita](https://qiita.com/gold-kou/items/7f6a3b46e2781b0dd4a0)も分かりやすいです。
