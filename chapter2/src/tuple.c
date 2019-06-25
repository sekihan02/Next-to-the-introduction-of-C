#include<stdio.h>

#define MAX_NUM 10

int make_tuple(int tuple[MAX_NUM][MAX_NUM]);

int main(int argc, char const *argv[])
{
	int tuple[MAX_NUM][MAX_NUM] = {{0}};	// MAX_NUM×MAX_NUMの多次元配列0で初期化
	int err_check;

	err_check = make_tuple(tuple);

	if (err_check == -1)
	{
		perror("Not Display");
		return 0;
	}
	
	for (int i = 0; i < MAX_NUM; i++)
	{
		for (int j = 0; j < MAX_NUM; j++)
		{
			fprintf(stdout, " %3d", tuple[i][j]);
		}
		fprintf(stdout, "\n");
	}

	return 0;
}

int make_tuple(int tuple[][MAX_NUM])
{
	if (tuple == NULL)
	{
		return -1;
	}

	for (int i = 0; i < MAX_NUM; i++)
	{
		for (int j = 0; j < MAX_NUM; j++)
		{
			tuple[i][j] = (i+1)*(j+1);
		}
	}
	return 0;
}
