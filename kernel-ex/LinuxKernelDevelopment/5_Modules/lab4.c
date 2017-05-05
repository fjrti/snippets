/* set up a doubly-linked circular list of data structs.
 * Test insertion and deletion */

#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>
#include <linux/list.h>
#include <linux/atomic.h>
#include <linux/slab.h>
#include <linux/errno.h>

LIST_HEAD (collection);

struct stuff 
{
	char id[4];
	unsigned char val;
	struct list_head list;
};

static int __init my_init(void)
{
	int i;
	struct stuff *mystuff;
	pr_info ("\n  --- START --- \n");

	for (i = 0; i < 8; i++)
	{
		mystuff = kmalloc(sizeof(struct stuff), GFP_KERNEL);
		if (!mystuff) return -ENOMEM;

		mystuff->val = i;
		sprintf(mystuff->id, "id%d", i);

		list_add(&mystuff->list, &collection);
	}

	return 0;
}

static void __exit my_exit(void)
{
	struct list_head *curelem;
	struct list_head *del;

	if (list_empty(&collection)) return;

	list_for_each_safe(curelem, del, &collection)
	{
		struct stuff *a = list_entry(curelem, struct stuff, list);
		pr_info("\n Element %d = %s \n", a->val, a->id);
		list_del(&a->list);
		kfree(a);
	}

	pr_info ("\n  --- FIN --- \n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_DESCRIPTION("LFD420:4.6 s_05/lab4.c");
MODULE_LICENSE("GPL v2");
