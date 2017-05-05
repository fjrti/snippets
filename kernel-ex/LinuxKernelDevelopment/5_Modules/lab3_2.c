/* export and load symbols from one module to another */

#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>

extern int yagv;
extern int yagf (int x);

static int __init my_init(void)
{
	pr_info("\n - Caller module - \n");
	pr_info(" Returned value = %d \n", yagf(yagv));
	pr_info(" - this was it. \n");
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module 2 Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_DESCRIPTION("LFD420:4.6 s_05/lab2.c");
MODULE_LICENSE("GPL v2");
