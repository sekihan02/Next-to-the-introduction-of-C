# Makefileとプログラムの分割
<!-- TOC -->

- [Makefileとプログラムの分割](#makefileとプログラムの分割)
		- [プログラムの分割](#プログラムの分割)
		- [make Makefile](#make-makefile)
			- [Makefileの実行方法](#makefileの実行方法)
		- [ファイルを分割したプログラムを作る](#ファイルを分割したプログラムを作る)
				- [Makefileの書き方](#makefileの書き方)
				- [コマンドライン引数](#コマンドライン引数)

<!-- /TOC -->

### プログラムの分割
複数人による並行開発では、一つのアプリケーションを部品ごとに分けて開発を行う。
分けたプログラムはコンパイルして実行形式にビルドする際に、順番や設定ファイルの設定をコマンドを組み合わせて行う。
コンパイルのたびに適切な引数でコマンドを実行するのは手間で無駄なので、ビルドを自動化するツールmakeを利用する。

### make Makefile
Cプログラムの分割コンパイルは、以下の流れで行う。
1. ソースコードをコンパイル、オブジェクトコードを生成
2. オブジェクトコードをリンクし、実行形式を生成

makeではこの流れを理解し、部分的に変更があった時には最低限必要な処理だけを実施してくれる。
makeはビルドの自動化、そして大規模なプロジェクトでは、ビルドの時間短縮にもなるツール。

### Makefileの実行方法
makeを使用するためには、Makefileという名前のファイルに内容を書いたうえで、
Makefileのあるディレクトリにterminalを移動し、以下のコマンドを実行するとビルドが実行される
```bash
make
```
Makefileが同一のディレクトリに複数ある時は、make コマンドの後ろに-fオブジェクトで名前を指定して以下のようにビルドを行う。Makefile名はMakefile.firstとした
```bash
make -f Makefile.first
```

### ファイルを分割したプログラムを作る
 以下の単純な二つのプログラムとMakefileをsrcディレクトリに作り試してみる。

- print1.c
```C
/* print1 */
/* Hello, Worldを出力する */

#include<stdio.h>

/* funchello */
/* 引数　：なし */
/* 戻り値：なし */
void funchello() {
	fprintf(stdout, "Hello, World ");
}
```
- print2.c
```C
/* print2 */
/* Split, fileを出力する */

#include<stdio.h>

/* funcfile */
/* 引数　：なし */
/* 戻り値：なし */
void funcfile() {
	fprintf(stdout, "Split, file.\n");
}

int main()
{
	funchello();
	funcfile();
	return 0;
}
```
- print.mk
```Makefile
PROGRAM =	print
OBJS    =	print1.o print2.o
SRCS    =	$(OBJS:%.o=%.c)
CC      =	gcc
CFLAGS  =	-g -O0 -Wall
LDFLAGS =


$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	$(RM) *.o
```
以下のコマンドでビルド
```
make -f print.mk
```
結果
```
$ make -f print.mk
gcc -g -O0 -Wall   -c -o print1.o print1.c
gcc -g -O0 -Wall   -c -o print2.o print2.c
print2.c: In function 'main':
print2.c:15:2: warning: implicit declaration of function 'funchello' [-Wimplicit-function-declaration]
  funchello();
  ^~~~~~~~~
gcc -g -O0 -Wall -lm -o print print1.o print2.o
```
print2.cでfunchello()という関数って何？言われた。
funchello()はprint1.cにある関数、print2.cが知っているはずがない。
インクルードして教えれば警告は解消しそう。
実行ファイルはできているし多分動作も問題ないがせっかくなのでヘッダーファイルも作る

- func.h
```h
void funchello();
```
print2.cをインクルードするように変更する
- print2.c
```C
/* print2 */
/* Split, fileを出力する */

#include <stdio.h>
#include "func.h"

/* funcfile */
/* 引数　：なし */
/* 戻り値：なし */
void funcfile() {
	fprintf(stdout, "Split, file.\n");
}

int main()
{
	funchello();
	funcfile();
	return 0;
}
```
もう一度makeを実行する
```bash
$ make -f print.mk
gcc -g -O0 -Wall   -c -o print1.o print1.c
gcc -g -O0 -Wall   -c -o print2.o print2.c
gcc -g -O0 -Wall  -o print print1.o print2.o
rm -f *.o
```
生成された実行ファイルを起動する

```bash
$ ./print
Hello, World Split, file.
```
実行できたのでMakefileに追加をして実行ファイルを消せるようにする
- print.mk
```Makefile
PROGRAM =	print
OBJS    =	print1.o print2.o
SRCS    =	$(OBJS:%.o=%.c)
CC      =	gcc
CFLAGS  =	-g -O0 -Wall
LDFLAGS =


$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	$(RM) *.o

clean:
	@rm -rf *.exe *.o *~
```
一応exeファイルと出力されていない中間ファイルも削除している
実行するには以下のコマンドを入力
```bash
make -f Makefile.first clean
```
##### Makefileの書き方

Makefileにはいろいろな書き方があるが比較的シンプルなものを調べた

| 項目 | 説明 |
|---|---|
| PROGRAM | プログラム名 |
| OBJS | リンクするオブジェクトファイル名<br>スペース区切りで列挙 |
| SRCS | コードのファイル名を |
| CFLAGS | コンパイルのオプションを指定 |
| LDFLAGS | リンカのオプションを指定 |
| $(PROGRAM) | プログラムの生成方法を記述 |
| clean: | Makefile実行コマンドの後にcleanをつけることで実行できる |

##### コマンドライン引数
コマンドライン引数は実行ファイルに続いて半角スペースを空け、コマンドを入力するとその内容がmain()の引数として渡される
具体的にはargcに渡された引数の数、argvがコマンドラインの引数の実体となる

コマンドラインの引数を表示するプログラムは以下
```C
#include<stdio.h>

int main(int argc, char const *argv[])
{
	fprintf(stdout, "argc %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		fprintf(stdout, "argv[%d] %s\n", i, argv[i]);
	}
	
	return 0;
}

```
実行例と結果
```
>argc_argv.exe 123 hello world "HELLO WORLD"
argc 5
argv[0] argc_argv.exe
argv[1] 123
argv[2] hello
argv[3] world
argv[4] HELLO WORLD
```
