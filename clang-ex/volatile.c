#include <stdio.h>

static int foo;

void bar(void)
{
	foo = 0;
	while (foo != 255)
		;
}

int main()
{
	bar();
	return 0;
}
