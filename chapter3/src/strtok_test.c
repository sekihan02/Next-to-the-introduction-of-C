#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_STR	256

int main(int argc, char const *argv[])
{
	FILE *fp;
	FILE *p1;
	char filename[] = "data.csv";
	char txt[MAX_STR] = {0};

	char p2[MAX_STR];
	char *token;

	fp = fopen(filename, "r");
	// p1 = fopen(filename, "r");

	/* ファイルの表示確認 */
	if (fp == NULL)
	{
		fprintf(stdout, "Not open file");
		return 0;
	}

	printf("%s\n", filename);
	// fgets()でファイルの中を一行ずつ取得してその都度表示する
	while(fgets(txt, 256, fp) != NULL)
	{
		printf("%s\n", txt);
	}
	fclose(fp);
	/*************************/
	puts("strtok_test");
	p1 = fopen(filename, "r");

	while (fgets(p2, 256, p1) != NULL)
	{
		token = strtok(p2, ",");
		printf("code = %s\n", token);
		while ((token = strtok(NULL, ",")) != NULL)
		{
			/* code */
			 printf("code = %s\n", token);
		}
		
	}
	fclose(p1);
	return 0;
}
