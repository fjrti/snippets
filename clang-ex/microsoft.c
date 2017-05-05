#include <stdio.h>

struct test {
	int i;
	int *p;
};

int main()
{
	struct test t;
	int *p = &t.i;

	p[0] = 4;
	p[1] = 3;

	t.p = p;
	t.p[1] = 1;
	t.p[0] = 2;	/* Segmentation fault, invalid address access */

	return 0;
}
