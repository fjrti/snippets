#include <stdio.h>
#include <unistd.h>
#include <signal.h>

unsigned char forever = 1;

void cleanup(int sig)
{
	forever = 0;
	printf("exiting test program\n");
	(void) signal(SIGINT, SIG_DFL);
}

int main()
{

	(void)signal(SIGINT, &cleanup);		/* CTRL+C */
	(void)signal(SIGABRT, &cleanup);
	(void)signal(SIGTERM, &cleanup);

	while (forever)
		sleep(1), printf("sleeping ZZZzzzz\n");

	return 0;
}
