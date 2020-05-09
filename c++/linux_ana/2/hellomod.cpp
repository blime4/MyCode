#include <linux/module.h>    
#include <linux/kernel.h>    
#include <linux/init.h>      
 
static int __init lkp_init(void)   
{
    printk("<1> Hello,Kernel!\n");
    return 0;
}

static void __exit lkp_cleanup(void)
{
    printk("<1>Goodbye,World! leaving kernel space...\n");
 
}

module_init(lkp_init);  
module_exit(lkp_cleanup); 
MODULE_LICENSE("GPL"); 

