# ビット演算
<!-- TOC -->

- [ビット演算](#ビット演算)
		- [どこで使う？](#どこで使う)

<!-- /TOC -->

### どこで使う？
---
ビット演算はデータ量を少なく済ませることができ、計算コストを抑えることができるので、計算リソースが限られている組み込み分野ではデータの設定で使われる。

C言語のビット演算は以下の表記を使う。

| 演算 | C言語での表記 |
|--|--|
|ビット反転|~|
|左ビットシフト|<<|
|右ビットシフト|>>|
|ビットAND|&|
|ビットOR|||
|ビットOR|^|


```C
#include <stdio.h>

int main() {
	char a = 0;

	a = 0;
	fprintf(stdout, "%x\n", a);
	a = -1;
	fprintf(stdout, "%x\n\n", a);

	/* ビット反転 */
	a = ~0;
	fprintf(stdout, "%x\n", a);
	a = ~1;
	fprintf(stdout, "%x\n", a);
	a = ~-1;
	fprintf(stdout, "%x\n", a);

	return 0;
}
```

```Makefile
PROGRAM =	bit1
OBJS    =	bit1.o
SRCS    =	$(OBJS:%.o=%.c)
CC      =	gcc
CFLAGS  =	-g -O0 -Wall
LDFLAGS =


$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	$(RM) *.o

clean:
	@rm -rf *.exe
```

実行結果例
```
$ ./bit1.exe
0
ffffffff

ffffffff
fffffffe
0
```