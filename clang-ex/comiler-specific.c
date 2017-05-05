#include <stdio.h>

void foo(int m, int n)
{
	printf("m=%d, n=%d\n", m, n);
}

int main()
{
	int b = 3;

	/* warning: operation on ‘b’ may be undefined */
	foo(b += 3, ++b);
	printf("b=%d\n", b);

	return 0;
}
