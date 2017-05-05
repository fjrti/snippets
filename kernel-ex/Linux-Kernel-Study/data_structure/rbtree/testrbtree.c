#include <linux/rbtree.h>
#include <linux/string.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

struct student
{
	int id;
	char* name;
	struct rb_node node;
};

static void insert_student(struct student*, struct rb_root*);
static void remove_student(struct student*, struct rb_root*);
static int display_student(struct rb_root*, int);
static void display_student_from_small(struct rb_node*);
static void display_student_from_big(struct rb_node*);
static void print_student(struct student*);

static int testrbtree_init(void){
#define N 10
	struct rb_root root = RB_ROOT;
	struct student *stu[N];
	char tmp_name[5] = "XRAY";
	int i;

	for(i = 0; i < N; i++){
		stu[i] = kmalloc(sizeof(struct student), GFP_KERNEL);
		stu[i]->id = i;
		stu[i]->name = kmalloc(sizeof(char)*6, GFP_KERNEL);
		tmp_name[3] = (char)(i + '0');
		strcpy(stu[i]->name, tmp_name);
		stu[i]->node.rb_left = NULL;
		stu[i]->node.rb_right = NULL;
	}


	for(i = 0; i < N; i++){
		printk(KERN_ALERT"id=%d   name=%s\n", stu[i]->id, stu[i]->name);
	}

	// add N students to rb-tree
	for(i = 0; i < N; i++){
		insert_student(stu[i], &root);
	}

	// display all students
	printk(KERN_ALERT"print from small to big\n");
	display_student(&root, -1);
	printk(KERN_ALERT"print from big to small\n");
	display_student(&root, 1);

	//remove student 8
	remove_student(stu[8], &root);
	display_student(&root, -1);

	// free all student
	for(i = 0; i < N; i++){
		kfree(stu[i]->name);
		kfree(stu[i]);
	}

	return 0;
}

static void testrbtree_exit(void){
	printk(KERN_ALERT"******************\n");
	print_current_time(0);
	printk(KERN_ALERT"testrbtree is exited\n");
	printk(KERN_ALERT"******************\n");
}

void print_student(struct student *stu){
	printk(KERN_ALERT"=====================\n");
	print_current_time(0);
	printk(KERN_ALERT"id=%d\tname=%s\n", stu->id, stu->name);
	printk(KERN_ALERT"=====================\n");
}

static void insert_student(struct student* stu, struct rb_root* root){
	struct rb_node *parent = NULL, **new = &root->rb_node;

	int id = stu->id;

	while(*new){
		parent = *new;
		if(id < rb_entry(parent, struct student, node)->id){
			new = &parent->rb_left;
		}else if(id > rb_entry(parent, struct student, node)->id){
			new = &parent->rb_right;
		}else{
			printk(KERN_ALERT"id=%d has in the rbtree now\n", id);
			return;
		}
	}

	rb_link_node(&stu->node, parent, new);
	rb_insert_color(&stu->node, root);
}

static void remove_student(struct student* stu, struct rb_root* root){
	rb_erase(&(stu->node), root);
}

static int display_student(struct rb_root *root, int order){
	if(!root->rb_node){
		return 1;
	}

	if(order < 0){
		display_student_from_small(root->rb_node);
	}else{
		display_student_from_big(root->rb_node);
	}

	return 0;
}

static void display_student_from_small(struct rb_node *node){
	struct student *tmp_stu;

	if(node){
		display_student_from_small(node->rb_left);
		tmp_stu = rb_entry(node, struct student, node);
		print_student(tmp_stu);
		display_student_from_small(node->rb_right);
	}
}

static void display_student_from_big(struct rb_node *node){
	struct student *tmp_stu;

	if(node){
		display_student_from_big(node->rb_right);
		tmp_stu = rb_entry(node, struct student, node);
		print_student(tmp_stu);
		display_student_from_big(node->rb_left);
	}
}


module_init(testrbtree_init);
module_exit(testrbtree_exit);