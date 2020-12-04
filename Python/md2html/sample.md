---
title: MacOSでVisual Studio Codeをインストールする手順
tags: MacOSX VisualStudioCode install
author: watamura
slide: false
---
Visual Studio Codeとは通称VSCodeと呼ばれ、Microsoft社が開発したテキストエディタです。

他のテキストエディタに比べ、HTMLやCSSなどを書く時の補助的な機能が揃っているため、多くのプログラマやWebデザイナー達の指示を集め最近人気のテキストエディタです。

それをMacOSにインストールし、使用できるまでの手順をまとめました。
ちなみにVSCodeはマルチプラットフォームなのでWindows、MacOS、Linuxのいずれの環境にもインストールできます。

# 1. VSCodeのサイトにアクセス
下記のサイトにアクセスし、「Download for Mac」をクリック

https://code.visualstudio.com/
<img width="1312" alt="スクリーンショット 2019-10-08 13.47.48.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/a5860874-68e7-1262-f435-15e4de206822.png">

# 2. ダウンロード
画面が移動したら自動でダウンロードが始まり、ダウンロードフォルダにアプリがダウンロードされます。

<img width="1312" alt="スクリーンショット_2019-10-08_13_47_57.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/d48a82b1-7646-7358-4305-f50b2c36eb93.png">

# 3. ダウンロードしたファイルを開く（解凍する）
画面右下の ① のアイコンをクリックすると、ダウンロードフォルダに入ったファイル一覧が出てくるので、該当の ② をクリックしてください。

<img width="865" alt="スクリーンショット_2019-10-08_13_48_31.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/cdf08fbf-738b-fc08-0344-c5c024fe328a.png">

# 4. アプリケーションフォルダに移動
ダウンロードフォルダにそれらしいアイコンが表示されたかと思いますが、まだ開かないでください。
そのアイコンをドラッグアンドドロップで、サイドメニューの「アプリケーション」に移動させます。

<img width="882" alt="スクリーンショット_2019-10-08_13_48_48.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/cde806a2-fbac-e35e-7ee0-99df26d29abb.png">

# 5. 認証ボタンを押す（人によっては表示されず、スキップして構いません）
この画面が表示されたら「認証」ボタンを押して、管理者のログイン情報を入力し認証してください。

<img width="488" alt="スクリーンショット 2019-10-08 13.49.10.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/52a94581-1d06-5770-f0fe-3ee27f37821c.png">

# 6. アプリケーションフォルダからVSCodeを開いてください
サイドメニューの「アプリケーション」をクリックし、VSCodeを見つけ、ダブルクリックで開いてください。

<img width="882" alt="スクリーンショット_2019-10-08_13_50_22.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/c093abf3-1cf2-20eb-3e99-eb22d6da15c9.png">

## 【開発元が未確認のため開けません】という警告ダイアログが表示された場合
macOS Sierraから、Macのセキュリティ機能であるGateKeeperによって確認が必要な状態となり、不明な開発元（デベロッパIDを持たない開発元）によって作られたアプリは開けなくなりました。
Mac App Storeで配布していないアプリ全般に表示されるので、これは必ずしもアプリケーションに問題がある訳ではありません。
※ただ不正なコードが含まれる可能師があるアプリも存在します。

このアプリにだけ、例外的にセキュリティ設定を無効化してこのままアプリケーションを開くには、次の手順に従います。

> 1. MacのFinderで、開きたいアプリケーションを検索します
> 2. Launchpadは使用しないでください。Launchpadではショートカットメニューにアクセスできません
> 3. Controlキーを押しながらアプリケーションアイコンをクリックして、ショートカットメニューから「開く」を選択します
> 4. 「開く」をクリックします。



### 参考
1. [開発元が未確認のMacアプリケーションを開く](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)
2. [Macで「開発元が未確認のため開けません」となりアプリが開けない場合はどうすれば？](https://aprico-media.com/posts/1382)

アプリケーションはセキュリティ設定の例外として保存され、今後は登録済みのアプリケーションと同様に、ダブルクリックすることで開くことができるようになります。



# 7. VSCodeの初期画面
この様な画面がでるかと思います。

<img width="1136" alt="スクリーンショット 2019-10-08 13.50.52.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/0512ef54-41a2-3f48-705e-e29837512d20.png">

# 8. もっと便利になるような拡張機能をインストール
サイドメニューの■マークが並んだアイコンをクリックしてください。
<img width="1136" alt="スクリーンショット_2019-10-08_13_51_01.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/5e27b3e2-e4b8-25ae-1b10-f8eb4cb4b44f.png">

# 9. 拡張機能の検索からインストールまで
赤枠の検索フォームに「Japanese Language Pack」と打ってみてください。
そうすると下に検索結果が表示されるので、同じ名前の拡張機能にある「Install」ボタンをクリックします。
<img width="1136" alt="スクリーンショット_2019-10-08_13_51_20.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/47b4e354-7741-54fc-4113-f3018aa27e2a.png">

# 10. 他の拡張機能もインストールしましょう

他にも下記の拡張機能を同じようにインストールしてみてください。
下記のテキストをコピー・アンド・ペーストで検索したほうが確実です。

* Japanese Language Pack
* Visual Studio IntelliCode
* Bracket Pair Colorizer
* Path Intellisense
* HTMLHint
* EvilInspector

# 11. ひととおりインストールしたらVSCodeを再起動しましょう。
VSCodeを開いた今の状態で、左上の「Code」から「Quit Visual Studio Code」をクリックすると閉じます。
そして再度アプリケーションフォルダからVSCodeを開いたら、インストールと準備は完了です。

<img width="428" alt="スクリーンショット 2019-10-08 13.52.08.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/74438/b4c88e0c-95e1-0a38-9611-1df67bad03ea.png">

# 12. 参考
HTMLを作成時にlang属性をenからjaに変更する方法が下記サイトで詳しく書いています。
[VSCodeのemmetでhtmlのlangをjaに設定する方法](https://qiita.com/mi_upto/items/67fea35140f126256260)

