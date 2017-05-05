/* **************** LFD420:4.6 s_09/lab3_stealsyscalls.c **************** */
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
/*  Lab: Stealing System Calls. (Kernel Module)
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

#include <linux/module.h>
#include <linux/init.h>
#include <asm/unistd.h>
#include <linux/sched.h>
#include <linux/kallsyms.h>

static void **sys_call_table;

static asmlinkage long (*old_sys_getpmsg) (void);
static asmlinkage long (*old_sys_putpmsg) (void);

static asmlinkage long my_sys_getpmsg(void)
{
	pr_info(" Entering my_sys_getpmsg, current->tgid=%d\n", current->tgid);
	return old_sys_getpmsg();
}

static asmlinkage long my_sys_putpmsg(void)
{
	pr_info(" Entering my_sys_putpmsg, current->tgid=%d\n", current->tgid);
	return old_sys_putpmsg();
}

static int __init my_init(void)
{
	pr_info("Loading module\n");
	sys_call_table = (void **)kallsyms_lookup_name("sys_call_table");
	pr_info("sys_call_table=%p\n", sys_call_table);
	old_sys_getpmsg = sys_call_table[__NR_getpmsg];
	old_sys_putpmsg = sys_call_table[__NR_putpmsg];
	pr_info("old: sys_getpmsg=%p, sys_putpmsg=%p\n", old_sys_getpmsg,
		old_sys_putpmsg);
	sys_call_table[__NR_getpmsg] = my_sys_getpmsg;
	sys_call_table[__NR_putpmsg] = my_sys_putpmsg;
	pr_info("new: sys_getpmsg=%p, sys_putpmsg=%p\n", my_sys_getpmsg,
		my_sys_putpmsg);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Unloading module\n");
	sys_call_table[__NR_getpmsg] = old_sys_getpmsg;
	sys_call_table[__NR_putpmsg] = old_sys_putpmsg;
	pr_info("Restored the original system call");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_DESCRIPTION("LFD420:4.6 s_09/lab3_stealsyscalls.c");
MODULE_LICENSE("GPL");
