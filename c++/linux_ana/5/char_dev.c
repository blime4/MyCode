#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

static struct cdev *demo_dev;
static dev_t dev_num;
static unsigned int dev_minor = 0;
static unsigned int major = 0;
static unsigned int minor = 0;


static int demodrv_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ERR "device driver is openning...\n");
	major = MAJOR(inode->i_rdev);
    	minor = MINOR(inode->i_rdev);
    	printk("%s: major=%d, minor=%d\n", __func__, major, minor);
	return 0;		
}

static ssize_t demodrv_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	printk("%s enter\n", __func__);
	return 0;
}

static ssize_t demodrv_write(struct file *filp, const char __user *buf, size_t len, loff_t *offp)
{
	printk("%s enter\n", __func__);
	return 0;
}


static const struct file_operations demodrv_fops = {
	.owner = THIS_MODULE,
	.open = demodrv_open,
	.read = demodrv_read,
	.write = demodrv_write,
};

static int __init simple_char_init(void)
{
	int ret;
	ret = alloc_chrdev_region(&dev_num, dev_minor, 1, 
		              "demo_dev");		
	if(ret < 0){
		printk(KERN_ERR "can not get a device number\n");
		return ret;
	}
	
	demo_dev = cdev_alloc();
	if(!demo_dev)
	{
		printk("cdev_alloc_failed\n");
		goto unregister_chrdev;
	}
	
	cdev_init(demo_dev, &demodrv_fops);
	ret = cdev_add(demo_dev, dev_num, 1);
	if(ret < 0){
		printk(KERN_ERR "cdev add error\n");
		goto cdev_add_err;
	}
	
	printk("successed register char device: %s\n", "demo_dev");
      printk("Major number=%d, Minor number=%d\n", MAJOR(dev_num), MINOR(dev_num));
	return 0;

cdev_add_err:
	cdev_del(demo_dev);
unregister_chrdev:
	unregister_chrdev_region(dev_num, 1);
	return ret;
}

static void __exit simple_char_exit(void)
{
	cdev_del(demo_dev);
	unregister_chrdev_region(dev_num, 1);
	printk(KERN_ERR "driver exit.....\n");
}
module_init(simple_char_init);
module_exit(simple_char_exit);
MODULE_LICENSE("GPL");