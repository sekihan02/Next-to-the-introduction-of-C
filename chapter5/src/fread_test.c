#include<stdio.h>

#define FILE_NAME_DAT "test.dat"
#define FILE_NAME_TXT "test.txt"

int main(int argc, char const *argv[])
{
	int array[20];
	size_t read_num;
	FILE *fp;

	fp = fopen(FILE_NAME_DAT, "r");
	if (fp == NULL)
	{
		fprintf(stdout, "open file error\n");
		return 0;
	}
	
	read_num = fread(array, sizeof(int), 20, fp);
	if (read_num != 20)
	{
		fclose(fp);
		return 0;
	}
	
	for (int i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		fprintf(stdout, "%3d", array[i]);
	}
	puts("");
	fprintf(stdout, "%s fread compleate\n", FILE_NAME_DAT);
	fclose(fp);

	fp = fopen(FILE_NAME_TXT, "r");
	if (fp == NULL)
	{
		fprintf(stdout, "open file error\n");
		return 0;
	}
	
	read_num = fread(array, sizeof(int), 20, fp);
	if (read_num != 20)
	{
		fclose(fp);
		return 0;
	}
	
	for (int i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		fprintf(stdout, "%3d", array[i]);
	}
	puts("");
	fprintf(stdout, "%s fread compleate\n", FILE_NAME_TXT);
	fclose(fp);

	return 0;
}
