<!-- omit in toc -->
# Gitの使い方

より詳しい情報は[Git Book](https://git-scm.com/book/ja/v2)を読んでください。[こちら](https://qiita.com/gold-kou/items/7f6a3b46e2781b0dd4a0)も分かりやすいです。

<!-- omit in toc -->
## Table of Contents

- [最初にやること](#最初にやること)
  - [GitHubのアカウントを作成](#githubのアカウントを作成)
  - [インストール](#インストール)
  - [初期設定](#初期設定)
  - [SSH接続を設定](#ssh接続を設定)
- [Gitの基本概念](#gitの基本概念)

## 最初にやること

### GitHubのアカウントを作成

https://github.com/

このページの`Sign up for GitHub`を押してアカウントを作ります。

### インストール

https://git-scm.com/book/ja/v2/%E4%BD%BF%E3%81%84%E5%A7%8B%E3%82%81%E3%82%8B-Git%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB

`git --version`でバージョンが表示されたらインストール成功です。

### 初期設定

まずはユーザー名とメールアドレスです。先程GitHubに登録したものを設定します。空白が含まれている場合は`"`で囲んでください。

- `git config --global user.name <ユーザー名>`
- `git config --global user.email <メールアドレス>`

[ロボット部のアカウント](https://github.com/izumi-robot/)の場合はこのようになります。(行の最初にある`>`は入力プロンプトです。)

```bash
> git config --global "izumi robot"
> git config --global izumi.robot@gmail.com
```

次に、gitで使用するエディターを設定します。コマンドは`git config --global core.editor <エディター起動コマンド>`です。VS Codeを使用する場合は`code --wait`、vimを使う場合は`vim`が`<エディター起動コマンド>`に当てはまります。

### SSH接続を設定

SSHとは、ざっくり言うとインターネット通信方式の一種です。HTTPSと同類です。より詳しい仕組みは[インフラエンジニアじゃなくても押さえておきたいSSHの基礎知識 - Qiita](https://qiita.com/tag1216/items/5d06bad7468f731f590e)を見てください。GitHubと通信するのに使います。

まずはSSHを使うためのツールをインストールします。といっても、Windows、Macには標準でインストールされています。Linuxの場合は`sudo apt-get install ssh`です。`ssh -V`でバージョンが表示されたらインストールされていることになります。

SSHで通信するのためには「鍵」が必要となります。鍵の作成コマンドは`ssh-keygen -t rsa`です。ファイル名とパスワードを求められますが、何も入力せずに飛ばしてください。作成が完了したら、`cat ~/.ssh/id_rsa.pub`で出てきた文字列をコピーしておいてください。後で使います。

次はその鍵をGitHubに登録します。https://github.com/ を開いてログインし、画面右上のユーザーアイコンにマウスを置いて出てくるメニューから「Settings」を選択します。「SSH and GPG keys」の項に移動し、「New SSH key」のボタンを押します。「Title」に鍵のタイトル、「Key」に先程コピーしたものを入力します。鍵のタイトルは何でもいいです。「Surface」など、鍵を作成したパソコンの機種名にしておくのがオススメです。「Add SSH Key」を押して鍵の登録が完了したら、鍵が追加されたというメールが来ます。

それでは、鍵が登録できたか確認してみましょう。`ssh -T git@github.com`を実行します。よく分からんwarningが出ますが気にしないでください。何かしらの許可を求められた場合は通してください。`Hi <ユーザー名>! ...`と出てきたら登録成功です。

## Gitの基本概念

参考

- https://git-scm.com/book/ja/v2/%E4%BD%BF%E3%81%84%E5%A7%8B%E3%82%81%E3%82%8B-Git%E3%81%AE%E5%9F%BA%E6%9C%AC

Gitで管理するプロジェクト全体を「リポジトリ」といいます。
