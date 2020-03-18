#include <linux/module.h>
#include <checker.h>

int init_module(void)
{
    printk( KERN_INFO "Hello, loading" );
    call_me("Hello from my module!");
    return 0;
}

void cleanup_module(void)
{
    printk( KERN_INFO "Leaving" );
}

MODULE_LICENSE("GPL");
