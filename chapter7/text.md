# 1. 動くだけから先へ

<!-- TOC -->

- [1. 動くだけから先へ](#1-動くだけから先へ)
	- [1.1. はじめに](#11-はじめに)
	- [1.2. 全体像を見る](#12-全体像を見る)
	- [1.3. サンプルコードを動かしてみる](#13-サンプルコードを動かしてみる)
	- [1.4. objdump](#14-objdump)
	- [1.5. GDB](#15-gdb)
	- [オーバーフロー](#オーバーフロー)

<!-- /TOC -->

---

## 1.1. はじめに
---
ここまで標準Cライブラリを実装してみたことで
なんとなく動くものは作れるようになったような幻覚が見えるようになったので
その先を見ようと思います。

## 1.2. 全体像を見る
---
プログラム言語で書かれたソースコードはしょせんコンパイルされる木ねじと素材の集まり。
つまり、コードは実行可能な状態であるバイナリファイルにコンパイルされる無ければ何もできない
コンパイルされ、a.outのようなマシンごで書かれたバイナリファイルが実行されて初めて機械は動く

動作は基本的にwindows10を使用するが
ここからは必要に応じてlinux OS であるraspberrypiも使用してCPUの動作を見ようと思う。
raspberrypiを使用するときは適宜そのこと記載する

## 1.3. サンプルコードを動かしてみる
---

C言語でHello worldを表示する以下のサンプルコードを使いバイナリファイルを遊んでみる

hello_world.c
```C
#include<stdio.h>

int main(int argc, char *argv[])
{
	fprintf(stdout, "Hello world\n");
	return 0;
}

```
Makefileは以下のように作成した
hello_world.mk
```
PROGRAM =	hello_world
OBJS    =	hello_world.o
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
makeと実行例は以下
```
>make -f hello_world.mk
gcc -g -O0 -Wall   -c -o hello_world.o hello_world.c
gcc -g -O0 -Wall  -o hello_world hello_world.o
rm -f *.o
>hello_world.exe
Hello world
```

## 1.4. objdump
---
C言語などでコンパイルを行うとできるバイナリファイルがどのようにコンパイルされているのかを見る方法としてobjdumpがある。
これを使い、hello_worldの中身を見てみる
```
>objdump -D hello_world.exe | grep -A20 main.:
00401460 <_main>:
  401460:       55                      push   %ebp
  401461:       89 e5                   mov    %esp,%ebp
  401463:       83 e4 f0                and    $0xfffffff0,%esp
  401466:       83 ec 10                sub    $0x10,%esp
  401469:       e8 62 05 00 00          call   4019d0 <___main>
  40146e:       a1 a0 81 40 00          mov    0x4081a0,%eax
  401473:       83 c0 20                add    $0x20,%eax
  401476:       89 44 24 0c             mov    %eax,0xc(%esp)
  40147a:       c7 44 24 08 0c 00 00    movl   $0xc,0x8(%esp)
  401481:       00
  401482:       c7 44 24 04 01 00 00    movl   $0x1,0x4(%esp)
  401489:       00
  40148a:       c7 04 24 64 50 40 00    movl   $0x405064,(%esp)
  401491:       e8 f2 25 00 00          call   403a88 <_fwrite>
  401496:       b8 00 00 00 00          mov    $0x0,%eax
  40149b:       c9                      leave
  40149c:       c3                      ret
  40149d:       90                      nop
  40149e:       90                      nop
  40149f:       90                      nop
--
004019d0 <___main>:
  4019d0:       a1 28 70 40 00          mov    0x407028,%eax
  4019d5:       85 c0                   test   %eax,%eax
  4019d7:       74 07                   je     4019e0 <___main+0x10>
  4019d9:       f3 c3                   repz ret
  4019db:       90                      nop
  4019dc:       8d 74 26 00             lea    0x0(%esi,%eiz,1),%esi
  4019e0:       c7 05 28 70 40 00 01    movl   $0x1,0x407028
  4019e7:       00 00 00
  4019ea:       eb 94                   jmp    401980 <___do_global_ctors>
  4019ec:       90                      nop
  4019ed:       90                      nop
  4019ee:       90                      nop
  4019ef:       90                      nop

004019f0 <.text>:
  4019f0:       83 ec 1c                sub    $0x1c,%esp
  4019f3:       8b 44 24 24             mov    0x24(%esp),%eax
  4019f7:       83 f8 03                cmp    $0x3,%eax
  4019fa:       74 14                   je     401a10 <.text+0x20>
  4019fc:       85 c0                   test   %eax,%eax

```
objdumpは大量の出力をするため指定した文字列を含む行を抽出するgrepを使いobjdumpの出力をmain.:文字列以降最大20行を表示する。
個人的にintel表示のほうが見やすいので表示する
```
>objdump -M intel -D hello_world.exe | grep -A20 main.:
00401460 <_main>:
  401460:       55                      push   ebp
  401461:       89 e5                   mov    ebp,esp
  401463:       83 e4 f0                and    esp,0xfffffff0
  401466:       83 ec 10                sub    esp,0x10
  401469:       e8 62 05 00 00          call   4019d0 <___main>
  40146e:       a1 a0 81 40 00          mov    eax,ds:0x4081a0
  401473:       83 c0 20                add    eax,0x20
  401476:       89 44 24 0c             mov    DWORD PTR [esp+0xc],eax
  40147a:       c7 44 24 08 0c 00 00    mov    DWORD PTR [esp+0x8],0xc
  401481:       00
  401482:       c7 44 24 04 01 00 00    mov    DWORD PTR [esp+0x4],0x1
  401489:       00
  40148a:       c7 04 24 64 50 40 00    mov    DWORD PTR [esp],0x405064
  401491:       e8 f2 25 00 00          call   403a88 <_fwrite>
  401496:       b8 00 00 00 00          mov    eax,0x0
  40149b:       c9                      leave
  40149c:       c3                      ret
  40149d:       90                      nop
  40149e:       90                      nop
  40149f:       90                      nop
--
004019d0 <___main>:
  4019d0:       a1 28 70 40 00          mov    eax,ds:0x407028
  4019d5:       85 c0                   test   eax,eax
  4019d7:       74 07                   je     4019e0 <___main+0x10>
  4019d9:       f3 c3                   repz ret
  4019db:       90                      nop
  4019dc:       8d 74 26 00             lea    esi,[esi+eiz*1+0x0]
  4019e0:       c7 05 28 70 40 00 01    mov    DWORD PTR ds:0x407028,0x1
  4019e7:       00 00 00
  4019ea:       eb 94                   jmp    401980 <___do_global_ctors>
  4019ec:       90                      nop
  4019ed:       90                      nop
  4019ee:       90                      nop
  4019ef:       90                      nop

004019f0 <.text>:
  4019f0:       83 ec 1c                sub    esp,0x1c
  4019f3:       8b 44 24 24             mov    eax,DWORD PTR [esp+0x24]
  4019f7:       83 f8 03                cmp    eax,0x3
  4019fa:       74 14                   je     401a10 <.text+0x20>
  4019fc:       85 c0                   test   eax,eax
```


## 1.5. GDB
GDBはデバッガ。
デバッガはコンパイルされたプログラムのレジスタの内容を確認したり１ステップずつ実行したりできるツール
以下はプログラム実行直前のレジスタの内容
```
>gdb -q ./hello_world.exe
Reading symbols from C:\github\Next_ intro_of_C\chapter7\src\hello_world.exe...done.
(gdb) set dis intel
Ambiguous set command "dis intel": disable-randomization, disassemble-next-line, disassembly-flavor, disconnected-dprintf...
(gdb) break main
Breakpoint 1 at 0x40146e: file hello_world.c, line 5.
(gdb) run
Starting program: C:\github\Next_ intro_of_C\chapter7\src/./hello_world.exe
[New Thread 5864.0x2bc4]
[New Thread 5864.0x180c]

Breakpoint 1, main (argc=1, argv=0x9415f8) at hello_world.c:5
5               fprintf(stdout, "Hello world\n");
(gdb) info registers
eax            0x1      1
ecx            0x401950 4200784
edx            0x0      0
ebx            0x26c000 2539520
esp            0x61ff20 0x61ff20
ebp            0x61ff38 0x61ff38
esi            0x4012e0 4199136
edi            0x4012e0 4199136
eip            0x40146e 0x40146e <main+14>
eflags         0x202    [ IF ]
cs             0x23     35
ss             0x2b     43
ds             0x2b     43
es             0x2b     43
fs             0x53     83
gs             0x2b     43
(gdb) quit
A debugging session is active.

        Inferior 1 [process 5864] will be killed.

Quit anyway? (y or n) y

error return ../../gdb-7.6.1/gdb/windows-nat.c:1275 was 5

```
break mainでmain関数にブレークポイント設定し、runと実行するとmain()が実行される直前で処理が停止する。
ここでinfo registersとすることでレジスタと現在の状態を見ることができる

set dis intelで出力をIntel形式にすることができる
また、ディレクトリ内で.gdbinitという名前でファイルを作り、コマンドを書いておくことでGDBを起動するたびに設定を実行できる

| レジスタ | 内容 |
|---|---|
| eax | 変数 |
| ecx | 変数 |
| edx | 変数 |
| ebx | 変数 |

```
>gcc -g hello_world.c
>gdb -q a.exe
Reading symbols from C:\github\Next_ intro_of_C\chapter7\src\a.exe...done.
(gdb) set dis intel
Ambiguous set command "dis intel": disable-randomization, disassemble-next-line, disassembly-flavor, disconnected-dprintf...
(gdb) list
1       #include<stdio.h>
2
3       int main(int argc, char *argv[])
4       {
5               fprintf(stdout, "Hello world\n");
6               return 0;
7       }
(gdb) disassemble main
Dump of assembler code for function main:
   0x00401460 <+0>:     push   %ebp
   0x00401461 <+1>:     mov    %esp,%ebp
   0x00401463 <+3>:     and    $0xfffffff0,%esp
   0x00401466 <+6>:     sub    $0x10,%esp
   0x00401469 <+9>:     call   0x4019d0 <__main>
   0x0040146e <+14>:    mov    0x4081a0,%eax
   0x00401473 <+19>:    add    $0x20,%eax
   0x00401476 <+22>:    mov    %eax,0xc(%esp)
   0x0040147a <+26>:    movl   $0xc,0x8(%esp)
   0x00401482 <+34>:    movl   $0x1,0x4(%esp)
   0x0040148a <+42>:    movl   $0x405064,(%esp)
   0x00401491 <+49>:    call   0x403a88 <fwrite>
   0x00401496 <+54>:    mov    $0x0,%eax
   0x0040149b <+59>:    leave
   0x0040149c <+60>:    ret
End of assembler dump.
(gdb) break main
Breakpoint 1 at 0x40146e: file hello_world.c, line 5.
(gdb) run
Starting program: C:\Next_ intro_of_C\chapter7\src/a.exe
[New Thread 8884.0x8cc]
[New Thread 8884.0x300c]

Breakpoint 1, main (argc=1, argv=0x7315f8) at hello_world.c:5
5               fprintf(stdout, "Hello world\n");
(gdb) info registers mov
Invalid register `mov'
(gdb) info registers sub
Invalid register `sub'
(gdb) info register mov
Invalid register `mov'
(gdb) info register eip
eip            0x40146e 0x40146e <main+14>
(gdb)
```
eipレジスタはプログラムが実行している最中の命令をお保持しているメモリアドレスを指すために使われる
gdbでポインタの中身を見てみる
```C
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char str[20];
	char *pointer;
	char *ptr;
	strcpy(str, "Hello, world!\n");
	pointer = str;
	fprintf(stdout, "%s", pointer);

	ptr = pointer +2;
	strcpy(ptr, "y ogottehosiiyade\n");
	fprintf(stdout, "%s", pointer);

	return 0;
}
```
Makefile作るのが面倒なのでコマンドでコンパイル
```
>gcc -g -o pointer pointer.c
>pointer.exe
Hello, world!
Hey ogottehosiiyade

>gdb -q pointer.exe
Reading symbols from C:\github\Next_ intro_of_C\chapter7\src\pointer.exe...done.
(gdb) set dis intel
Ambiguous set command "dis intel": disable-randomization, disassemble-next-line, disassembly-flavor, disconnected-dprintf...
(gdb) list
1       #include <stdio.h>
2       #include <string.h>
3
4       int main(int argc, char const *argv[])
5       {
6               char str[20];
7               char *pointer;
8               char *ptr;
9               strcpy(str, "Hello, world!\n");
10              pointer = str;
(gdb)
11              fprintf(stdout, "%s", pointer);
12
13              ptr = pointer +2;
14              strcpy(ptr, "y ogottehosiiyade\n");
15              fprintf(stdout, "%s", pointer);
16
17              return 0;
18      }
(gdb)
Line number 19 out of range; pointer.c has 18 lines.
(gdb) break 11
Breakpoint 1 at 0x401498: file pointer.c, line 11.
(gdb) run\

Starting program: C:\github\Next_ intro_of_C\chapter7\src/pointer.exe
[New Thread 14000.0x1690]
[New Thread 14000.0x2d1c]

Breakpoint 1, main (argc=1, argv=0xae15f8) at pointer.c:11
11              fprintf(stdout, "%s", pointer);
(gdb) x/xw pointer
0x61ff14:       0x6c6c6548
(gdb) x/s pointer
0x61ff14:       "Hello, world!\n"
(gdb) print pointer
$1 = 0x61ff14 "Hello, world!\n"
(gdb) print &pointer
$2 = (char **) 0x61ff2c
```
11行目にブレークポイントを設置、これはstrに"Hello, world!\n"をコピーし、
その先頭をポインタ変数が設定された直後に処理が止まる。

pointerの内容を文字列として表示してみる
アドレス演算子を使用することで、ポインタ変数が0x61ff2cというアドレスに割り当てられているのがわかる

## オーバーフロー
C言語は簡潔に自由に書くことができ、プログラマがコントロールできる。
これはメリットだがデメリットでもある。
つまり、変数にデータを代入する場合、そのデータが代入先のメモリ領域内に収まっていないプログラムを書き、これを実行してクラッシュさせることもできる。
8byteの領域に10byteのデータを格納してみる

```C
/* 引数に10byte文字与えてクラッシュさせる */

#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char buffer_one[8] = {0};
	char buffer_two[8] = {0};

	strcpy(buffer_one, "one");
	puts("buffer_one strcpy()");
	fprintf(stdout, "buffer_one     address:%p, string:%s\n", buffer_one, buffer_one);
	fprintf(stdout, "buffer_two     address:%p, string:%s\n\n", buffer_two, buffer_two);

	strcpy(buffer_two, "0123456789");
	puts("buffer_two strcpy()");
	fprintf(stdout, "buffer_one num address:%p, string:%s\n", buffer_one, buffer_one);
	fprintf(stdout, "buffer_two num address:%p, string:%s\n\n", buffer_two, buffer_two);

	if (argc <= 1)
	{
		return 0;
	}
	strcpy(buffer_one, argv[1]);
	fprintf(stdout, "buffer_one arg address:%p, string:%s\n", buffer_one, buffer_one);
	fprintf(stdout, "buffer_two arg address:%p, string:%s\n", buffer_two, buffer_two);

	return 0;
}
```
実行例
```
>a.exe 0123456789
buffer_one strcpy()
buffer_one     address:0061FF28, string:one
buffer_two     address:0061FF20, string:

buffer_two strcpy()
buffer_one num address:0061FF28, string:89
buffer_two num address:0061FF20, string:0123456789

argv 10byte
buffer_one arg address:0061FF28, string:0123456789
buffer_two arg address:0061FF20, string:012345670123456789

>a.exe abcdefghij
buffer_one strcpy()
buffer_one     address:0061FF28, string:one
buffer_two     address:0061FF20, string:

buffer_two strcpy()
buffer_one num address:0061FF28, string:89
buffer_two num address:0061FF20, string:0123456789

argv 10byte
buffer_one arg address:0061FF28, string:abcdefghij
buffer_two arg address:0061FF20, string:01234567abcdefghij

>a.exe  111111111111111111111111111111111111111111111111111111111111111111111111111111111
buffer_one strcpy()
buffer_one     address:0061FF28, string:one
buffer_two     address:0061FF20, string:

buffer_two strcpy()
buffer_one num address:0061FF28, string:89
buffer_two num address:0061FF20, string:0123456789

```
メモリのアドレスをみると、buffer_oneはbuffer_twoの後に割り当てられている。
このため、buffer_twoに10byteのデータを格納するとオーバーフローした最後の2byteがbuffer_oneに書き込まれる。
さらに大きなデータを引数に指定すると、プログラムはクラッシュし、異常終了する。
