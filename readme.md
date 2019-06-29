# はじめに
これから使われるかもしれない資料の物置。
作りかけで文章不得手で説明不足悪目立ち。自己責任でどのようにでもどうぞ

　C言語を覚え、組み込みエンジニアになり何年かが過ぎた。
しかし、依然としてポインタで実体のないデータにNULLアクセスをしては人の手を借りるような状態。
この現状を変えるべく、本当の意味でC言語初心者になるべく学習した。

※OSはWindows10を使用している。
もし違う環境を使用する場合は適宜そのchapter冒頭で宣言する。

## 構成
　構成はchapterごとにディレクトリを分け、
その中に以下のように使用したファイルを保存する

chapter

|

|--text.md // chapterの本文

|

|--text.html // 本文のhtml

|

|--src // 使用したソースコードとmakeファイル

	|- ***.c

	|- Makefile

## これくらいあれば中身を読むことができる前提知識
- 1. 入門書レベルのC知識
- 2. gccで実行ファイルを作れる
- 3. 知らない単語を検索する程度の能力
