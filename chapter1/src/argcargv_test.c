#include<stdio.h>

int main(int argc, char const *argv[])
{
	fprintf(stdout, "argc %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		fprintf(stdout, "argv[%d] %s\n", i, argv[i]);
	}
	
	return 0;
}
