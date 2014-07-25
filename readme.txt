CobuildConv 使用説明書


1. CobuildConvとは

"Collins COBUILD Advanced Leaner's English Dictionary NEW EDITION"(Collinsコウビルド英英辞典【改訂第5版 CD-ROM付】)のデータを変換し、EBStudio用の入力ファイルを作成します。
変換されるのは、テキストのみで、画像・音声は変換されません。


2. ファイルの内容

readme.txt      ... このファイル
CobuildConv.cpp ... ソース
CobuildConv.exe ... Borland C++ 5.5.1でコンパイルしたロードモジュール
Cobuild.ebs     ... EBStudioの作業環境定義ファイル
Wordbank.ebs    ... EBStudioの作業環境定義ファイル
Gaiji.xml       ... 外字フォントファイル
GaijiMap.xml    ... 外字定義ファイル

3. 動作確認環境

OS : Windows XP
コンパイラ：Borland C++ 5.0.1 / Borland C++ 5.5.1
CD-ROM : ISBN4-88996-203-4 付属のCD-ROM

4. 使い方

コマンドプロンプトで以下の様に指定して実行します。
CobuildConv データディレクトリ [-w]
実行ディレクトリにcobuild.htmlが作成されます。

[例]
CobuildConv "C:\Program Files\Collins COBUILD\Cobuild Dictionary 2006\data"

wordbankを変換する場合は、次の様にします。
CobuildConv データディレクトリ -w
実行ディレクトリにwordbank.htmlが作成されます。

[例]
CobuildConv "C:\Program Files\Collins COBUILD\Cobuild Dictionary 2006\data" -w


5. EBStudioで変換

EBStudioを起動し、添付のCobuild.ebsまたはWordbank.ebsを開きます。
基準ディレクトリと出力先を適当に変更し、実行します。


6. 作成される索引

  Dictionary
    見出し語の前方一致、後方一致、クロス条件索引を作成します。
    類義語、反義語の条件索引を作成します。
    
  Wordbank
    用例中の英単語の条件索引を作成します。


7. コンパイル

ソースを変更してコンパイルし直す場合は、
http://www.codegear.com/jp/downloads/free/cppbuilder
で"Borland C++ 5.5.1"を入手することができます。
そのままコンパイルすると、コンパイル時に警告が出ますが無視してください。

8. 参考

NOMAD氏の"CobuildConv.rb v1.32"を参考にしました。


9. 権利

オープンソース扱いとします。
自由に改変・配布してかまいません。

