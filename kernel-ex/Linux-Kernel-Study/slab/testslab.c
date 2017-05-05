#include "kn_common.h"
#include <linux/slab.h>
#include <linux/slab_def.h>

MODULE_LICENSE("Dual BSD/GPL");

#define MYSLAB "testslab"

static struct kmem_cache *myslab;

static void ctor(void* obj){
	printk(KERN_ALERT "constructor is called...\n");
}

struct student
{
	int id;
	char* name;
};

static void print_student(struct student*);

static int testslab_init(void){
	struct student *stu1, *stu2;

	// create kmem_cache
	myslab = kmem_cache_create(MYSLAB, sizeof(struct student), 0, 0, ctor);

	// allocate two objects

	printk(KERN_ALERT "allocate one students\n");
	stu1 = (struct student*)kmem_cache_alloc(myslab, GFP_KERNEL);
	stu1->id = 1;
	stu1->name = "Xia Rui";
	print_student(stu1);

	printk(KERN_ALERT "allocate two students\n");
	stu2 = (struct student*)kmem_cache_alloc(myslab, GFP_KERNEL);
	stu2->id = 2;
	stu2->name = "Zhang tl";
	print_student(stu2);


	// free kmem_cache
	printk(KERN_ALERT "free first student\n");
	kmem_cache_free(myslab, stu1);

	printk(KERN_ALERT "free second student\n");
	kmem_cache_free(myslab, stu2);

	return 0;
}

static void testslab_exit(void){
	printk(KERN_ALERT "*******************\n");
	print_current_time(0);
	kmem_cache_destroy(myslab);
	printk(KERN_ALERT "testslab exit!\n");
	printk(KERN_ALERT "*******************\n");
}

void print_student(struct student *stu){
	if(stu != NULL){
		printk(KERN_ALERT "********* stu info *********\n");
		printk(KERN_ALERT "student id : %d\n", stu->id);
		printk(KERN_ALERT "student name: %s\n", stu->name);
		printk(KERN_ALERT "****************************\n");
	}
}


module_init(testslab_init);
module_exit(testslab_exit);