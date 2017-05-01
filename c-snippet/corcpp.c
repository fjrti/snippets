#include <stdio.h>

int main()
{
#ifdef __cplusplus
	printf("cpp\n");
#elif defined(__STDC__)
	printf("c\n");
#endif
	return 0;
}
