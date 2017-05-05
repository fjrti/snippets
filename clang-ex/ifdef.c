/*
 * NOTE:
 * gcc will raise a warning like this
 * ifdef.c:18:10: warning: extra tokens at end of #ifdef directive
 *
 * The result is not we want, so this should be changed
 * to the following:
 * #if defined(A) || defined(B)
 */

#include <stdio.h>

#define	B

int main()
{
	/* this is completely wrong */
#ifdef A || B
	printf("^^^^^^^^^^A || B^^^^^^^^^^\n");
#else
	printf("^^^^^^^^^^oops^^^^^^^^^^\n");
#endif

	/* right one */
#if defined(A) || defined(B)
	printf("^^^^^^^^^^A || B^^^^^^^^^^\n");
#else
	printf("^^^^^^^^^^oops^^^^^^^^^^\n");
#endif


	return 0;
}
