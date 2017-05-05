/* export and load symbols from one module to another */

#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>

int yagv = 7;
int yagf (int x)
{
	pr_info("\n Exported variable = %d", x);
	pr_info("\n Exported function says hi !\n");

	return x+1;
}	

static int __init my_init(void)
{
	pr_info("\n ------------------- ");
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module 1 Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

EXPORT_SYMBOL(yagv);
EXPORT_SYMBOL(yagf);

MODULE_AUTHOR("A GENIUS");
MODULE_DESCRIPTION("LFD420:4.6 s_05/lab2.c");
MODULE_LICENSE("GPL v2");
