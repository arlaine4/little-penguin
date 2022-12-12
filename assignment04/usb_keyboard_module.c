// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>

static int __init usb_init_module(void)
{
	pr_info("usb_keyboard_module: USB Keyboard plugged.\n");
	return 0;
}

static void __exit usb_cleanup_module(void)
{
	pr_info("usb_keyboard_module: USB Keyboard disconnected.\n");
}

module_init(usb_init_module);
module_exit(usb_cleanup_module);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur LAINE");
MODULE_DESCRIPTION("Simple hello world KM");
