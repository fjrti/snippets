#include "kn_common.h"

void print_current_time(int is_new_line){
	struct timeval *tv;
	struct tm *t;

	tv = kmalloc(sizeof(struct timeval), GFP_KERNEL);
	t = kmalloc(sizeof(struct tm), GFP_KERNEL);

	do_gettimeofday(tv);
	time_to_tm(tv->tv_sec, 0, t);

	printk(KERN_ALERT "%ld-%d-%d %d:%d:%d",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		(t->tm_hour + 8) % 24,
		t->tm_min,
		t->tm_sec);

	if(is_new_line == 1){
		printk(KERN_ALERT "\n");
	}

	kfree(tv);
	kfree(t);

}