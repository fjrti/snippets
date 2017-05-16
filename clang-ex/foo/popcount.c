#include <stdio.h>

int main()
{
	int i = 0xaa55;

	printf("There are %d '1s' in integer: %x\n",
			__builtin_popcount(i), i);

	return 0;
}
