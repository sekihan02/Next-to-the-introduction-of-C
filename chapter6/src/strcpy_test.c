#include<stdio.h>

char *my_strcpy(char *s1, char *s2)
{
	char *save = s1;
	for (; (*s1 = *s2); s1++, s2++);
	return save;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	my_strcpy(argv[1], argv[2]);
	fprintf(stdout, "%s\n", argv[1]);
	fprintf(stdout, "%s\n", my_strcpy(argv[1], argv[2]));
	return 0;
}
