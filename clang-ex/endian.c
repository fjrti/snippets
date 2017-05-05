#include <stdio.h>

/* NOTE the order of union member matters */
union {
	char	c[4];
	int	a;
} u = {{'l', '?', '?', 'b'}};

void check_endian()
{
	printf("%c\n", (char)u.a);
}

union {
	int	a;
	char	c;
} u1;

void check_endian1(void)
{
	u1.a = 1;
	printf("%d\n", u1.c);
}

int main()
{
	check_endian();
	check_endian1();
	return 0;
}
