#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
 
static int __init v_main(void)
{
    printk(KERN_INFO "Charlie's first driver registered\n");
    printk(KERN_INFO "Charlie, are you happy?\n");
    return 0;
}
 
static void __exit v_exit(void)
{
    printk(KERN_INFO "Charlie's first driver unregistered\n");
}
 
module_init(v_main);
module_exit(v_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Valera");
MODULE_DESCRIPTION("First driver");
