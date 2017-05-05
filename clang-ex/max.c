#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
	int a = -3 + 7;
	int b = 5;

	printf("%d\n", max(a, b));

	return 0;
}
