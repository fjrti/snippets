#include <stdio.h>

int main()
{
	char *a = "hello";
	char *b = "hello";

	if (a == b)
		printf("compiled with gcc optimization\n");
	else
		printf("compiled without gcc optimization\n");

	return 0;
}
