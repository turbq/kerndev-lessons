#ifndef _CHECKER_H_
#define _CHECKER_H_

#define CHECKER_MACRO (printk( KERN_INFO "checker info" ))

void call_me(const char *message);
int array_sum(short *arr, size_t n);

#endif
