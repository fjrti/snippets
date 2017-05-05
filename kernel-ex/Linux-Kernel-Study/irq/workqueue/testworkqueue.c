#include <linux/workqueue.h>
#include "kn_common.h"
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

static void my_work_func(struct work_struct *work){
	long ID;
	printk(KERN_ALERT"=============\n");
	print_current_time(0);
	ID = current->pid;
	printk(KERN_ALERT"my workqueue function is called!.... pid = %ld\n", ID);
	printk(KERN_ALERT"=============\n");
}

static void my_work_custom_func(struct work_struct *work){
	long ID;
	printk(KERN_ALERT"=============\n");
	print_current_time(0);
	ID = current->pid;
	printk(KERN_ALERT"my customize workqueue is called!... pid = %ld\n", ID);
	printk(KERN_ALERT"=============\n");
}

DECLARE_WORK(mywork, my_work_func);

static int testworkqueue_init(void){
	struct workqueue_struct *myworkqueue = create_workqueue("myworkqueue");

	// init a work_struct dynamically use pointer
	struct work_struct *mywork2;
	mywork2 = kmalloc(sizeof(struct work_struct), GFP_KERNEL);
	INIT_WORK(mywork2, my_work_custom_func);

	flush_scheduled_work();

	// schedule work
	schedule_work(&mywork);

	// flush customized workqueue
	flush_workqueue(myworkqueue);
	queue_work(myworkqueue, mywork2);

	return 0;
}

static void testworkqueue_exit(void){
	printk(KERN_ALERT"*************\n");
	print_current_time(0);
	printk(KERN_ALERT"testworkqueu exit\n");
	printk(KERN_ALERT"*************\n");
}

module_init(testworkqueue_init);
module_exit(testworkqueue_exit);