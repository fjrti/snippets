#include <stdio.h>
#include <stdlib.h>

void foo(void)
{
	printf("main already gone.\n");
}

int main()
{
	atexit(foo);
	printf("look out\n");

	return 0;
}
