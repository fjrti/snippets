#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main()
{
	char *p;
	p = (char *)malloc(0);
	if (p == NULL)
		printf("Got a null pointer\n");
	else
		printf("Got a valid pointer: %p\n", p);

	/* This is completely wrong, NEVER do this */
	strcpy(p, "hello world!");
	printf("%s\n", p);

	free(p);

	return 0;
}
