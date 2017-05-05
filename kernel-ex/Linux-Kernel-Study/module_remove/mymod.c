#include <linux/init.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/list.h>  
#include <linux/cpumask.h>  
#include <linux/types.h>
      
static int __init mymod_init(void)  
{  
    struct module *mod,*relate;  
    int cpu, i;
    int zero = 0;
  
    // print this mod's name 
    printk(KERN_ALERT"[insmod mymod] name:%s state:%d\n",THIS_MODULE->name,THIS_MODULE->state);  
  
    // iterator all mods, and find the target by name
    list_for_each_entry(mod,THIS_MODULE->list.prev,list)  
    {  
        // "testlist" can be changed to other name
        if(strcmp(mod->name,"testlist")==0) {   
            // print target module's name, state, refcnt 
            printk(KERN_ALERT"name:%s state:%d refcnt:%u ",mod->name,mod->state,module_refcount(mod));  
            // relate = mod;
      
            // print all dependent modules 
            if(!list_empty(&mod->source_list)) {   
                list_for_each_entry(relate,&mod->source_list,source_list)  
                    printk(KERN_ALERT"%s ",relate->name);  
            } else  
                printk(KERN_ALERT"used by NULL\n");  
            
            // change its state
            mod->state = MODULE_STATE_LIVE;
            // set refcnt := 0  
            for_each_possible_cpu(cpu){
                per_cpu_ptr(mod->refptr, cpu)->decs = 0;
                per_cpu_ptr(mod->refptr, cpu)->incs = 0;
            } 
      
            // reprint target module's name, state, refcnt  
            printk(KERN_ALERT"name:%s state:%d refcnt:%u\n",mod->name,mod->state,module_refcount(mod));  
        }  
    } 
    return 0;  
}  
      
static void __exit mymod_exit(void)  
{  
    printk(KERN_ALERT"[rmmod mymod] name:%s state:%d\n",THIS_MODULE->name,THIS_MODULE->state);  
}  
      
module_init(mymod_init);  
module_exit(mymod_exit);  
      
MODULE_AUTHOR("Xiarui");  
MODULE_LICENSE("GPL");  
MODULE_DESCRIPTION("Force removing a zombie module for mistaking init. Under Linux 3.18.44");  