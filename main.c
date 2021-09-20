#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>

#include "config.h"

#define SUCCESS 0
#define DEVICE_NAME "myimudrv"
#define BUF_LEN 20

static int device_Open = 0;
static char msg[BUF_LEN];
static char *msg_ptr;

//static dev_t first; // variable for device number
static struct cdev c_dev; // variable for the character device structure
static struct class *cls; // variable for the device class

static int open_dev(struct inode *i, struct file *f)
{
 if(device_Open)
  return -EBUSY;

 device_Open++;

 printk(KERN_INFO "Device Open\n");
 return 0;
}

static int close_dev(struct inode *i, struct file *f)
{
 device_Open--;

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
 
long ioctl_dev(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{

 switch(ioctl_num)
 {
 }

return SUCCESS;
}

static struct file_operations fops =
{
  .owner 	= THIS_MODULE,
  .open 	= open_dev,
  .release 	= close_dev,
  .unlocked_ioctl = ioctl_dev,
  .read 	= read_dev,
  .write 	= write_dev
};
 

static int __init mydev_init(void)
{
 int ret_val;
 printk(KERN_INFO "Driver Registered");
 
 if ((ret_val=register_chrdev(MAGIC_NUM, DEVICE_NAME, &fops)) < 0)
 {
  printk(KERN_INFO "Error Drv Register:%d\n",ret_val);
  return -1;
 }

 if ((cls = class_create(THIS_MODULE, "mychardrv")) == NULL)
 {
  unregister_chrdev_region(MAGIC_NUM, 1);
  return -1;
 }
 
 if (device_create(cls, NULL, MAGIC_NUM, NULL, "myimudrv") == NULL)
 {
  class_destroy(cls);
  unregister_chrdev_region(MAGIC_NUM, 1);
  return -1;
 }

 cdev_init(&c_dev, &fops);
 
 if (cdev_add(&c_dev, MAGIC_NUM, 1) == -1)
 {
  device_destroy(cls, MAGIC_NUM);
  class_destroy(cls);
  unregister_chrdev_region(MAGIC_NUM, 1);
  return -1;
 }

return 0;
}

static void __exit mydev_exit(void) 
{
 cdev_del(&c_dev);
 device_destroy(cls, MAGIC_NUM);
 class_destroy(cls);
 unregister_chrdev_region(MAGIC_NUM, 1);
 printk(KERN_INFO "Driver unregistered\n");
}

module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JEEVARAAM K");
MODULE_DESCRIPTION("IMU V-Driver");
