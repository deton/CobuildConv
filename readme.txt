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

OS : Windows 7
コンパイラ：Borland C++ 5.5.1 / Visual Studio 2010 Express
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
http://www.embarcadero.com/jp/products/cbuilder/free-compiler
で"Borland C++ 5.5.1"を入手することができます。
そのままコンパイルすると、コンパイル時に警告が出ますが無視してください。

8. 参考

NOMAD氏の"CobuildConv.rb v1.32"を参考にしました。


9. 権利

オープンソース扱いとします。
自由に改変・配布してかまいません。

10. 履歴

2007/07/27 公開 by pcs http://www31.ocn.ne.jp/~h_ishida/CobuildConv/
2014/07/26 修正 by deton
  * CobuildConvが異常終了して、最後の単語のzygoteの本文が欠ける問題を修正。
  * 構文記述(syntax)の長さが256以上の単語に関し、記述が途中で切れる問題を修正。
    紙の辞書で、本文最初の青く塗られた領域や青枠で囲われた領域に相当。
    (about, bath, do^1, far, for, forward, have^3, in^1, into, of, off, on,
    round^1, -'s, take^1, through, to^1, with)
    例えば、farの場合、Further and furthest are dealt with in separate entries.
    のareの前で切れる。
  * Visual C++でビルドした場合、特記事項(alternative)の長さが256以上の単語に
    関し、記述の最後の部分が本文最初に重複して出力される問題を修正。
    紙の辞書で、本文最初の青く塗られた領域や青枠で囲われた領域に相当。
    (come, put, -s)
