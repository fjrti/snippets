#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/delay.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

static void test_delay(void);
static void test_short_delay(void);
static void test_schedule_timeout(void);
static void my_delay_function(unsigned long);

static int testdelay_init(void){
	printk(KERN_ALERT "HZ in current system: %dHz\n", HZ);
	
	// test short delay mdelay()
	test_short_delay();

	// test timer()
	test_delay();

	// test schedule_timeout();
	test_schedule_timeout();

	return 0;
}

static void testdelay_exit(void){
	printk(KERN_ALERT"*************\n");
	print_current_time(0);
	printk(KERN_ALERT"testdelay is exited\n");
	printk(KERN_ALERT"*************\n");
}

static void test_short_delay(void){
	printk(KERN_ALERT"jiffies [b e f o r e] short delay: %lu\n", jiffies);
	ndelay(5);
	printk(KERN_ALERT"jiffies [a f t e r] short delay: %lu\n", jiffies);
}

static void test_delay(void){
	// init
	struct timer_list my_timer;
	init_timer(&my_timer);

	// complete
	my_timer.expires = jiffies + 1 * HZ;
	my_timer.data = jiffies;
	my_timer.function = my_delay_function;

	// active
	add_timer(&my_timer);
}

static void test_schedule_timeout(void){
	printk(KERN_ALERT"This sample start at : %lu\n", jiffies);

	// sleep 2 sec
	set_current_state(TASK_INTERRUPTIBLE);
	printk(KERN_ALERT"sleep 2 sec...\n");
	schedule_timeout(2 * HZ);

	printk(KERN_ALERT "This sample end at : %lu \n", jiffies);
}

static void my_delay_function(unsigned long data){
	printk(KERN_ALERT "This is my delay function start.....\n");
	printk(KERN_ALERT "The jiffies when init the timer : %lu\n", data);
	printk(KERN_ALERT "The jiffies when the timer is running : %lu\n", jiffies);
	printk(KERN_ALERT "This is my delay function end.....\n");
}

module_init(testdelay_init);
module_exit(testdelay_exit);