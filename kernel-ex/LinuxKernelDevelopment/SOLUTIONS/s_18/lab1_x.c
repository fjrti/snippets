/* **************** LFD420:4.6 s_05/lab1_ps.c **************** */
/*
 *  * The code herein is: Copyright the Linux Foundation, 2016
 *   *
 *    * This Copyright is retained for the purpose of protecting free
 *     * redistribution of source.
 *      *
 *       *     URL:    http://training.linuxfoundation.org
 *        *     email:  trainingquestions@linuxfoundation.org
 *         *
 *          * This code is distributed under Version 2 of the GNU General Public
 *           * License, which you should have received with the source.
 *            *
 *             */
/*
 *  * Iterating over processes
 *   *
 *    * Write a module that uses the for_each_process() macro to generate
 *     * some of the information obtained from the ps command.
 *      *
 *       * For each task, printout the process ID, state, command line and any
 *        * other interesting information.
 *         *
 *          * You can get the definition of the fields in the task_struct from
 *           * linux/sched.h.
 *            *
 *             * Don't forget to take out appropriate locks.
 *              *
 *              @*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/page-flags.h>
#include <linux/mm_types.h>

static int __init my_init(void)
{
	//struct page *pp;
	unsigned long pcnt = 0;

	pr_info("\n Memory Statistics Module: \n");
	
	for (pcnt = 0; pcnt < get_num_physpages(); pcnt++)
	{
		pr_info(" [%l]", pcnt);
	}



	return 0;
}

static void __exit my_exit(void)
{
		pr_info("Module Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Mihai Dragan");
MODULE_DESCRIPTION("LFD420:4.6 s_18/lab1.c");
MODULE_LICENSE("GPL v2");
