#include <stdio.h>

int main()
{
	int a = 19, b = 88;

	printf("before swap: a = %d, b = %d\n", a, b);

	a = a + b;
	b = a - b;
	a = a - b;

	printf("after swap: a = %d, b = %d\n", a, b);

	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	printf("swap back: a = %d, b = %d\n", a, b);

	return 0;
}
