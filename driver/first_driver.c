// http://www.opensourceforu.com/2011/10/usb-drivers-in-linux-1/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define VENDOR 0x0b05
#define PRODUCT_ID 0x1743


static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "Charlie Audio (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
    return 0;
}

static void pen_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "Charlie Audio removed\n");
}

static struct usb_device_id pen_table[] =
{
    { USB_DEVICE(VENDOR, PRODUCT_ID) },
    {} /* Terminating entry */
};

MODULE_DEVICE_TABLE (usb, pen_table);

static struct usb_driver pen_driver =
{
    .name = "charlie_audio",
    .id_table = pen_table,
    .probe = pen_probe,
    .disconnect = pen_disconnect,
};

static int __init pen_init(void)
{
    return usb_register(&pen_driver);
}

static void __exit pen_exit(void)
{
    usb_deregister(&pen_driver);
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Charlie");
MODULE_DESCRIPTION("Asus Xonar U1 Registration Driver");
