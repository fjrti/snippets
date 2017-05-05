#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*********************** test 0 *************************/
void getmem0(char **str)
{
	*str = "hello world!";
}

void test0(void)
{
#if 0
	char str[60];
#else
	char **str;
	str = (char **)malloc(60);
#endif
	memset(str, '\0', sizeof(str));
	getmem0(str);

	printf("%s: %s\n", __func__, *str);
}

/*********************** test 1 *************************/
void *getmem1(void)
{
	/* static */char p[] = "hello world!";

	printf("p: %p\n", p);

	return p;
}

void test1(void)
{
	char *str = NULL;

	str = getmem1();

	printf("%s: string is: %s, ptr is: %p\n", __func__, str, str);
}

/*********************** test 2 *************************/
void getmem2(char *p)
{
	/* NOTE:
	 * please always remember to check if we got a valid pointer
	 */
	p = (char *) malloc(100);
}

void test2(void)
{
	char *str = NULL;

	getmem2(str);
	strcpy(str, "hello world");
	printf("%s: %s\n", __func__, str);
}

/*********************** test 3 *************************/
void getmem3(char **p, int size)
{
	/* NOTE:
	 * please always remember to check if we got a valid pointer
	 */
	*p = (char *) malloc(size);
}

void test3(void)
{
	char *str = NULL;

	getmem3(&str, 100);
	strcpy(str, "hello world");
	printf("%s: %s\n", __func__, str);
	/* NOTE: free str, etc */
}

/*********************** test 3 *************************/
void test4(void)
{
	char *str = (char *) malloc(100);
	strcpy(str, "hello world");
	printf("%s: %s\n", __func__, str);
	free(str);
	/* str = NULL; */	/* dangling pointer */
}

int main()
{
	test0();
	test1();
	//test2();
	test3();
	test4();

	return 0;
}
