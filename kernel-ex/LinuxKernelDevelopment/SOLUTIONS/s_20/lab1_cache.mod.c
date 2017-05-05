#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x141d70f7, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x51eafc8e, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xe3d03d12, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0xbf529951, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x1d72abd2, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xadbf06c0, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "315946F826B15A58822A02F");
