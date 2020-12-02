#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 240, my_minor = 0;
static struct cdev *my_cdev;
static int m=0, n=0;
static int Device_Open = 0;
static char msg[10];
static char *p_msg;

#define MYDEV_NAME "solution_node"
#define KBUF_SIZE (size_t) ((10) * PAGE_SIZE)

static int mychrdev_open(struct inode *inode, struct file *file)
{
    if (Device_Open)
        return -EBUSY;

    Device_Open++;

    printk(KERN_INFO "opening device %s %d times:\n\n", MYDEV_NAME, m++);
    try_module_get(THIS_MODULE);

    return 0;
}

static int mychrdev_release (struct inode *inode, struct file *file)
{
    Device_Open--;

    printk(KERN_INFO "chardev release %s:\n\n", MYDEV_NAME);

    module_put(THIS_MODULE);

    return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
    int nbytes=0;
    static int reads=0;

    sprintf(msg, "%d %d\n", m, n);
    p_msg = msg;

    reads++;
    if (reads==2){
        reads = 0;
        *p_msg = 0;
    }
    if (*p_msg ==0)
        return 0;

    while (lbuf && *p_msg) {
        put_user(*(p_msg++), buf++);

        lbuf--;
        nbytes++;
    }

    printk(KERN_INFO "read device %s", MYDEV_NAME);

    return nbytes;
}

static ssize_t mychrdev_write(struct file * file, const char __user *buf,
        size_t lbuf, loff_t *ppos)
{
    int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
    *ppos += nbytes;

    printk(KERN_INFO "write device %s nbytes = %d ppos = %d:\n\n", MYDEV_NAME,
            nbytes, (int) *ppos);
    n += nbytes;

    return nbytes;
}

static const struct file_operations mycdev_fops = {
    .owner = THIS_MODULE,
    .read = mychrdev_read,
    .write = mychrdev_write,
    .open = mychrdev_open,
    .release = mychrdev_release
};

static int __init init_chardev(void)
{
    printk( KERN_INFO "Hello, loading" );
    kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
    
    first = MKDEV (my_major, my_minor);
    register_chrdev_region (first,count,MYDEV_NAME);

    my_cdev = cdev_alloc();

    cdev_init(my_cdev, &mycdev_fops);
    cdev_add(my_cdev, first, count);

    return 0;
}

static void __exit cleanup_chardev(void)
{
    printk( KERN_INFO "Leaving" );
}

module_init (init_chardev);
module_exit (cleanup_chardev);

MODULE_LICENSE("GPL");
