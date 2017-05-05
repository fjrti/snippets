/* print system information like uname -a */

#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>

static int __init my_init(void)
{
	struct new_utsname *u = init_utsname();
	pr_info("\n ------------------- ");
	pr_info("\n  sysname  = %s", u->sysname);
	pr_info("\n  nodename = %s", u->nodename);
	pr_info("\n  release  = %s", u->release);
	pr_info("\n  version  = %s", u->version);
	pr_info("\n  machine  = %s", u->machine);
	pr_info("\n  domain   = %s \n", u->domainname);

	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_DESCRIPTION("LFD420:4.6 s_05/lab2.c");
MODULE_LICENSE("GPL v2");
