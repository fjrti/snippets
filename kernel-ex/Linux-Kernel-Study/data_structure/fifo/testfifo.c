#include "kn_common.h"

struct student
{
	int id;
	char* name;
};

static void print_student(struct student *);

static int __init testfifo_init(void){
	struct kfifo fifo;
	struct student *stu1, *stu2, *stu3, *stu4;
	struct student *stu_tmp;
	char *c_tmp;
	int i, ret;

	 // !!importent  init a unlocked lock
	// spinlock_t	 sl = SPIN_LOCK_UNLOCKED;

	// fifo = kfifo_alloc(4 * sizeof(struct student), GFP_KERNEL, &sl); // ?

	ret = kfifo_alloc(&fifo, 4 * sizeof(struct student), GFP_KERNEL);
	if(ret){
		printk(KERN_ALERT "kfifo_alloc error \n");
		return ret;
	}

	stu1 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu1->id = 1;
    stu1->name = "xr1";
    kfifo_in(&fifo, (char *)stu1, sizeof(struct student));
    // kfifo_put(fifo, stu1);

    stu2 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu2->id = 1;
    stu2->name = "xr2";
    kfifo_in(&fifo, (char *)stu2, sizeof(struct student));
    // kfifo_put(fifo, stu2);

    stu3 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu3->id = 1;
    stu3->name = "xr3";
    kfifo_in(&fifo, (char *)stu3, sizeof(struct student));
    // kfifo_put(fifo, stu3);

    stu4 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu4->id = 1;
    stu4->name = "xr4";
    kfifo_in(&fifo, (char *)stu4, sizeof(struct student));
    // kfifo_put(fifo, stu4);

    c_tmp = kmalloc(sizeof(struct student), GFP_KERNEL);

    printk(KERN_ALERT "current kfifo length is %d\n", kfifo_len(&fifo));

    for(i = 0; i < 4; i++){
    	kfifo_out(&fifo, c_tmp, sizeof(struct student));
    	stu_tmp = (struct student*)(c_tmp);
    	print_student(stu_tmp);
    	printk(KERN_ALERT "current kfifo length is %d\n", kfifo_len(&fifo));
    }

    printk(KERN_ALERT "current kfifo length is %d\n", kfifo_len(&fifo));
    kfifo_free(&fifo);
    kfree(c_tmp);
    return 0;

}

static void print_student(struct student *stu){
	printk(KERN_ALERT "===================\n");
	print_current_time(1);
	printk(KERN_ALERT "student id: %d\n", stu->id);
	printk(KERN_ALERT "student name: %s\n", stu->name);
	printk(KERN_ALERT "===================\n");
}

static void __exit testfifo_exit(void){
	printk(KERN_ALERT "===================\n");
	printk(KERN_ALERT "testfifo is finished!\n");
	printk(KERN_ALERT "===================\n");
}

module_init(testfifo_init);
module_exit(testfifo_exit);