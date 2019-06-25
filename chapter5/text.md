# ファイルの扱い
<!-- TOC -->

- [ファイルの扱い](#ファイルの扱い)
		- [まず](#まず)
		- [ファイルを開く](#ファイルを開く)

<!-- /TOC -->

### まず
ファイルは読み書きそろって初めて使える。
まずはひととおりファイル関数の説明を行い、ファイルを使った読み書きのサンプルコードを試す。

### ファイルを開く
ファイル入出力はfopen()関数を使う
> FILE *fopen(
> 	const char * restrict ファイルパス,
> 	const char * モード
> );

| モード | ファイル |            機能            | ファイルがないとき |
|------|--------|--------------------------|------------------|
| "r"    | テキスト | 読み取り                   | エラー             |
| "w"    | テキスト | 書き込み                   | 新規作成           |
| "a"    | テキスト | 追加書き込み               | 新規作成           |
| "rb"   | バイナリ | 読み取り                   | エラー             |
| "wb"   | バイナリ | 書き込み                   | 新規作成           |
| "ab"   | バイナリ | 追加書き込み               | 新規作成           |
| "r+"   | テキスト | 更新(読み取り及び書き込み) | エラー             |
| "w+"   | テキスト | 更新(読み取り及び書き込み) | 新規作成           |
| "a+"   | テキスト | 更新(追加書き込み)         | 新規作成           |

戻り値は、FILE型のポインタ。FILE型の変数は実体ではなくポインタだけを宣言する必要がある。
この時戻り値として得られるポインタは内部的にどこから持ってきたメモリ領域を割りつける。
これはmalloc()関数に似ているが動作が違うようなのでfree()で解放せずfclose()で後始末する

> int fclose(
> 	FILE *stream
> );

fwrite_test.c
```C
#include<stdio.h>

#define FILE_NAME_DAT "test.dat"
#define FILE_NAME_TXT "test.txt"

int main(int argc, char const *argv[])
{
	int array[20];
	FILE *fp;
	size_t write_num;

	for (int i = 0; i < (sizeof(array)/sizeof(array[0])); i++)
	{
		array[i] = i;
		printf("%3d", array[i]);
	}
	printf("\n");
	
	fp = fopen(FILE_NAME_DAT, "w");
	if (fp == NULL)
	{
		fprintf(stdout, "open file error\n");
		return 0;
	}
	
	write_num = fwrite(array, sizeof(int), 20, fp);
	if (write_num != 20)
	{
		fprintf(stdout, "write file error\n");
		fclose(fp);
		return 0;
	}
	fprintf(stdout, "%s complete\n", FILE_NAME_DAT);
	fclose(fp);
	
	fp = fopen(FILE_NAME_TXT, "a");
	if (fp == NULL)
	{
		fprintf(stdin, "text file open error\n");
		return 0;
	}
	
	write_num = fwrite(array, sizeof(int), 20, fp);
	if (write_num != 20)
	{
		fprintf(stdout, "write file error\n");
		fclose(fp);
		return 0;
	}
	fprintf(stdout, "%s complete\n", FILE_NAME_TXT);
	fclose(fp);
	
	return 0;
}
```
実行結果
```
  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
test.dat complete
test.txt complete
```
fread_test.c
```C
#include<stdio.h>

#define FILE_NAME_DAT "test.dat"
#define FILE_NAME_TXT "test.txt"

int main(int argc, char const *argv[])
{
	int array[20];
	size_t read_num;
	FILE *fp;

	fp = fopen(FILE_NAME_DAT, "r");
	if (fp == NULL)
	{
		fprintf(stdout, "open file error\n");
		return 0;
	}
	
	read_num = fread(array, sizeof(int), 20, fp);
	if (read_num != 20)
	{
		fclose(fp);
		return 0;
	}
	
	for (int i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		fprintf(stdout, "%3d", array[i]);
	}
	puts("");
	fprintf(stdout, "%s fread compleate\n", FILE_NAME_DAT);
	fclose(fp);

	fp = fopen(FILE_NAME_TXT, "r");
	if (fp == NULL)
	{
		fprintf(stdout, "open file error\n");
		return 0;
	}
	
	read_num = fread(array, sizeof(int), 20, fp);
	if (read_num != 20)
	{
		fclose(fp);
		return 0;
	}
	
	for (int i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		fprintf(stdout, "%3d", array[i]);
	}
	puts("");
	fprintf(stdout, "%s fread compleate\n", FILE_NAME_TXT);
	fclose(fp);

	return 0;
}

```
実行結果
```
  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
test.dat fread compleate
  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
test.txt fread compleate
```
