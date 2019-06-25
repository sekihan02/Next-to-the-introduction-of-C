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
