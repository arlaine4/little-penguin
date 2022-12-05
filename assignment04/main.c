#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hid.h>

static void hello_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "Hello, probe.\n");
	return(0);
}

static void hello_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO "USB device disconnected.\n");
}

static const struct usb_device_id hello_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, 
			USB_INTERFACE_SUBCLASS_BOOT, 
			USB_INTERFACE_PROTOCOL_KEYBOARD)},
	{ },
}

static struct usb_driver hello_driver = {
	.name = "hello_driver",
	.id_table = hello_table,
	.probe = hello_probe,
	.disconnect = hello_disconnect,
};

int	init_module(void)
{
	printk(KERN_INFO "Hello world !\n");
	return usb_register(&hello_driver);
}

void	cleanup_module(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur Laine");
MODULE_DESCRIPTION("Simple Hello World KM with USB keyboard connectivity tracking");

