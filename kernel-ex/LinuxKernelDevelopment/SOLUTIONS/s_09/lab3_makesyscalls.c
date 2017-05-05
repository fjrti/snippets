/* **************** LFD420:4.6 s_09/lab3_makesyscalls.c **************** */
/*
 * The code herein is: Copyright the Linux Foundation, 2016
 *
 * This Copyright is retained for the purpose of protecting free
 * redistribution of source.
 *
 *     URL:    http://training.linuxfoundation.org
 *     email:  trainingquestions@linuxfoundation.org
 *
 * This code is distributed under Version 2 of the GNU General Public
 * License, which you should have received with the source.
 *
 */
/*  Lab: Stealing System Calls. (User Application)
 *
 * Write a module that steals the positions in the sys_call_table of
 * the getpmsg() and putpmsg() non-implemented system calls.  Make sure
 * the old functions are restored upon module removal.
 *
 * Your module must contain new functions to be executed whenever a
 * user exercises these system calls.  They may call the old system
 * calls when they are done.
 *
 * You'll also need to write a brief application program to make the
 * system calls.
 *
 * You can hard code the address of the <TB>sys_call_table</TB> or you
 * can use the script we presented to do the substitutions.
@*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

/*_syscall0 (long, getpmsg) _syscall0 (long, putpmsg)*/

int main()
{
	int j;
	for (j = 0; j < 5; j++) {
		/*
		   printf (" called getpmsg() = %ld  ", getpmsg ());
		   printf (" called putpmsg() = %ld\n", putpmsg ());
		 */
		printf(" called getpmsg() = %ld  ", syscall(__NR_getpmsg));
		printf(" called putpmsg() = %ld\n", syscall(__NR_putpmsg));
	}
	exit(EXIT_SUCCESS);
}
