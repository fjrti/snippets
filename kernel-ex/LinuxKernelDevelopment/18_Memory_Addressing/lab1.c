/* gather memory statistics */

#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>

static int __init my_init(void)
{
	int i;
	unsigned long CountFree = 0, CountLocked = 0, CountDirty = 0, CountUp2Date = 0;
	struct page *cp;

	for (i=0; i <= get_num_physpages(); i++)
	{
		if (pfn_valid(i)) 
		{
			cp = pfn_to_page(i);
			if (!page_count(cp))
			{
				CountFree++;
			}
			else
			{
				CountLocked += PageLocked(cp);
				CountDirty  += PageDirty(cp);
				CountUp2Date+= PageUptodate(cp);
			}
		}
	}

	pr_info("\n       Pages Free = %lu", CountFree);
	pr_info("\n     Pages Locked = %lu", CountLocked);
	pr_info("\n     Pages Dirty  = %lu", CountDirty);
	pr_info("\n Pages Up to date = %lu \n", CountUp2Date);
					
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("\n Module Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_DESCRIPTION("LFD420:4.6 s_18/lab1.c");
MODULE_LICENSE("GPL v2");
