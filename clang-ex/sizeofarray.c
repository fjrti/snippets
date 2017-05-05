#include <stdio.h>

#define	ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))
/* #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr)) */

int main()
{
	int a[] = {1, 2, 3, 4, 5, 6};

	printf("size of array is: %d\n", ARRAY_SIZE(a));

	return 0;
}
