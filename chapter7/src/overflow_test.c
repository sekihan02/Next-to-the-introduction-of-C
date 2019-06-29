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

	fprintf(stdout, "argv %dbyte\n", strlen(argv[1]));
	fprintf(stdout, "buffer_one arg address:%p, string:%s\n", buffer_one, buffer_one);
	fprintf(stdout, "buffer_two arg address:%p, string:%s\n", buffer_two, buffer_two);

	return 0;
}
