# RBTree Lab
**Attention: The version of the kernel is 3.18.44**
* 1. Define a structure with a element of `struct rb_node`
```
	struct student
	{
		int id;
		char* name;
		struct rb_node node;
	};
```

* 2. Init the structures

* 3. Init the root of the rbtree `struct rb_root` use macro `RB_ROOT`
```
	struct rb_root root = RB_ROOT;
```

* 4. Insert the structure to the rbtree(root)
```
	for(i = 0; i < N; i++){
		insert_student(stu[i], &root);
	}
```

* 5. Remove the specific structrue from the rbtree(root)
```
	remove_student(stu[8], &root);
```

* 6. Insert function `insert_student()`. Use two pointer `struct rb_node **new` & `struct rb_node *parent`
```
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
```

* 7. Remove function `remove_student()`. Simply use the API `rb_erase()`
```
	rb_erase(&(stu->node), root);
```

* 8. Iterator all the elements in the rbtree
```
	// Previous Order
	if(node){
		display_student_from_small(node->rb_left);
		tmp_stu = rb_entry(node, struct student, node);
		print_student(tmp_stu);
		display_student_from_small(node->rb_right);
	}
```