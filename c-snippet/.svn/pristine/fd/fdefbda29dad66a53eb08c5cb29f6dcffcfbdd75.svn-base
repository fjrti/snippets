#define _GNU_SOURCE
#include <stdio.h>

#define SYSFS	"/sys"

int main()
{
	int l;
	char *root;

	l = asprintf(&root, SYSFS "%s/", "/class/firmware/mmc0:0006:1");
	printf("asprintf return value: %d\n", l);

	return 0;
}
