#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first; // variable for device number
static struct cdev c_dev; // variable for the character device structure
static struct class *cls; // variable for the device class

static int open_dev(struct inode *i, struct file *f)
{
 printk(KERN_INFO "Device Open\n");
 return 0;
}

static int close_dev(struct inode *i, struct file *f)
{
 printk(KERN_INFO "Device Close\n");
 return 0;
}

static ssize_t read_dev(struct file *f, char __user *buf, size_t len, loff_t *off)
{
 printk(KERN_INFO "Device read\n");
 return 0;
}

static ssize_t write_dev(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
 printk(KERN_INFO "Device write\n");
 return len;
}
 
static struct file_operations fops =
{
  .owner 	= THIS_MODULE,
  .open 	= open_dev,
  .release 	= close_dev,
  .read 	= read_dev,
  .write 	= write_dev
};
 

static int __init mydev_init(void)
{
 printk(KERN_INFO "Driver Registered");
 
 if (alloc_chrdev_region(&first, 0, 1, "BPHC") < 0)
 {
  return -1;
 }

 if ((cls = class_create(THIS_MODULE, "mychardrv")) == NULL)
 {
  unregister_chrdev_region(first, 1);
  return -1;
 }
 
 if (device_create(cls, NULL, first, NULL, "myimudrv") == NULL)
 {
  class_destroy(cls);
  unregister_chrdev_region(first, 1);
  return -1;
 }

 cdev_init(&c_dev, &fops);
 
 if (cdev_add(&c_dev, first, 1) == -1)
 {
  device_destroy(cls, first);
  class_destroy(cls);
  unregister_chrdev_region(first, 1);
  return -1;
 }

return 0;
}

static void __exit mydev_exit(void) 
{
 cdev_del(&c_dev);
 device_destroy(cls, first);
 class_destroy(cls);
 unregister_chrdev_region(first, 1);
 printk(KERN_INFO "Driver unregistered\n");
}

module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JEEVARAAM K");
MODULE_DESCRIPTION("IMU V-Driver");
