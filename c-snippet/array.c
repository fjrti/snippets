#include <stdio.h>

int array(int a[2])
{
	a[0] = 1;
	a[1] = 2;

	return 0;
}

int main()
{
	int i[2];

	array(i);
	printf("%d %d\n", i[0], i[1]);

	return 0;
}
