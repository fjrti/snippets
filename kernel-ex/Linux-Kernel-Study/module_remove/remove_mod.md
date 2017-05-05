## Force Remove a module from kernel

* 1 **modules are gathered as a list, use `list_for_each_entry` to iterator all modules**

* 2 **module name is your target**

* 3 **remove it by two step:**

	 i. set its state to `MODULE_STATE_LIVE`

	ii. clear all reference, set `mod->refptr->desc`&`mod->refptr->incs` to 0

[code](https://github.com/jiexray/Linux-Kernel-Study/blob/master/module_remove/mymod.c)
