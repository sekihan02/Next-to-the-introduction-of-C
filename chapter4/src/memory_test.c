#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	int *one_num;
	char *one_string;
	int *zero_test;

	char str = '1';

	one_num = malloc(sizeof(int)*10);
	one_string = calloc(20, sizeof(char));
	zero_test = calloc(20, sizeof(int));

	// malloc()の表示確認
	for (int i = 0; i < 10; i++)
	{
		one_num[i] = i;
		fprintf(stdout, "%2d", one_num[i]);
	}
	free(one_num);
	one_num = NULL;

	printf("\n");

	// calloc(文字列)の表示確認
	for (int j = 0; j < 20; j++)
	{
		one_string[j] = str;
		fprintf(stdout, "%c", one_string[j]);
	}
	free(one_string);
	one_string = NULL;

	printf("\n");

	// calloc()の表示確認
	for (int k = 0; k < 20; k++)
	{
		fprintf(stdout, "%d", zero_test[k]);
	}
	free(zero_test);
	zero_test = NULL;

	return 0;
}
