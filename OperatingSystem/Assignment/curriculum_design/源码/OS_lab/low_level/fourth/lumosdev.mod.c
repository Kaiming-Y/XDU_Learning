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
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x105dd2a8, "module_put" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6bce40fa, "try_module_get" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xa916b694, "strnlen" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xc1352057, "__register_chrdev" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "948D2CF26B6B2987B814D83");
