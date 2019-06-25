#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	char s2[] = "hello, string";
	// char s1[sizeof(s2) + 6] = "s2 is ";
	char s1[6] = "s2 is ";

	strcpy((&s1[0]+6), s2);

	fprintf(stdout, "s1 is %s\n", s1);

	return 0;
}
