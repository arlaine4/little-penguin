// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define BUF "arlaine"
#define BUF_LEN 7

static struct miscdevice device;

static ssize_t module_read(struct file *f, char *buffer, size_t length, loff_t *offset)
{
	int res;
	char *read_from = BUF + *offset;
	size_t read_num = length < (BUF_LEN - *offset) ? length : (BUF_LEN - *offset);

	if (read_num == 0) {
		res = 0;
		goto end;
	}

	res = copy_to_user(buffer, read_from, read_num);
	if (res == read_num) {
		res = -EIO;
	} else {
		*offset = BUF_LEN - res;
		res = read_num - res;
	}
end:
	return (res);
}

static ssize_t module_write(struct file *f, const char *buf, size_t len, loff_t *offset)
{
	char buffer[BUF_LEN];
	ssize_t res;
	int tmp;

	if (len != BUF_LEN) {
		res = -EINVAL;
		goto end;
	}
	tmp = copy_from_user(buffer, buf, BUF_LEN);
	(void)tmp;
	if (strncmp(buffer, BUF, BUF_LEN) == 0)
		res = BUF_LEN;
	else
		res = -EINVAL;
end:
	return (res);
}


static const struct file_operations fops = {
	.read = module_read,
	.write = module_write,
};

int init_module(void)
{
	int retval;

	printk(KERN_INFO "Hello World!\n");
	device.minor = MISC_DYNAMIC_MINOR;
	device.name = "fortytwo";
	device.fops = &fops;
	retval = misc_register(&device);
	if (retval)
		return retval;
	printk(KERN_INFO "fortytwo: got minor number %i\n", device.minor);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
	misc_deregister(&device);
}

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Arthur LAINE");
MODULE_DESCRIPTION("Misc char device driver + hello world");
