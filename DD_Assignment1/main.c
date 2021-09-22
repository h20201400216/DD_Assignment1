//Kernel Includes

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/random.h>

//Common Header for IOCTL Interface

#include "config.h"

//Basic defines for frequent usage values
#define SUCCESS 0
#define DEVICE_NAME "imu_char"

static dev_t first; // variable for device number
static struct cdev c_dev; // variable for the character device structure
static struct class *cls; // variable for the device class

static int device_open = 0; //Device busy flag variable
static int bit_select = 0; //MPU9255 and BMP280 read switch flag


//Open Attached Character Device
static int open_dev(struct inode *i, struct file *f)
{
        if(device_open) //Device busy check
         return -EBUSY;

        device_open++; //Raise busy flag
        try_module_get(THIS_MODULE);

	printk(KERN_INFO "Device Open\n");
	return SUCCESS;
}

static int close_dev(struct inode *i, struct file *f)
{
        device_open--; //Reset the device busy flag
        module_put(THIS_MODULE);

	printk(KERN_INFO "Device Close\n");
	return SUCCESS;
}
static ssize_t read_dev(struct file *f, char __user *buf, size_t len, loff_t *off)
{
 uint16_t val,i=0; //Val - Variable to hold random number
 char *addr;
 get_random_bytes(&val, sizeof(val)); //Generate random number and store it
 
 if(bit_select) //MPU9255 and BMP280 switch
 {
  val = val%1023;
 }

 addr = (char *)&val;
 while(i<2)
 {
  //printk(KERN_INFO "Copied Char:%d\n",*addr);
  put_user(*(addr++),buf++); //Copy generated value from kernel to user space
  i++;
 }
 //printk(KERN_INFO "Device read(Buf:%s,Len:%d,Data:%d)\n",buf,len,val);
 return i;
}

static ssize_t write_dev(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
 printk(KERN_INFO "Device write(Regsiter:%s)\n",buf); //Write to specific register to read a value
 return len;
}
 
long ioctl_dev(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
 char *reg_no="0"; //Register choose variable
 int i;

 bit_select=0; //Flag to switch between MPU9255 and BMP280
 switch(ioctl_num)
 {
  case IOCTL_MAGNET_X:
   reg_no="1";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_MAGNET_Y:
   reg_no="2";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_MAGNET_Z:
   reg_no="3";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_ACCEL_X:
   reg_no="4";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_ACCEL_Y:
   reg_no="5";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_ACCEL_Z:
   reg_no="6";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_GYRO_X:
   reg_no="7";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_GYRO_Y:
   reg_no="8";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_GYRO_Z:
   reg_no="9";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

  case IOCTL_PRESSURE:
   bit_select = 1;
   reg_no="10";
   i = write_dev(file,reg_no,2,0);
   i = read_dev(file, (char *)ioctl_param,2,0);
   put_user('\0',(char *)ioctl_param+i);
   break;

 }

return SUCCESS;
}

//File operations structure for Driver
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
 
 if (device_create(cls, NULL, first, NULL, "imu_char") == NULL)
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
