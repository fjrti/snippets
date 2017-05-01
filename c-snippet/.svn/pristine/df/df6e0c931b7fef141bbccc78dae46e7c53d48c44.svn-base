#include <stdio.h>
#include <string.h>

int main()
{
	char *pmsg = "hello, world!";

	/* result in Segmentation fault
	 * The address of string constant is allocated at build time
	 * and pmsg is a pointer to that address, so its content cannot
	 * be changed
	 */
	strcpy(pmsg, "hi, there."); 
	printf("%s\n", pmsg);

	return 0;
}
