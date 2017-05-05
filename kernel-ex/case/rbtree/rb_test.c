#include <linux/init.h>
#include <linux/module.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wang Shuxiao");


struct myroot {
	struct rb_root rbroot;
};

static struct myroot groot;

struct mynode {
	char *data;
	int key;
	struct rb_node rbnode;
};

static inline struct mynode * rb_search_mynode(struct myroot *root, int key)
{
	struct rb_node *n = root->rbroot.rb_node;

	struct mynode *p;

	while (n) {
		p = rb_entry(n, struct mynode, rbnode);

		if (key < p->key)
			n = n->rb_left;
		else if (key > p->key)
			n = n ->rb_right;
		else
			return p;
	}
	return NULL;
}

static inline struct mynode * __rb_insert_mynode(struct myroot *root, int key, struct rb_node * node)
{
	struct rb_node **p = &root->rbroot.rb_node;
	struct rb_node * parent = NULL;
	struct mynode *tmp_node;

	while (*p) {
		parent = *p;
		tmp_node = rb_entry(parent, struct mynode, rbnode);

		if (key < tmp_node->key)
			p = &(*p)->rb_left;
		else if (key > tmp_node->key)
			p = &(*p)->rb_right;
		else
			return tmp_node;
	}

	rb_link_node(node, parent, p);
}

static inline struct mynode * rb_insert_mynode(struct myroot *root, int key, struct rb_node * node)
{
	struct mynode * ret;
	if ((ret = __rb_insert_mynode(root, key, node)))
		goto out;
	rb_insert_color(node, &root->rbroot);

out:
	return ret;
}

static int hello_init(void)
{
	RB_EMPTY_ROOT(&groot.rbroot);
	struct mynode * n = kmalloc(sizeof(struct mynode), GFP_KERNEL);
	n->key = 3;
	n-> data = "hello, my dear\n";
	rb_insert_mynode(&groot, n->key, &(n->rbnode));

	return 0;
}

static void hello_exit(void)
{
	struct mynode * n = rb_search_mynode(&groot, 3);

	printk(KERN_INFO "%s", n->data);

	kfree(n);
}

module_init(hello_init);
module_exit(hello_exit);
