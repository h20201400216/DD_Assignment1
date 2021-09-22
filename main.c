#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/random.h>

#include "config.h"

#define SUCCESS 0
#define DEVICE_NAME "myimudrv"
#define BUF_LEN 20

static int device_Open = 0;
static char msg[BUF_LEN];
static char *msg_ptr;

static dev_t first; // variable for device number
static struct cdev c_dev; // variable for the character device structure
static struct class *cls; // variable for the device class

static int open_dev(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Mychar : open()\n");
	return 0;
}

static int close_dev(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Mychar : close()\n");
	return 0;
}
static ssize_t read_dev(struct file *f, char __user *buf, size_t len, loff_t *off)
{
 int val,i=0;
 char *addr;
 get_random_bytes(&val, sizeof(val));
 addr = (char *)&val;
 while(i<2)
 {
  printk(KERN_INFO "Copied Char:%d\n",*addr);
  put_user(*(addr++),buf++);
  i++;
 }
 put_user('\0',buf++);
 printk(KERN_INFO "Device read(Buf:%s,Len:%d,Data:%d)\n",buf,len,val);
 return i;
}

static ssize_t write_dev(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
 printk(KERN_INFO "Device write(Regsiter:%s)\n",buf);
 return len;
}
 
long ioctl_dev(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
 char *reg_no="0";
 int i;

 switch(ioctl_num)
 {
  case IOCTL_MAGNET_X:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_MAGNET_Y:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_MAGNET_Z:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_ACCEL_X:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_ACCEL_Y:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_ACCEL_Z:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_GYRO_X:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_GYRO_Y:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_GYRO_Z:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_PRESSURE:
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

 }

return SUCCESS;
}

static struct file_operations fops =
{
  .owner        = THIS_MODULE,
  .open         = open_dev,
  .release      = close_dev,
  .unlocked_ioctl = ioctl_dev,
  .read         = read_dev,
  .write        = write_dev
};

static int __init mydev_init(void)
{
 int ret_val;
 
 if ((ret_val=alloc_chrdev_region(&first,0,1, DEVICE_NAME)) < 0)
 {
  printk(KERN_INFO "Error Drv Register:%d\n",ret_val);
  return -1;
 }

 if ((cls = class_create(THIS_MODULE, "mychardrv")) == NULL)
 {
  printk(KERN_INFO "Class not created\n");
  unregister_chrdev_region(first, 1);
  return -1;
 }
 
 if (device_create(cls, NULL, first, NULL, "myimudrv") == NULL)
 {
  printk(KERN_INFO "Device not created\n");
  class_destroy(cls);
  unregister_chrdev_region(first, 1);
  return -1;
 }

 cdev_init(&c_dev, &fops);
 
 if (cdev_add(&c_dev, first, 1) == -1)
 {
  printk(KERN_INFO "CDEV Error");
  device_destroy(cls, first);
  class_destroy(cls);
  unregister_chrdev_region(first, 1);
  return -1;
 }
 printk(KERN_INFO "Driver Registered");

return 0;
}

static void __exit mydev_exit(void) 
{
 cdev_del(&c_dev);
 device_destroy(cls, first);
 class_destroy(cls);
 unregister_chrdev_region(first,1);
 printk(KERN_INFO "Driver unregistered\n");
}

module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JEEVARAAM K");
MODULE_DESCRIPTION("IMU V-Driver");
