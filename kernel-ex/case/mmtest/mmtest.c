#include <linux/init.h>
#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mm.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wang Shuxiao");

static unsigned long  vaddr;

static int hello_init(void)
{
	struct page *page;

	printk(KERN_INFO "hello, linux kernel\n");

	/* allocate a free page in physical memory */
	page = alloc_pages(GFP_KERNEL, 0);

	/* map the page to virtual memory */
	vaddr = page_address(page);

	printk(KERN_INFO "virtual memory:%p", vaddr);
	return 0;
}

static void hello_exit(void)
{
	free_pages(vaddr, 0);
	printk(KERN_INFO "Goodbye, linux kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);
