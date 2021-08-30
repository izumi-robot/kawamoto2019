<!-- omit in toc -->
# Git & SSHのアレコレ

<!-- omit in toc -->
## 目次

- [複数アカウントでGitHubと通信する](#複数アカウントでgithubと通信する)
- [参考](#参考)

## 複数アカウントでGitHubと通信する

**1: 鍵を複数作る**

ターミナルで以下のように進めます。`# ...`の部分はコメントです。Windowsの場合、コマンドプロンプトではなくPowerShellで進めることをオススメします。

```
$ cd ~/.ssh
$ ssh-keygen -t rsa
Generating public/private rsa key pair.
Enter file in which to save the key (C:\Users\your-username/.ssh/id_rsa):./id_rsa_[name] # [name]の内容は後述 ./を忘れない
Enter passphrase (empty for no passphrase): # パスワードはあってもなくても
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

`[name]`にはGitHubのアカウント名を識別できる何かを入れてください。例えば、[ロボ部のアカウント](https://github.com/izumi-robot)用に鍵を作る場合は`robo`などにするのがいいでしょう。(私は実際に自分のパソコンで鍵を作って登録しました)

`intro.md`で説明したのと同様に、`id_rsa_[name].pub`の内容を対応するGitHubアカウントに登録します。

**2: 鍵用の設定をする**

ターミナルに戻ります。

```
$ cd ~/.ssh
$ code config
```

2つ目のコマンドでVSCodeが開きます。おそらく空のファイルが開くので、次のように入力します。空でなかった場合は、末尾に追加してください。

```
Host github.com.[name]
    HostName github.com
    User git
    Port 22
    IdentityFile ~/.ssh/id_rsa_[name]
    TCPKeepAlive yes
    IdentitiesOnly yes
```

察しているかもしれませんが、`[name]`の部分は先程の鍵作成で書いた`[name]`と揃えてください。

**3: 接続確認**

`ssh git@github.com.[name]`で接続を確認します。セクション1での例のように鍵を作り、設定を適切に行った場合は次のようになります。

```
$ ssh git@github.com.robo
Hi izumi-robot! You've successfully authenticated, but GitHub does not provide shell access.
Connection to github.com closed.
```

`Hi [アカウント名]!`という表示が出ていれば成功です。

**4: クローンしてみる**

`git clone ssh://git@github.com.[name]/[ユーザーid]/[リポジトリ名]`でクローンできます。例えば、前例で作った鍵でロボ部の`rcj2021`というリポジトリをクローンする場合は次のようになります。

```
$ git clone ssh://github.com.robo/izumi-robot/rcj2021
Cloning into 'rcj2021'...
remote: Enumerating objects: 125, done.
remote: Counting objects: 100% (125/125), done.
remote: Compressing objects: 100% (94/94), done.
remote: Total 125 (delta 39), reused 43 (delta 11), pack-reused 0R                     % (84/125), 12.55 MiB | 1.75
Receiving objects: 100% (125/125), 13.90 MiB | 1.50 MiB/s, done.
Resolving deltas: 100% (39/39), done.
```

ただし、このままではgitを使用するユーザーの設定がグローバルのままになっているので、クローンした後に次のように続ける必要があります。

```
$ cd rcj2021                                          # クローンしたリポジトリのフォルダー
$ git config --local user.name izumi-robot            # [name]またはGitHubのユーザーid
$ git config --local user.email izumi.robot@gmail.com # アカウントのメールアドレス
```

## 参考

- https://qiita.com/yampy/items/24638156abd383e08758
