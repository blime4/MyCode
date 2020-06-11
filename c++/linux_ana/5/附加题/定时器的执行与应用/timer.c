#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/kernel.h>

struct timer_list stimer; 
int timeout = 10 * HZ;

static void time_handler(unsigned long data){ 
  struct task_struct *p = (struct task_struct *)data;
  wake_up_process(p);
  printk("After wake up process the jiffies is:%ld\n", jiffies); 
}

static int __init timer_init(void){ 
  printk("Insmod!\n");
  init_timer(&stimer);
  stimer.data = (unsigned long)current; 
  stimer.expires = jiffies + timeout; 
  stimer.function = time_handler;
  add_timer(&stimer);
  printk("Before suspending a process,the jiffies is:%ld\n", jiffies);
  set_current_state(TASK_INTERRUPTIBLE);
  schedule(); 
  del_timer(&stimer); 
  return 0;
}
static void __exit timer_exit(void){
  printk("Rmmod!\n");
  return;
}
module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");
