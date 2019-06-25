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
