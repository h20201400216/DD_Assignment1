#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#include "config.h"

int ioctl_gyro_x(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_GYRO_X,msg);
 return 0;
}

int ioctl_gyro_y(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_GYRO_Y,msg);
 return 0;
}

int ioctl_gyro_z(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_GYRO_Z,msg);
 return 0;
}

int ioctl_accel_x(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_ACCEL_X,msg);
 return 0;
}

int ioctl_accel_y(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_ACCEL_Y,msg);
 return 0;
}

int ioctl_accel_z(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_ACCEL_Z,msg);
 return 0;
}

int ioctl_pressure(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_PRESSURE,msg);
 return 0;
}

int main()
{
 int file_desc, ret_val;
 char *msg="From User space\n";

 file_desc = open(DEVICE_FILE_NAME,0);

 if(file_desc<0)
 {
  printf("Device file not opened. Name:%s\n",DEVICE_FILE_NAME);
  exit(-1);
 }

 ioctl_gyro_x(file_desc,msg);
 ioctl_gyro_y(file_desc,msg);
 ioctl_gyro_z(file_desc,msg);
 ioctl_accel_x(file_desc,msg);
 ioctl_accel_y(file_desc,msg);
 ioctl_accel_z(file_desc,msg);

 close(file_desc);
 return 0;
}
