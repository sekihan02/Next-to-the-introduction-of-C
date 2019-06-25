#include<stdio.h>

#define FILE_NAME_DAT "test.dat"
#define FILE_NAME_TXT "test.txt"

int main(int argc, char const *argv[])
{
	int array[20];
	FILE *fp;
	size_t write_num;

	for (int i = 0; i < (sizeof(array)/sizeof(array[0])); i++)
	{
		array[i] = i;
		printf("%3d", array[i]);
	}
	printf("\n");
	
	fp = fopen(FILE_NAME_DAT, "w");
	if (fp == NULL)
	{
		fprintf(stdout, "open file error\n");
		return 0;
	}
	
	write_num = fwrite(array, sizeof(int), 20, fp);
	if (write_num != 20)
	{
		fprintf(stdout, "write file error\n");
		fclose(fp);
		return 0;
	}
	fprintf(stdout, "%s complete\n", FILE_NAME_DAT);
	fclose(fp);
	
	fp = fopen(FILE_NAME_TXT, "a");
	if (fp == NULL)
	{
		fprintf(stdin, "text file open error\n");
		return 0;
	}
	
	write_num = fwrite(array, sizeof(int), 20, fp);
	if (write_num != 20)
	{
		fprintf(stdout, "write file error\n");
		fclose(fp);
		return 0;
	}
	fprintf(stdout, "%s complete\n", FILE_NAME_TXT);
	fclose(fp);
	
	return 0;
}

