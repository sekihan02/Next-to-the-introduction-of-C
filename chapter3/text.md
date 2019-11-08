# 文字列操作関数
<!-- TOC -->

- [文字列操作関数](#文字列操作関数)
			- [Cは文字列操作がややこしい](#cは文字列操作がややこしい)
			- [文字列コピー](#文字列コピー)
			- [文字列をつなげる](#文字列をつなげる)
			- [文字列の長さを確認する](#文字列の長さを確認する)
			- [文字列の比較](#文字列の比較)
			- [文字列の検索](#文字列の検索)
			- [文字列の切り出し](#文字列の切り出し)

<!-- /TOC -->

#### Cは文字列操作がややこしい
Cには文字列がないので文字型(char型)の配列を使う
これを自力で操作しようとすると他言語に比べると不便な標準ライブラリとポインタを使う必要がある。
組み込みではあまり使わない文字列操作だが、世の中のIoTやAIへの期待を考えると
新機能の開発として、大量のデータの中から必要なデータを収集する設計を行うこともあるかもしれない。
また、新規開発で設定画面を開発する場合には文字列操作は必須となる。
少しでも楽をするべくstring.hを使用し、文字列操作関数を確認しておく

#### 文字列コピー
文字列のコピーはstrcpy()を使う
> char *strcpy(
>	char * コピー先 s1,
>	const char * コピー元 s2
> );

s2が指す文字列をs1が指す文字列にコピーする

```C
#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char s2[] = "hello, string";
	char s1[sizeof(s2) + 6] = "s2 is ";

	strcpy((&s1[0]+6), s2);

	fprintf(stdout, "s1 is %s\n", s1);

	return 0;
}

```
実行例
```
s1 is s2 is hello, string
```

#### 文字列をつなげる
先ほどの例は文字列のコピーだったが、
s2の文字列の末端からs1をコピーしたので文字列s1とs2をつなげたような結果になった。
しかし、C標準ライブラリには文字列連結関数strcat()があり、もっと楽ができる

> char *strcat(
> 	char * 連結先 s1,
> 	const char * 連結対象 s2
> )
```C
#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char s1[] = "s2 is ";
	char s2[] = "hello, string";

	strcat(s1, s2);

	fprintf(stdout, "%s\n", s1);

	return 0;
}

```
実行例
```
s2 is hello, string
```
#### 文字列の長さを確認する
文字列の長さの取得は文字列操作のなかで特に使用してきた
strlen()で取得する
> size_t strlen(
> 	const char *s
> );

先ほど書いたstrcpy_test.cのコードをstrlen()を使って書き直してみる
```C
#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char s2[] = "hello, string";
	// char s1[sizeof(s2) + 6] = "s2 is ";
	char s1[256] = "s2 is ";

	strcpy((&s1[0]+strlen(s1)), s2);

	fprintf(stdout, "s1 is %s\n", s1);

	return 0;
}
```
実行例
```
s1 is s2 is hello, string
```
#### 文字列の比較
パスワードを文字列で入力した時、その文字とパスワードを比較して一致するかを判定する時、
文字列の比較はstrcmp()使用し以下のように行う
> int strcmp(
> 	const char *s1,
> 	const char *s2
> );

戻り値は、
- $s1 > s2$の時
	正の数
- $s1 < s2$の時
	負の数
- $s1 = s2$の時
	0

文字列の大小を比較して結果を戻り値として返す
大小は文字の辞書順で計算される

```C
#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	fprintf(stdout, "hoge geho = %2d\n", strcmp("hoge", "geho"));
	fprintf(stdout, "hoge hoge = %2d\n", strcmp("hoge", "hoge"));
	fprintf(stdout, "geho hoge = %2d\n", strcmp("geho", "hoge"));

	return 0;
}
```
実行例
```
hoge geho =  1
hoge hoge =  0
geho hoge = -1
```
#### 文字列の検索
文字列から特定の文字の場所を見つけ置き換えるにはstrchr()関数を使う

> char *strchr(
> 	const char *文字列,
> 	int 検索したい文字
> );

戻り値は、最初に検索したい文字が現れた位置へのポインタを返す
見つからない場合、NULLを返す

次の例は文字列の中から1を見つけ、その位置を０にする
```C
#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char num_str[] = "000000000001000000000000";
	char search = '1';
	char *ptr;

	ptr = strchr(num_str, search);

	// 見つけた位置を０に置き換える
	strcpy(ptr, "0");

	fprintf(stdout, "%s\n", num_str);
	return 0;
}
```
実行例
```
000000000000
```
#### 文字列の切り出し
トークンを切り出す関数strtok()を使いCSVファイルからカンマ区切りで文字列を表示してみる
> char *strtok(
> 	char * restrict s1,
> 	const char * restrict s2 /* 区切り文字列 */
> );

```C
	p1 = fopen(filename, "r");

	while (fgets(p2, 256, p1) != NULL)
	{
		token = strtok(p2, ",");
		printf("code = %s\n", token);
		while ((token = strtok(NULL, ",")) != NULL)
		{
			/* code */
			 printf("code = %s\n", token);
		}
		
	}
	fclose(p1);
```
実行例
```
data.csv
ダウンロードした時刻：2019/03/02 17:50:04



,旭川,旭川,旭川,東京,東京,東京,名古屋,名古屋,名古屋,福岡,福岡,福岡,多治見,多治見,多治見

年月,平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(℃),平均気温(▒
▒▒),平均気温(℃)

,,品質情報,均質番号,,品質情報,均質番号,,品質情報,均質番号,,品質情報,均質番号,,品質情報,均質番号

1990/1,-8.5,8,1,5.0,8,1,4.2,8,1,6.0,8,1,2.9,8,1

1990/2,-3.6,8,1,7.8,8,1,8.5,8,1,10.2,8,1,7.3,8,1

```

ファイルを一行ずつ取得してその中から","区切りで出力する