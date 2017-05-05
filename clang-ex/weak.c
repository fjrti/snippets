#include <stdio.h>

extern void foo() __attribute__((weak));
extern void foo();

int main()
{
	if (foo)
		foo();

	return 0;
}
