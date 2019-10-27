# include <stdio.h>

int main(int argc, char const *argv[])
{
	int a = 5;
	int b = 10;
	int *a_p;

	a_p = &a;
	printf("a = %d\n", a);
	printf("a_p = %d\n", *a_p);

	*a_p = b;
	printf("a_p = %d\n", *a_p);
	printf("a = %d\n", a);
	printf("b = %d\n", b);


	return 0;
}
