//#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");
static int __init printk_init(void){
	printk(KERN_INFO"Hello world. Xiarui...\n");
	return 0;
}

static void __exit printk_exit(void){
	printk(KERN_INFO"Bye. Xia\n");
}
module_init(printk_init);
module_exit(printk_exit);

// #include "linux/module.h"

// #include "linux/init.h"


// MODULE_LICENSE("Dual BSD/GPL");
// static int __init hello_init(void)
// {
//     printk(KERN_ALERT "Hello, world\n");
//     return 0;
// }
// static void __exit hello_exit(void)
// {
//     printk(KERN_ALERT "Goodbye, cruel world\n");
// }
// module_init(hello_init);
// module_exit(hello_exit);