# ダブルポインタとトリプルポインタ
<!-- TOC -->

- [ダブルポインタとトリプルポインタ](#ダブルポインタとトリプルポインタ)
		- [なに](#なに)
- [多次元配列](#多次元配列)
		- [ポインタのキャスト](#ポインタのキャスト)

<!-- /TOC -->

### なに
---

- ダブルポインタ：
	ポインタ変数のアドレスを格納できるポインタ変数
- トリプルポインタ:
	ポインタ変数のアドレスを格納したポインタ変数のアドレスを格納するポインタ変数

よくわからないのでコード
- ptr_double
```C
#include <stdio.h>

int main(int argc, char const *argv[])
{
	char array[] = {'A', 'B', 'C', '\0'};
	
	char *ptr = array;
	char **ptr_double = &ptr;
	char ***ptr_triple = &ptr_double;

	puts("配列の表示");
	printf("array %p\n", array);
	printf("array %s\n", array);
	for (int i = 0; i < sizeof(array); i++)
	{
		printf("array[%d] %c\n", i, array[i]);
	}
	
	puts("\nポインタの表示");
	fprintf(stdout, "ptr %p\n", ptr);
	fprintf(stdout, "&ptr %p\n", &ptr);
	fprintf(stdout, "ptr %s\n", ptr);
	for (int i = 0; i < sizeof(ptr); i++)
	{
		fprintf(stdout, "*(ptr + %d) %c\n", i, *(ptr+i));
	}

	puts("\nダブルポインタの表示");
	fprintf(stdout, "ptr_double %p\n", ptr_double);
	fprintf(stdout, "&ptr_double %p\n", &ptr_double);
	fprintf(stdout, "*ptr_double %s\n", *ptr_double);

	fprintf(stdout, "ptr_double %s\n", ptr_double);
	
	for (int i = 0; i < sizeof(*ptr_double); i++)
	{
		fprintf(stdout, "*(*ptr_double + %d) %c\n", i, *(*ptr_double+i));
	}

	puts("\nトリプルポインタの表示");
	fprintf(stdout, "ptr_triple %p\n", ptr_triple);
	fprintf(stdout, "**ptr_triple %s\n", **ptr_triple);
	for (int i = 0; i < sizeof(**ptr_triple); i++)
	{
		fprintf(stdout, "*(**ptr_triple + %d) %c\n", i, *(**ptr_triple+i));
	}
	
	return 0;
}

```
実行結果例
```
驟榊・縺ｮ陦ｨ遉ｺ
array 0061FF14
array ABC
array[0] A
array[1] B
array[2] C
array[3]

繝昴う繝ｳ繧ｿ縺ｮ陦ｨ遉ｺ
ptr 0061FF14
&ptr 0061FF18
ptr ABC
*(ptr + 0) A
*(ptr + 1) B
*(ptr + 2) C
*(ptr + 3)

繝繝悶Ν繝昴う繝ｳ繧ｿ縺ｮ陦ｨ遉ｺ
*ptr_double 0061FF14
&ptr_double 0061FF1C
*ptr_double ABC
ptr_double a
*(*ptr_double + 0) A
*(*ptr_double + 1) B
*(*ptr_double + 2) C
*(*ptr_double + 3)

繝医Μ繝励Ν繝昴う繝ｳ繧ｿ縺ｮ陦ｨ遉ｺ
**ptr_triple 0061FF14
**ptr_triple ABC
*(**ptr_triple + 0) A
*(**ptr_triple + 1) B
*(**ptr_triple + 2) C
*(**ptr_triple + 3)
```
array, ptr, *ptr_double, **ptr_tripleで同じアドレスを表示し、%sで文字列ABCと表示される。
ダブルポインタは多次元配列をポインタで表すときや関数からポインタをもらうときに使ったことがある。

# 多次元配列
---

表のようなデータを使うときは2次元配列を利用する。
Cには多次元配列は存在しないが配列の配列として配列を宣言することで実現する

次のような表をソースで書いてみる
()
|   | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| 0 | 1 | 2 | 3 | 4 | 5 |
| 1 | 2  | 4 |  |   |   |
| 2 |   |   |   |   |   |
| 3 |   |   |   |   |   |
| 4 |   |   |   |   | 16 |

```C
#include<stdio.h>

#define MAX_NUM 10

int make_tuple(int tuple[MAX_NUM][MAX_NUM]);

int main(int argc, char const *argv[])
{
	int tuple[MAX_NUM][MAX_NUM] = {{0}};	// MAX_NUM×MAX_NUMの多次元配列0で初期化
	int err_check;

	err_check = make_tuple(tuple);

	if (err_check == -1)
	{
		perror("Not Display");
		return 0;
	}
	
	for (int i = 0; i < MAX_NUM; i++)
	{
		for (int j = 0; j < MAX_NUM; j++)
		{
			fprintf(stdout, " %3d", tuple[i][j]);
		}
		fprintf(stdout, "\n");
	}

	return 0;
}

int make_tuple(int tuple[][MAX_NUM])
{
	if (tuple == NULL)
	{
		return -1;
	}

	for (int i = 0; i < MAX_NUM; i++)
	{
		for (int j = 0; j < MAX_NUM; j++)
		{
			tuple[i][j] = (i+1)*(j+1);
		}
	}
	return 0;
}
```
実行結果例
```
   1   2   3   4   5   6   7   8   9  10
   2   4   6   8  10  12  14  16  18  20
   3   6   9  12  15  18  21  24  27  30
   4   8  12  16  20  24  28  32  36  40
   5  10  15  20  25  30  35  40  45  50
   6  12  18  24  30  36  42  48  54  60
   7  14  21  28  35  42  49  56  63  70
   8  16  24  32  40  48  56  64  72  80
   9  18  27  36  45  54  63  72  81  90
  10  20  30  40  50  60  70  80  90 100
```

### ポインタのキャスト
---

ポインタの値はただのアドレスでしかないもののCコンパイラはポインタに対してデータ型を要求する。
```C
#include<stdio.h>

int main(int argc, char const *argv[])
{
	char char_array[] = {'a', 'b', 'c', 'd', 'e'};
	int int_array[] = {1, 2, 3, 4, 5};

	char *char_pointer;
	int *int_pointer;

	char *char_ptr;
	int *int_ptr;

	char *char_ptr2;
	int *int_ptr2;

	char *char_ptr3;
	int *int_ptr3;

	char_pointer = char_array;
	int_pointer = int_array;

	char_ptr = int_array;
	int_ptr = char_array;

	char_ptr2 = (char *)int_array;
	int_ptr2 = (int *)char_array;

	char_ptr3 = (char *)int_array;
	int_ptr3 = (int *)char_array;

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %d\n", int_pointer, *int_pointer);
		int_pointer += 1;
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %c\n", char_pointer, *char_pointer);
		char_pointer += 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %c\n", int_ptr, *int_ptr);
		int_ptr += 1;
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %d\n", char_ptr, *char_ptr);
		char_ptr += 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %c\n", int_ptr2, *int_ptr2);
		int_ptr2 += 1;
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %d\n", char_ptr2, *char_ptr2);
		char_ptr2 += 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %c\n", int_ptr3, *int_ptr3);
		int_ptr3 = (int *)((char *)int_ptr3 + 1);
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %d\n", char_ptr3, *char_ptr3);
		char_ptr3 = (char *)((int *)char_ptr3 + 1);
	}
	return 0;
}

```
実行例
```
>ptr_type.exe
num_pointer is 0061FF0C, num is 1
num_pointer is 0061FF10, num is 2
num_pointer is 0061FF14, num is 3
num_pointer is 0061FF18, num is 4
num_pointer is 0061FF1C, num is 5
str_pointer is 0061FF07, str is a
str_pointer is 0061FF08, str is b
str_pointer is 0061FF09, str is c
str_pointer is 0061FF0A, str is d
str_pointer is 0061FF0B, str is e

num_pointer is 0061FF07, num is a
num_pointer is 0061FF0B, num is e
num_pointer is 0061FF0F, num is
num_pointer is 0061FF13, num is
num_pointer is 0061FF17, num is
str_pointer is 0061FF0C, str is 1
str_pointer is 0061FF0D, str is 0
str_pointer is 0061FF0E, str is 0
str_pointer is 0061FF0F, str is 0
str_pointer is 0061FF10, str is 2

num_pointer is 0061FF07, num is a
num_pointer is 0061FF0B, num is e
num_pointer is 0061FF0F, num is
num_pointer is 0061FF13, num is
num_pointer is 0061FF17, num is
str_pointer is 0061FF0C, str is 1
str_pointer is 0061FF0D, str is 0
str_pointer is 0061FF0E, str is 0
str_pointer is 0061FF0F, str is 0
str_pointer is 0061FF10, str is 2

num_pointer is 0061FF07, num is a
num_pointer is 0061FF08, num is b
num_pointer is 0061FF09, num is c
num_pointer is 0061FF0A, num is d
num_pointer is 0061FF0B, num is e
str_pointer is 0061FF0C, str is 1
str_pointer is 0061FF10, str is 2
str_pointer is 0061FF14, str is 3
str_pointer is 0061FF18, str is 4
str_pointer is 0061FF1C, str is 5

```
実行結果はループ内でポインタに1を加算しながら表示を行う。
ポインタには1という値を加算しているだけだが、ポインタのアドレスはintとcharで違った量だけインクリメントされている。(文字は1byte整数は4byte)
また、ポインタに整合性のない型の値が格納されているアドレスを代入しようとするとコンパイラが警告を出す。
ただ、あくまで警告なので実行ファイルはできるし、もちろん実行できる(想定している結果にはならないと思うが)。
この警告はキャストを使いポインタの型をその場で変更すると表示されない。(実行結果はキャストしなかったときと同じになる)

ポインタに整合性の無い型の値が格納されたアドレスを代入すると思わぬところにアクセスしてしまう。
これはキャストを使い、ポインタの型をその場で変更することで回避できる。
