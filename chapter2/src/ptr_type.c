#include<stdio.h>

int main(int argc, char const *argv[])
{
	char char_array[] = {'a', 'b', 'c', 'd', 'e'};
	int int_array[] = {1, 2, 3, 4, 5};

	char *char_pointer;
	int *int_pointer;

	char *char_ptr;
	int *int_ptr;

	char *char_ptr2;
	int *int_ptr2;

	char *char_ptr3;
	int *int_ptr3;

	char_pointer = char_array;
	int_pointer = int_array;

	char_ptr = int_array;
	int_ptr = char_array;

	char_ptr2 = (char *)int_array;
	int_ptr2 = (int *)char_array;

	char_ptr3 = (char *)int_array;
	int_ptr3 = (int *)char_array;

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %d\n", int_pointer, *int_pointer);
		int_pointer += 1;
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %c\n", char_pointer, *char_pointer);
		char_pointer += 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %c\n", int_ptr, *int_ptr);
		int_ptr += 1;
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %d\n", char_ptr, *char_ptr);
		char_ptr += 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %c\n", int_ptr2, *int_ptr2);
		int_ptr2 += 1;
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %d\n", char_ptr2, *char_ptr2);
		char_ptr2 += 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof(int_array)/sizeof(int); i++)
	{
		fprintf(stdout, "num_pointer is %p, num is %c\n", int_ptr3, *int_ptr3);
		int_ptr3 = (int *)((char *)int_ptr3 + 1);
	}
	
	for (size_t i = 0; i < sizeof(char_array)/sizeof(char); i++)
	{
		fprintf(stdout, "str_pointer is %p, str is %d\n", char_ptr3, *char_ptr3);
		char_ptr3 = (char *)((int *)char_ptr3 + 1);
	}
	return 0;
}
