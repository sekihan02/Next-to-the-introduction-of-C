#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	fprintf(stdout, "hoge geho = %2d\n", strcmp("hoge", "geho"));
	fprintf(stdout, "hoge hoge = %2d\n", strcmp("hoge", "hoge"));
	fprintf(stdout, "geho hoge = %2d\n", strcmp("geho", "hoge"));

	return 0;
}
