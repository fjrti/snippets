#include <stdio.h>

struct test {
	int a:2;
	int b:2;
	int c:1;
};

int main()
{
	struct test t;

	t.a = 1;
	t.b = 3;
	t.c = 1;

	printf("%d %d %d\n", t.a, t.b, t.c);

	return 0;
}
