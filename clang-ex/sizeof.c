#include <stdio.h>

/*
 * for more about attribute please visit:
 * http://gcc.gnu.org/onlinedocs/gcc-3.4.0/gcc/Type-Attributes.html
 */

void f(char p[100])
{
	printf("sizeof(p) = %d\n", sizeof(p));
	printf("\n");
}

void test_sizeof_char(void)
{
	char *pmsg = "A";
	char msg[] = "A";
	char ch    = 'A'; 

	printf("sizeof(pmsg) = %d\n", sizeof(pmsg));
	printf("sizeof(msg) = %d\n", sizeof(msg));
	printf("sizeof(\"A\") = %d\n", sizeof("A"));
	printf("sizeof(ch) = %d\n", sizeof(ch));
	printf("sizeof('A') = %d\n", sizeof('A'));
	printf("\n");
}

struct test1 {
	int	i;
	char	c;
	short	s;
};

struct test2 {
	char	c;
	short	s;
	int	i;
};

struct test3 {
	short	s;
	int	i;
	char	c;
};

struct test4 {
	short	s;
	int	i;
	char	c;
} __attribute__((packed));

struct test5 {
	char	c;
	short	s;
	int	i;
} __attribute__((packed));

void test_sizeof_struct(void)
{
	struct test1 t1;
	struct test2 t2;
	struct test3 t3;
	struct test4 t4;
	struct test4 t5;

	printf("\n");
	printf("mem locations:\n");
	printf("sizeof struct test1 = %d\n", sizeof(t1));
	printf("t.i: %p\n", &t1.i);
	printf("t.c: %p\n", &t1.c);
	printf("t.s: %p\n", &t1.s);
	printf("\n");

	printf("sizeof struct test2 = %d\n", sizeof(t2));
	printf("t.c: %p\n", &t2.c);
	printf("t.s: %p\n", &t2.s);
	printf("t.i: %p\n", &t2.i);
	printf("\n");

	printf("sizeof struct test3 = %d\n", sizeof(t3));
	printf("t.s: %p\n", &t3.s);
	printf("t.i: %p\n", &t3.i);
	printf("t.c: %p\n", &t3.c);
	printf("\n");

	printf("sizeof struct test4 = %d\n", sizeof(t4));
	printf("t.s: %p\n", &t4.s);
	printf("t.i: %p\n", &t4.i);
	printf("t.c: %p\n", &t4.c);
	printf("\n");

	printf("sizeof struct test5 = %d\n", sizeof(t5));
	printf("t.c: %p\n", &t5.c);
	printf("t.s: %p\n", &t5.s);
	printf("t.i: %p\n", &t5.i);
	printf("\n");
}

int main()
{
	char a[100];

	test_sizeof_char();

	f(a);

	test_sizeof_struct();

	printf("short: %d\n", sizeof(short));
	printf("int: %d\n", sizeof(int));
	printf("long: %d\n", sizeof(long));
	printf("long long: %d\n", sizeof(long long));

	return 0;
}
