#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xfe0edd20, "pv_ops" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x92997ed8, "_printk" },
	{ 0x72d79d83, "pgdir_shift" },
	{ 0xc5bbbf60, "current_task" },
	{ 0xa648e561, "__ubsan_handle_shift_out_of_bounds" },
	{ 0xd7b002d, "boot_cpu_data" },
	{ 0xdad13544, "ptrs_per_p4d" },
	{ 0x1d19f77b, "physical_mask" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4956D6675A68A8E7C5A6597");
