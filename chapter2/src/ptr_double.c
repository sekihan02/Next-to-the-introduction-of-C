#include <stdio.h>

int main(int argc, char const *argv[])
{
	char array[] = {'A', 'B', 'C', '\0'};
	
	char *ptr = array;
	char **ptr_double = &ptr;
	char ***ptr_triple = &ptr_double;

	puts("配列の表示");
	printf("array %p\n", array);
	printf("array %s\n", array);
	for (int i = 0; i < sizeof(array); i++)
	{
		printf("array[%d] %c\n", i, array[i]);
	}
	
	puts("\nポインタの表示");
	fprintf(stdout, "ptr %p\n", ptr);
	fprintf(stdout, "&ptr %p\n", &ptr);
	fprintf(stdout, "ptr %s\n", ptr);
	for (int i = 0; i < sizeof(array); i++)
	{
		fprintf(stdout, "*(ptr + %d) %c\n", i, *(ptr+i));
	}

	puts("\nダブルポインタの表示");
	fprintf(stdout, "ptr_double %p\n", ptr_double);
	fprintf(stdout, "*ptr_double %p\n", *ptr_double);
	fprintf(stdout, "&ptr_double %p\n", &ptr_double);

	fprintf(stdout, "*ptr_double %s\n", *ptr_double);
		for (int i = 0; i < sizeof(array); i++)
	{
		fprintf(stdout, "*(*ptr_double + %d) %c\n", i, *(*ptr_double+i));
	}

	puts("\nトリプルポインタの表示");
	fprintf(stdout, "ptr_triple %p\n", ptr_triple);

	fprintf(stdout, "**ptr_triple %p\n", **ptr_triple);
	fprintf(stdout, "**ptr_triple %s\n", **ptr_triple);
	for (int i = 0; i < sizeof(array); i++)
	{
		fprintf(stdout, "*(**ptr_triple + %d) %c\n", i, *(**ptr_triple+i));
	}
	
	return 0;
}
