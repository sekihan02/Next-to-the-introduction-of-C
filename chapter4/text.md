# メモリの確保
<!-- TOC -->

- [メモリの確保](#メモリの確保)
		- [サイズ指定でメモリを確保](#サイズ指定でメモリを確保)
		- [メモリを解放する](#メモリを解放する)
		- [メモリを拡張する](#メモリを拡張する)
		- [リスト構造 [書き途中]](#リスト構造-書き途中)

<!-- /TOC -->

### サイズ指定でメモリを確保
必ず決まった大きさのデータを扱うとは限らない。
予想しているサイズよりもデータが小さい場合、大きい場合に動的にサイズを確保しようとするとき、まずポインタ変数を自動変数として宣言し、必要なメモリをどこかから適当に見繕って対応する事になる。
が、根拠なく自分の憶測でメモリを取得するのは危険で説明も難しい。
こういう時はmalloc()関数を使いメモリサイズをシステムから借りて対応する。

> void *malloc(
> 	size_t 必要なサイズ
> );

必要なサイズを渡すとシステムのどこかに確保したvoidポインタを返す。
必要なサイズが確保できないときはNULLポインタが返る。

malloc()はメモリ領域を初期化されて無いが
clloc()関数を使うと０で初期化したうえでメモリ領域を確保できる。
> void *calloc(
> 	size_t 要素数,
> 	size_t 要素当たりに必要なサイズ
> );

### メモリを解放する
メモリの確保については連携するように解放の処理のfree()関数を利用する
> void free(
> 	void *ptr
> );

解放したメモリはNULLを代入し、この後の処理で解放されたメモリを使わないようにしたほうが良い。
ポインタに対してfreeを使わない場合、
そのバッファは利用できない。
実際に使っていなくてもシステム的にはそのバッファが使われている判断される。

ここまでの例として、0～9までの数字を格納するメモリをmalloc()で宣言し、char配列20byteをcalloc()で宣言して表示確認する
memory_test.c
```C
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	int *one_num;
	char *one_string;
	int *zero_test;

	char str = '1';

	one_num = malloc(sizeof(int)*10);
	one_string = calloc(20, sizeof(char));
	zero_test = calloc(20, sizeof(int));

	// malloc()の表示確認
	for (int i = 0; i < 10; i++)
	{
		one_num[i] = i;
		fprintf(stdout, "%2d", one_num[i]);
	}
	free(one_num);
	one_num = NULL;

	printf("\n");

	// calloc(文字列)の表示確認
	for (int j = 0; j < 20; j++)
	{
		one_string[j] = str;
		fprintf(stdout, "%c", one_string[j]);
	}
	free(one_string);
	one_string = NULL;

	printf("\n");

	// calloc()の表示確認
	for (int k = 0; k < 20; k++)
	{
		fprintf(stdout, "%d", zero_test[k]);
	}
	free(zero_test);
	zero_test = NULL;

	return 0;
}
```
実行結果
```
 0 1 2 3 4 5 6 7 8 9
11111111111111111111
00000000000000000000
```

### メモリを拡張する
ここまでのメモリの確保方法は動的ではあるもののmalloc(), calloc()関数呼び出しじにサイズを指定している。
そのため処理の途中でメモリを追加することができない。
このような時のためにrealloc()関数を使うことで処理途中でメモリ領域を拡張できる
> void *realloc(
> 	void *拡張したいポインタ,
> 	size_t 拡張後のサイズ
> );
戻り値は拡張されたメモリ領域が得られる。
拡張できなかったときはNULLとなる。

realloc_test.c
```C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char *one_string;
	char *new_string;

	one_string = malloc(sizeof(char)*16);
	// メモリ領域のエラー処理
	if (one_string == NULL)
	{
		fprintf(stdout, "Memory allocation error.\n");
		return 0;
	}
	// メモリのポインタの表示
	fprintf(stdout, "one_string = %p\n", one_string);
	// 文字列のコピー
	strcpy(one_string, "Hello world\n\0");
	fprintf(stdout, "%s", one_string);

	// メモリの拡張
	new_string = realloc(one_string, 32);
	
	// メモリ領域のエラー処理
	if (new_string == NULL)
	{
		fprintf(stdout, "Memory allocation error.\n");
		free(one_string);
		return 0;
	}
	// 拡張したメモリのポインタの表示
	fprintf(stdout, "new_string = %p\n", new_string);
	one_string = new_string;
	strcpy(one_string, "hello world\nHELLO WORLD\n\0");

	fprintf(stdout, "%s", one_string);
	
	free(one_string);
	return 0;
}
```
実行結果
```
one_string = 00751668
Hello world
new_string = 00751668
hello world
HELLO WORLD
```

### リスト構造 [書き途中]
動的メモリの具体例を調べてみると、リスト構造という実態は連続していないが動作的には連続して並んでいる配列のようにみせるデータ構造を使う例がヒットした。
健康診断用の個人情報データプログラムを作ってみる

* 利用・提供する個人情報の項目
	-	保険証記号＆番号
	-	氏名
	-	住所
	-	生年月日
	-	年齢
	-	電話番号
	-	メールアドレス
	-	所属部署名　
	-	健康診断結果

住所番号
名前
住所
次のデータへのポインタ