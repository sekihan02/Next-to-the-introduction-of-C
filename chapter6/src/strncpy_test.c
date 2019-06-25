#include<stdio.h>

char *my_strncpy(char *s1, char *s2, size_t n)
{
	printf("s1 %s\n",s1);
	printf("s2 %s\n",s2);
	for (size_t i = 0; i < n; i++, s1++, s2++)
	{
		printf("s1 %c\n",*s1);
		printf("s2 %c\n",*s2);

		*s1 = *s2;
	}
	
	return s1;
}

int main(int argc, char *argv[])
{
	int num;
	sscanf(argv[3], "%d", &num);

	if (argc < 3)
	{
		fprintf(stdout, "Few argc error\n");
		return 1;
	}
	printf("s argv[1] %s\n",argv[1]);
	printf("s argv[2] %s\n",argv[2]);
	
	printf("c argv[1] %c\n",*argv[1]);
	printf("c argv[2] %c\n",*argv[2]);
	
	my_strncpy(argv[1], argv[2], num);
	fprintf(stdout, "%s\n", argv[1]);
	return 0;
}
