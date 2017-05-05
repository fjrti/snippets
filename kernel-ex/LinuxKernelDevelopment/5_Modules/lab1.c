/* for each task print the PID, state, etc. */

#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init my_init(void)
{
	struct task_struct *p;
	for_each_process(p)
	{
		pr_info("\n --------------------------");
		pr_info("\n Process ID   = %d ", p->pid);
		pr_info("\n TGID         = %d ", p->tgid);
		pr_info("\n State        = %d ",(int) p->state);
		pr_info("\n CPUs allowed = %d \n", p->nr_cpus_allowed);
	}
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_DESCRIPTION("LFD420:4.6 s_05/lab1.c");
MODULE_LICENSE("GPL v2");
