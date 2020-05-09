#include <linux/module.h>  
#include <linux/kernel.h> 
#include <linux/sched.h>   
#include <linux/uaccess.h> 
#include <linux/proc_fs.h> 

static struct proc_dir_entry *proc_parent; 
int len, temp;							   
char *msg;								  

static ssize_t read_proc(struct file *filp, char __user *buf, size_t count, loff_t *offp){ 
	if (count > temp){
		count = temp;
	}
	temp = temp - count;
	raw_copy_to_user(buf, msg, count);
	if (count == 0){
		temp = len;
	}
	return count;
}

static const struct file_operations proc_fops = {
	.read = read_proc
};

void create_new_proc_entry(void){ 
	proc_parent = proc_mkdir("hello", NULL);
	if (!proc_parent){
		printk(KERN_INFO "创建proc入口失败"); 
	}
	proc_create("world", 0, proc_parent, &proc_fops);
	msg = "hello world\n"; 
	len = strlen(msg);	   
	temp = len;
	printk(KERN_INFO "1.len=%d", len);
}

int proc_init(void){
	create_new_proc_entry();
	return 0;
}

void proc_cleanup(void)
{
	printk(KERN_INFO "清理模块\n");
	remove_proc_entry("hello", proc_parent);
	remove_proc_entry("world", NULL);
}

MODULE_LICENSE("GPL");
module_init(proc_init);	
module_exit(proc_cleanup);
