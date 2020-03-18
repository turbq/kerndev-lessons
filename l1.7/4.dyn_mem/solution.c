#include <linux/module.h>
#include <linux/slab.h>
#include <checker.h>

#define ARR_LEN 5

void *vp;
int *ip;
struct device *dp;

int init_module(void)
{
    vp = kmalloc(get_void_size(), GFP_KERNEL);
    ip = kmalloc(sizeof(int) * (get_int_array_size()), GFP_KERNEL);
    dp = kmalloc(sizeof(struct device), GFP_KERNEL);

    submit_void_ptr(vp);
    submit_int_array_ptr(ip);
    submit_struct_ptr(dp);

    printk( KERN_INFO "dyn_mem started succsesfully" );

    return 0;
}

void cleanup_module(void)
{
    checker_kfree(vp);
    checker_kfree(ip);
    checker_kfree(dp);
    
    printk( KERN_INFO "Leaving dyn_mem" );
}

MODULE_LICENSE("GPL");
