# 1. 動くだけから先へ

<!-- TOC -->

- [1. 動くだけから先へ](#1-動くだけから先へ)
	- [1.1. はじめに](#11-はじめに)
	- [1.2. 全体像を見る](#12-全体像を見る)
	- [1.3. サンプルコードを動かしてみる](#13-サンプルコードを動かしてみる)
	- [1.4. objdump](#14-objdump)
	- [1.5. GDB](#15-gdb)

<!-- /TOC -->

---

## 1.1. はじめに
---
ここまで標準Cライブラリを実装してみたことで
なんとなく動くものは作れるようになったような幻覚が見えるようになったので
その先を見ようと思います。

## 1.2. 全体像を見る
---
プログラム言語で書かれたソースコードはしょせんコンパイルされる木ねじと素材の集まりです。
つまり、コードは実行可能な状態であるバイナリファイルにコンパイルされる無ければ何もできません。
コンパイルされ、a.outのようなマシンごで書かれたバイナリファイルが実行されて初めて機械は動きだします。
ここからはlinux OS であるraspberrypiを使いCPUの動作を見ていこうと思う

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
$ make -f hello_world.mk 
gcc -g -O0 -Wall   -c -o hello_world.o hello_world.c
gcc -g -O0 -Wall  -o hello_world hello_world.o 
rm -f *.o
$ ./hello_world
Hello world
```

## 1.4. objdump
---
C言語などでコンパイルを行うとできるバイナリファイルがどのようにコンパイルされているのかを見る方法としてobjdumpがある。
これを使い、hello_worldの中身を見てみる
```
$ objdump -D hello_world | grep -A20 main.:
00010464 <main>:
   10464:	e92d4800 	push	{fp, lr}
   10468:	e28db004 	add	fp, sp, #4
   1046c:	e24dd008 	sub	sp, sp, #8
   10470:	e50b0008 	str	r0, [fp, #-8]
   10474:	e50b100c 	str	r1, [fp, #-12]
   10478:	e59f3020 	ldr	r3, [pc, #32]	; 104a0 <main+0x3c>
   1047c:	e5933000 	ldr	r3, [r3]
   10480:	e3a0200c 	mov	r2, #12
   10484:	e3a01001 	mov	r1, #1
   10488:	e59f0014 	ldr	r0, [pc, #20]	; 104a4 <main+0x40>
   1048c:	ebffff9e 	bl	1030c <fwrite@plt>
   10490:	e3a03000 	mov	r3, #0
   10494:	e1a00003 	mov	r0, r3
   10498:	e24bd004 	sub	sp, fp, #4
   1049c:	e8bd8800 	pop	{fp, pc}
   104a0:	00021028 	andeq	r1, r2, r8, lsr #32
   104a4:	00010518 	andeq	r0, r1, r8, lsl r5

000104a8 <__libc_csu_init>:
   104a8:	e92d47f0 	push	{r4, r5, r6, r7, r8, r9, sl, lr}

```
objdumpは大量の出力をするため指定した文字列を含む行を抽出するgrepを使いobjdumpの出力をmain.:文字列以降最大20行を表示する。
個人的にintel表示のほうが見やすいので表示する
```
$ objdump -M intel -D hello_world | grep -A20 main.:
Unrecognised disassembler option: intel
00010464 <main>:
   10464:	e92d4800 	push	{fp, lr}
   10468:	e28db004 	add	fp, sp, #4
   1046c:	e24dd008 	sub	sp, sp, #8
   10470:	e50b0008 	str	r0, [fp, #-8]
   10474:	e50b100c 	str	r1, [fp, #-12]
   10478:	e59f3020 	ldr	r3, [pc, #32]	; 104a0 <main+0x3c>
   1047c:	e5933000 	ldr	r3, [r3]
   10480:	e3a0200c 	mov	r2, #12
   10484:	e3a01001 	mov	r1, #1
   10488:	e59f0014 	ldr	r0, [pc, #20]	; 104a4 <main+0x40>
   1048c:	ebffff9e 	bl	1030c <fwrite@plt>
   10490:	e3a03000 	mov	r3, #0
   10494:	e1a00003 	mov	r0, r3
   10498:	e24bd004 	sub	sp, fp, #4
   1049c:	e8bd8800 	pop	{fp, pc}
   104a0:	00021028 	andeq	r1, r2, r8, lsr #32
   104a4:	00010518 	andeq	r0, r1, r8, lsl r5

000104a8 <__libc_csu_init>:
   104a8:	e92d47f0 	push	{r4, r5, r6, r7, r8, r9, sl, lr}

```
## 1.5. GDB
GDBはデバッガで
