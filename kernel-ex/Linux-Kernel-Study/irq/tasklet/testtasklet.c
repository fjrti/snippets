#include <linux/interrupt.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

static void my_tasklet_func(unsigned long);

DECLARE_TASKLET(mytasklet, my_tasklet_func, 1000);

static int testtasklet_init(void){
	printk(KERN_ALERT"interrupt top half\n");

	print_current_time(0);
	tasklet_schedule(&mytasklet);

	return 0;
}

static void testtasklet_exit(void){
	printk(KERN_ALERT"************\n");
	print_current_time(0);
	printk(KERN_ALERT"testtasklet is exited!\n");
	printk(KERN_ALERT"************\n");
}

static void my_tasklet_func(unsigned long data){
	printk(KERN_ALERT"==============\n");
	print_current_time(0);
	printk(KERN_ALERT"my tasklet function is called!...\n");
	printk(KERN_ALERT"parameter data is %ld\n", data);
	printk(KERN_ALERT"==============\n");
}

module_init(testtasklet_init);
module_exit(testtasklet_exit);