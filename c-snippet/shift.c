#include <stdio.h>

int main()
{
	printf("%d %d\n", 4<<1, 1<<4);
	printf("%#x\n", 1<<31 | 1);
	printf("%#x\n", (0x0e & 0x3f) << 1);

	return 0;
}
