#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char str[20];
	char *pointer;
	char *ptr;
	strcpy(str, "Hello, world!\n");
	pointer = str;
	fprintf(stdout, "%s", pointer);

	ptr = pointer +2;
	strcpy(ptr, "y ogottehosiiyade\n");
	fprintf(stdout, "%s", pointer);

	return 0;
}
