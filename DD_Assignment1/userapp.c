#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#include "config.h"

//IOCTL interface routines for 10 different reads

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

int ioctl_magnet_x(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_MAGNET_X,msg);
 return 0;
}

int ioctl_magnet_y(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_MAGNET_Y,msg);
 return 0;
}

int ioctl_magnet_z(int file_desc, char *msg)
{
 int ret_val;

 ret_val = ioctl(file_desc, IOCTL_MAGNET_Z,msg);
 return 0;
}

int main()
{
 int file_desc, ret_val,option;
 char *msg="From User space\n";
 char recv_msg[100];

 //Open the device
 file_desc = open(DEVICE_FILE_NAME,0);

 if(file_desc<0)
 {
  printf("Device file not opened. Name:%s\n",DEVICE_FILE_NAME);
  exit(-1);
 }

 //Basic Menu style options
 printf("1. Gyro\n2.Accelerometer\n3.Magnetometer\n4.Pressure\n5.Exit\n");
 start:
 printf("\nPlease Enter the option:");
 scanf("%d",&option);

 //Use IOCTL interface based on requested option
 switch(option)
 {
 case 1:
  ioctl_gyro_x(file_desc,recv_msg);
  printf("Gyro X:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  ioctl_gyro_y(file_desc,recv_msg);
  printf("Gyro Y:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);
 
  ioctl_gyro_z(file_desc,recv_msg);
  printf("Gyro Z:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);
 
  break;

 case 2:
  ioctl_accel_x(file_desc,recv_msg);
  printf("Accel X:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  ioctl_accel_y(file_desc,recv_msg);
  printf("Accel Y:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  ioctl_accel_z(file_desc,recv_msg);
  printf("Accel Z:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  break;

 case 3:
  ioctl_magnet_x(file_desc,recv_msg);
  printf("Magnet X:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  ioctl_magnet_y(file_desc,recv_msg);
  printf("Magnet Y:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  ioctl_magnet_z(file_desc,recv_msg);
  printf("Magnet Z:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  break;

 case 4:
  ioctl_pressure(file_desc,recv_msg);
  printf("Pressure:%X",recv_msg[0]);
  printf("%X\n",recv_msg[1]);

  break;

 case 5:goto end; break;
 default:
  printf("Please enter valid Option\n");
 }
 goto start;
 end:
 close(file_desc); //Close the file
 return 0;
}
