#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_mnor = 0;
static struct cdev *my_cdev;

#define MYDEV_NAME "mychardev"
#define KBUF_SIZE size_t ((10) * PAGE_SIZE)

static int __init init_module(void)
{
    printk( KERN_INFO "Hello, loading" );
    return 0;
}

static void __exit cleanup_module(void)
{
    printk( KERN_INFO "Leaving" );
}

module_init (init_chardev);
module_exit (exit_chardev);

MODULE_LICENSE("GPL");
