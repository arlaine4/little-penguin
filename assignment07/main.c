// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include "id_fops.c"
#include "foo_fops.c"

static struct dentry *debugfs_root;

static struct dentry *create_u64(char *name, umode_t mode,
	struct dentry *parent, u64 *value) 
{

	debugfs_create_u64(name, mode, parent, value);
	return parent;
}

static int __init init_km(void)
{
	int res = 0;

	printk(KERN_INFO "Hello World!\n");
	debugfs_root = debugfs_create_dir("fortytwo", NULL);
	if (!debugfs_root) {
		res = -ENOENT;
		goto end;
	}
	if (!debugfs_create_file("id", 0666, debugfs_root, NULL, &id_fops)
			|| !create_u64("jiffies", 0444, debugfs_root, (u64*) &jiffies)
			|| !debugfs_create_file("foo", 0644, debugfs_root, NULL, &foo_fops)) {
		res = -ENOENT;
		goto end;
	}
end:
	return res;
}

static void __exit cleanup_km(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
	debugfs_remove_recursive(debugfs_root);
}

module_init(init_km);
module_exit(cleanup_km);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur LAINE");
MODULE_DESCRIPTION("Just a simple Hello World! KM");
