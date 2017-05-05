#include <stdio.h>

int main()
{
	int a[] = {1, 2, 3, 4, 5, 6};
	typeof (a) i;		/* same as int j[6] */
	typeof (a[0]) j;	/* same as int j */

	i[0] = a[0];
	i[1] = 7;

	j = 2;

	printf("i[0]: %d\n", i[0]);
	printf("i[1]: %d\n", i[1]);
	printf("j: %d\n", j);

	printf("sizeof(i): %d\n", sizeof(i));
	printf("sizeof(j): %d\n", sizeof(j));

	return 0;
}
