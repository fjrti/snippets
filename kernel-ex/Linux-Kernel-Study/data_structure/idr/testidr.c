#include <linux/idr.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

struct student
{
	int id;
	char* name;
};

static int print_student(int, void*, void*);

static int testidr_init(void){
	DEFINE_IDR(idp);
	struct student *stu[4];

	int ret, i;

	// init 4 struct student
    for(i = 0; i < 4; i++){
    	stu[i] = kmalloc(sizeof(struct student), GFP_KERNEL);
    	stu[i]->id = i;
    	stu[i]->name = "xr_nku";
    }

	for(i = 0; i < 4; i++){
		// do{

		// 	// reserve resources for idr allocation, this function will modify the idr-tree
		// 	// 0:fail; 1:success
		// 	// 2.6.x Cannot be used in 3.18.x
		// 	// if(!idr_pre_get(&idp, GFP_KERNEL)){
		// 	// 	return -ENOSPC;
		// 	// }

		// 	// get a new UID
		// 	// use pointer idp to allocate a new UID, it will be associated with a pointer(stu[i]), and the new UID will be stored in id
		// 	// ret = idr_get_new(&idp, stu[i], &id);

			
			
		// }while(ret != -ENOSPC && ret);

		idr_preload(GFP_KERNEL);


		ret = idr_alloc(&idp, stu[i], 1, -1, GFP_KERNEL);

		idr_preload_end();
		
		if(ret < 0){
			printk(KERN_ALERT"Error when allocate new UID\n");
			return -ENOSPC;
		}else{
			printk(KERN_ALERT"id=%d\n", ret);
		}


	}

	/*
		int idr_for_each(struct idr *idp,
		 	int (*fn)(int id, void *p, void *data), void *data);
	*/

	//display all students in idr
	idr_for_each(&idp, print_student, NULL);

	idr_destroy(&idp);

	kfree(stu[0]);
	kfree(stu[1]);
	kfree(stu[2]);
	kfree(stu[3]);

	return 0;
}

static int print_student(int id, void *p, void * data){
	struct student *stu = p;
	if(stu == NULL){
		printk(KERN_ALERT"pointer of student is NULL\n");
		return 0;
	}

	printk(KERN_ALERT"===============\n");
	print_current_time(0);
	printk(KERN_ALERT"idr id:%d\n",id);
	printk(KERN_ALERT"id=%d\n", stu->id);
	printk(KERN_ALERT"name=%s\n", stu->name == NULL ? "NULL": stu->name);
	printk(KERN_ALERT"===============\n");

	return 0;
}

static void testidr_exit(void){
	printk(KERN_ALERT"================\n");
	print_current_time(0);
	printk(KERN_ALERT"testidr exit\n");
	printk(KERN_ALERT"================\n");
}

module_init(testidr_init);
module_exit(testidr_exit);