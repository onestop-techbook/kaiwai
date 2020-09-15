== 執筆環境の準備

執筆環境は以下の通りです。

 * コミュニケーションツール：Slack
 * ドキュメントのリポジトリ：GitHub
 * 組版フレームワーク：Re:VIEW
 * CI/CD環境：wercker
 
サークル「親方Project」の持っている基盤を利用させていただく形で、準備のコストを最小限に抑えています。

=== Slackでコミュニケーション
これは、ひとえに「おやかた合同誌Slack」がもとからあったという点につきます。

親方Projectでは、見積もりや勉強会、あるいはエンジニアのスキル等に関する合同誌を発行しています。合同誌なので、複数の著者がいますが、そのやりとり（テーマの相談・決定、スケジュール策定、内容の相談、追記修正の指示など）、および日々のざっくばらんな会話の場として、Slackを使っています。技術書界隈を盛り上げる会の参加者（登壇者、聴講者）も相当数すでに参加していました。

新しいワークスペースを作ることも考えたのですが、参加ワークスペースが増えると管理も大変です。また、親方Projectへの寄稿がシームレスに進むのではないかという（おやかたの）下心もあり、こちらに間借りさせていただくことになりました。

新しいチャンネルを作り、すでにいる関係者をそのチャンネルに呼ぶだけですから、簡単です。

=== GitHubで原稿管理
複数人で原稿を持ち寄るため、バージョン管理や原稿の統合が大変になる可能性があります。そこで、比較的使い慣れている（仕事で普通に使っている人も多い）、GitHubでの原稿管理とします。後述の組版フレームワークであるRe:VIEWは、Markdownライクなマークアップテキストをコンパイルするものですから、Gitでの差分管理が簡単です。

特徴的だと考えているのは、権限周りでしょう。マージ権限は、参加者全員に付与します。

通常の開発においては、以下の流れで開発（ここでは執筆）が進んでいくと聞いています。

 1. ブランチを切ってからそのブランチで執筆する
 2. masterブランチにPull Requestをあげる
 3. 権限を持つ人がレビューし、その結果をマージする
 
 これに対し、このプロジェクトおよび親方Projectの他の本では、masterブランチ1本での運用と、セルフでのマージmasterブランチへの直Pushを推奨しています。

その理由は、次の三つです。

 * アプリなどと違って見えづらい・特定条件でのみ発動したりするような、レビューが必要なバグが混入することは滅多にない
 * masterブランチ1本でやることで自然に他の人の目に触れるので、他の著者の目にもなんとなく触れることでレビューされやすくなる。
 * ブランチのマージ忘れなどのせっかく書いた原稿を取りこぼすリスクが減る

編集長が単一障害点になりかねません。またGitのお作法など知らない人が新たに覚えなければいけないことが増えてしまいます。またすぐに結果をみることができないとか、様々な弊害が生じます。

CIでのコンパイルさえ通れば、あとは微調整も容易ですし、細かい問題点があったとしても、masterでやっていれば誰かが直すことも容易です。細かい（本質的でない）コンパイルエラーの解決に時間を取られて執筆のモチベーションを失うのは本末転倒の極みです。ですから、カジュアルにmasterにPushしてください。編集長の方で二分探索でもなんでもやりながら直すので・・・

=== Re:VIEWで組版
今回は（今回も）Re:VIEWでの組版です。みなさんが書いてくれた原稿は、本の形になるように文字を並べる必要があります。

プレーンテキストで書いたとして、章タイトルや節目次は文字を大きくしたり、文の頭を一文字空けたり、ページ番号をいれたりしたいですよね？これを自動でやるのが組版ツールです。世の中の出版界ではAdobeのInDesignが主流ですが、自由度が高すぎる分使いこなすには技術が必要です。

そこで、技術書典をはじめとした技術書界隈でほぼデファクトスタンダードと言って良い、Re:VIEWを使います。テキストに制御タグを埋め込むだけで、RubyがTeXコードに変換し、LaTeXにより組版され、PDFとして出力されます。

細かい調整には、TeXの知識が必要になるのですが、もともとあるテンプレートが優秀なのでほとんど何も考えずに本文を書くだけで印刷可能なPDFが出力されます。

組版はRe:VIEWでやるのですが、使ったことのない人も当然います。そういう人には、プレーンテキストでも、WordでもMarkdownでも、なんでもいいから一番使い慣れたツールで出してください、というお願いをしています。編集部でコンバートすることも時々あります。

いろいろRe:VIEWについての恨み節を持っている人はいるのですが、ここでは触れません。

=== WerckerCIによる自動コンパイル
原稿を書いて、GitHubにPushすると、自動的にコンパイルが走るようにCIを組んでいます。

組版の環境構築は案外面倒です。Re:VIEWを使うにはRubyとTeXをいれなければならなかったり、あるいはDockerを使いましょうという説明がされることがありますが、どんな環境、誰の環境でも絶対に動くという保証はありません。我々がやりたいのは、原稿を書いてPDFを確認し入稿ことであり、環境構築ではありません。（そこで、環境構築に喜びを見出してしまう人が少なくないのは事実ですが）

ですから、同じ環境で、かつ原稿をPushしたら自動でPDFが出てくる環境を作っておくことで、環境構築でのハマりを抑止します。CIでコンパイルが走ってPDFが出力されるまで2～3分かかってしまうというデメリットはありますが、ある程度の量を書いて、Pushするといった形であれば特に問題はないでしょう。

実際、今でも、私おやかたは、ローカル環境でのRe:VIEWは使っていません。（一応作ってはありますが、うまく動かないことも多いのです・・・）

=== 執筆環境の準備のまとめ
以上、執筆環境に関するTipsです。いずれも、執筆者が原稿の執筆に集中できるように、その他のストレスを出来るだけ引き受けることができる環境を作るという趣旨で構築した環境です。

テキストを書いてくれればあとはこっちでなんとかするから！というのはいつも参加者にお伝えしていることです。
