# 1. 標準Cライブラリをなんちゃって実装 libc glibc

<!-- TOC -->

- [1. 標準Cライブラリをなんちゃって実装 libc glibc](#1-標準cライブラリをなんちゃって実装-libc-glibc)
	- [1.1. はじめに](#11-はじめに)
	- [1.2. 標準Cライブラリはどこに](#12-標準cライブラリはどこに)
	- [1.3. 見てみる](#13-見てみる)
	- [1.4. string.h](#14-stringh)
		- [memcpy()](#memcpy)
		- [strcpy()](#strcpy)
		- [strncpy()](#strncpy)

<!-- /TOC -->

---

## 1.1. はじめに
---
ここから標準Cライブラリを見つつ実装をしながらさらにCを使いこなせるようになろうと思う

## 1.2. 標準Cライブラリはどこに
---
標準Cライブラリはどのようなソースで動いているのか興味を持っても自分のPCのどこかにあるという事実以外
どこにソースがあるかわからないかもしれない(とりあえず書いている自分はわからない)

ここでは標準Cライブラリの確認の方法をまとめる

- 1 Glibcをダウンロードする
標準Cライブラリはlibcと呼ばれ、多くのプログラムで共通して使われるような、システムコールを始めとする基本的な「部品」を集めたもの
これはオープンソースで公開され、そのソースコードはダウンロードすることができる
GlibcはLinuxのマシンには標準で入っているGNUが提供する標準Cライブラリ。
これはgitで取得できる。以下コマンド
```
git clone git://sourceware.org/git/glibc.git
```

- 2 Webでソースを見る
Glibcはweb上でも確認できる。さらにUnix系OSのFreeBSDのページはソースを探しやすかったのでリンクを載せる

	* <a href="https://github.com/ceseo/glibc">glibc</a>

	* <a href="https://svnweb.freebsd.org/base/head/lib/libc/">FreeBSD/libc</a>

## 1.3. 見てみる
---

見てみようにも、たくさんのファイルがあって迷子になってしまったのでstrcpy()を見てみようと思う。


- <a href="https://github.com/ceseo/glibc/blob/master/string/strcmp.c">glibc/string/strcmp.c</a>
```C
/* Copyright (C) 1991-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <string.h>

#undef strcmp

#ifndef STRCMP
# define STRCMP strcmp
#endif

/* Compare S1 and S2, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
int
STRCMP (const char *p1, const char *p2)
{
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;

  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
	return c1 - c2;
    }
  while (c1 == c2);

  return c1 - c2;
}
libc_hidden_builtin_def (strcmp)
```

- <a href="https://svnweb.freebsd.org/base/head/lib/libc/string/strcmp.c?revision=326025&view=markup">FreeBSD
libc/string/strcpy.c</a>

```C
/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)strcmp.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <string.h>

/*
 * Compare strings.
 */
int
strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}
```

ライセンス表示が長いのとバージョン情報用の変数もあるが本質は一行。
ほぼコピペだが実装するとこんな感じ
```C
#include <stdio.h>

int my_strcmp(const char *s1, const char *s2)
{
	int i = 0;
	fprintf(stdout, "s1 : %s\n", s1);
	fprintf(stdout, "s2 : %s\n", s2);

	while (*s1 == *s2++)
	{
		fprintf(stdout, "count : %d\n", i);
		
		fprintf(stdout, "s1 : %c\n", *s1);
		fprintf(stdout, "s2 : %c\n", *s2);
		
		if (*s1++ == '\0')
		{
			return 0;
		}
		i++;
	}
	return(*s1 - * (s2-1));
}

int main(int argc, char const *argv[])
{
	int res;

	if (argc < 2)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	res = my_strcmp(argv[1], argv[2]);

	fprintf(stdout, "%d\n", res);
	return 0;
}
```
実行例
```
>strcmp.exe hello hello
s1 : hello
s2 : hello
count : 0
s1 : h
s2 : e
count : 1
s1 : e
s2 : l
count : 2
s1 : l
s2 : l
count : 3
s1 : l
s2 : o
count : 4
s1 : o
s2 :
count : 5
s1 :
s2 : ﾁ
0
>strcmp.exe hello HELLO
s1 : hello
s2 : HELLO
32
>strcmp.exe hello Hello
s1 : hello
s2 : Hello
32
>strcmp.exe hello hells
s1 : hello
s2 : hells
count : 0
s1 : h
s2 : e
count : 1
s1 : e
s2 : l
count : 2
s1 : l
s2 : l
count : 3
s1 : l
s2 : s
-4
```

ソースの内容は意外と違うので読み物として面白いと思う。
次からは自分なりに標準Cライブラリを実装していく

## 1.4. string.h
---

文字列操作関数の定義
| 関数名 | 内容 |
|---|---|
| memcpy | オブジェクトを指定文字数分コピー |
| strcpy | 文字列をコピー |
| strncpy | 文字列を指定文字数分コピー |

### memcpy()

```C
/* Copy memory to memory until the specified number of bytes
   has been copied.  Overlap is NOT handled correctly.
   Copyright (C) 1991-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Torbjorn Granlund (tege@sics.se).
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <string.h>
#include <memcopy.h>

#undef memcpy

void *
memcpy (void *dstpp, const void *srcpp, size_t len)
{
  unsigned long int dstp = (long int) dstpp;
  unsigned long int srcp = (long int) srcpp;

  /* Copy from the beginning to the end.  */

  /* If there not too few bytes to copy, use word copy.  */
  if (len >= OP_T_THRES)
    {
      /* Copy just a few bytes to make DSTP aligned.  */
      len -= (-dstp) % OPSIZ;
      BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

      /* Copy whole pages from SRCP to DSTP by virtual address manipulation,
	 as much as possible.  */

      PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);

      /* Copy from SRCP to DSTP taking advantage of the known alignment of
	 DSTP.  Number of bytes remaining is put in the third argument,
	 i.e. in LEN.  This number may vary from machine to machine.  */

      WORD_COPY_FWD (dstp, srcp, len, len);

      /* Fall out and copy the tail.  */
    }

  /* There are just a few bytes to copy.  Use byte memory operations.  */
  BYTE_COPY_FWD (dstp, srcp, len);

  return dstpp;
}
libc_hidden_builtin_def (memcpy)
```

完全になんちゃって実装
```C
#include <stdio.h>
#include <stdlib.h>

void *my_memcpy(char *s1, char *s2, int n)
{
	for (int i = 0; i < n; i++)
	{
		*s1++ = *s2++;
	}
	return s1;
}

int main(int argc, char *argv[])
{

	if (argc < 3)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	my_memcpy(argv[1], argv[2], atoi(argv[3]));
	fprintf(stdout, "%s\n", argv[1]);

	return 0;
}
```
実行結果
```
>memcpy.exe hello ha 2
hallo
```

### strcpy()
```C
/* Copyright (C) 1991-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <stddef.h>
#include <string.h>

#undef strcpy

#ifndef STRCPY
# define STRCPY strcpy
#endif

/* Copy SRC to DEST.  */
char *
STRCPY (char *dest, const char *src)
{
  return memcpy (dest, src, strlen (src) + 1);
}
libc_hidden_builtin_def (strcpy)
```

```C
/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)strcpy.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <string.h>

char *
strcpy(char * __restrict to, const char * __restrict from)
{
	char *save = to;

	for (; (*to = *from); ++from, ++to);
	return(save);
}
```

\0をループの終了フラグにして処理をコンパクトにしている
```C
#include<stdio.h>

char *my_strcpy(char *s1, char *s2)
{
	char *save = s1;
	for (; (*s1 = *s2); s1++, s2++);
	return save;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	my_strcpy(argv[1], argv[2]);
	fprintf(stdout, "%s\n", argv[1]);
	fprintf(stdout, "%s\n", my_strcpy(argv[1], argv[2]));
	return 0;
}

```
実行例
```
>strcpy.exe 12345 abc
abc
abc
>strcpy.exe       123

>strcpy.exe ----- 12345
12345
12345
```
### strncpy()

```C
/* Copyright (C) 1991-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <string.h>

#undef strncpy

#ifndef STRNCPY
 #define STRNCPY strncpy
#endif

char *
STRNCPY (char *s1, const char *s2, size_t n)
{
  size_t size = __strnlen (s2, n);
  if (size != n)
    memset (s1 + size, '\0', n - size);
  return memcpy (s1, s2, size);
}
libc_hidden_builtin_def (strncpy)
```

```C
#include<stdio.h>

char *my_strncpy(char *s1, char *s2, size_t n)
{
	printf("s1 %s\n",s1);
	printf("s2 %s\n",s2);
	for (size_t i = 0; i < n; i++, s1++, s2++)
	{
		printf("s1 %c\n",*s1);
		printf("s2 %c\n",*s2);

		*s1 = *s2;
	}
	
	return s1;
}

int main(int argc, char *argv[])
{
	int num;
	sscanf(argv[3], "%d", &num);

	if (argc < 3)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	printf("s argv[1] %s\n",argv[1]);
	printf("s argv[2] %s\n",argv[2]);
	
	printf("c argv[1] %c\n",*argv[1]);
	printf("c argv[2] %c\n",*argv[2]);
	
	my_strncpy(argv[1], argv[2], num);
	fprintf(stdout, "%s\n", argv[1]);
	return 0;
}

```
実行例
```
>strncpy.exe 12345 abcdef 3
s argv[1] 12345
s argv[2] abcdef
c argv[1] 1
c argv[2] a
s1 12345
s2 abcdef
s1 1
s2 a
s1 2
s2 b
s1 3
s2 c
abc45
```