#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char s1[] = "s2 is ";
	char s2[] = "hello, string";

	strcat(s1, s2);

	fprintf(stdout, "%s\n", s1);

	return 0;
}
