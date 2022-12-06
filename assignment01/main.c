// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

MODULE_AUTHOR("Arthur Laine");

MODULE_DESCRIPTION("Simple Hello World KM");

int	init_module(void)
{
	printk(KERN_INFO "Hello world !\n");
	return 0;
}

void	cleanup_module(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
}
