#include <stdio.h>

int main()
{
	char *p = "be";
	char a;

	sscanf(p, "%hhx", &a);
	printf("%hhx\n", a);

	return 0;
}

