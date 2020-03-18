#include <linux/module.h>
#include <linux/random.h>
#include <checker.h>

#define ARR_LEN 5

static void __exit exit_checker(void)
{
    CHECKER_MACRO;
}

int mysum(short *arr, size_t n)
{
    int sum=0;

    while(n--){
        sum += arr[n];
    }

    return sum;
}

int init_module(void)
{
    int i=0, sum=0, mySum=0;
    size_t n=ARR_LEN;
    
    CHECKER_MACRO;

    for(i=0;i<12;i++){
        short array[n];
        char buf[256];

        for(n=0;n<ARR_LEN;n++){
            get_random_bytes(&array[n], sizeof(int));
            array[n] = array[n] % 100;
            //printk( KERN_INFO "array[%d]=%d\n", (int) n, (int) array[n] );
        }
        sum = array_sum(array, n);
        mySum = mysum(array, n);

        generate_output(sum, array, ARR_LEN, buf);

        if (sum==mySum){
            printk( KERN_INFO "[kernel_mooc]: %s", buf );
            /*printk( KERN_INFO "[kernel_mooc]: <%d>", mySum );
            for(n=0;n<5;n++){
                printk( KERN_INFO "<%d>", array[n] );
            }*/
        } else {
            printk( KERN_ERR "[kernel_mooc]: %s", buf );
            /*printk( KERN_ERR "[kernel_mooc]: <%d>", mySum );
            for(n=0;n<5;n++){
                printk( KERN_ERR "<%d>", array[n] );
            }*/
        }

    }

    return 0;
}

module_exit(exit_checker);

MODULE_LICENSE("GPL");
