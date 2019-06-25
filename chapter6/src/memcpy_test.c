#include <stdio.h>
#include <stdlib.h>

void *my_memcpy(char *s1, char *s2, int n)
{
	for (int i = 0; i < n; i++)
	{
		*s1++ = *s2++;
	}
	return s1;
}

int main(int argc, char *argv[])
{

	if (argc < 3)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	my_memcpy(argv[1], argv[2], atoi(argv[3]));
	fprintf(stdout, "%s\n", argv[1]);

	return 0;
}
