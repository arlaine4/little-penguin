// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>

static int hello_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	printk(KERN_INFO "Hello, probe.\n");
	return 0;
}

static void hello_disconnect(struct usb_interface *intf)
{
	printk(KERN_INFO "USB device disconnected.\n");
}

static const struct usb_device_id hello_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{ },
};

MODULE_DEVICE_TABLE(usb, hello_table);

/*
 * probe and disconnect are function pointers called when a device
 * that matches the informations provided in the id_table variable is either
 * seen or removed.
 */
static struct usb_driver hello_driver = {
	.name = "hello_driver",
	.id_table = hello_table,
	.probe = hello_probe,
	.disconnect = hello_disconnect,
};

int	init_module(void)
{
	printk(KERN_INFO "Hello world !\n");
	/*
	 * usb_register is a built-in function that takes a usb_driver struct pointer
	 * as parameter. Define usb_elements inside the usb_driver struct
	 */
	return usb_register(&hello_driver);
}

void	cleanup_module(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
	usb_deregister(&hello_driver);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur Laine");
MODULE_DESCRIPTION("Simple Hello World KM with USB keyboard connectivity tracking");

