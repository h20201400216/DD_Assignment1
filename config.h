#ifndef CHAR_CONFIG_H
#define CHAR_CONFIG_H

#include <linux/ioctl.h>

#define MAGIC_NUM 456

#define IOCTL_MAGNET_X _IOWR(MAGIC_NUM, 0, char *)
#define IOCTL_MAGNET_Y _IOWR(MAGIC_NUM, 1, char *)
#define IOCTL_MAGNET_Z _IOWR(MAGIC_NUM, 2, char *)
#define IOCTL_ACCEL_X _IOWR(MAGIC_NUM, 3, char *)
#define IOCTL_ACCEL_Y _IOWR(MAGIC_NUM, 4, char *)
#define IOCTL_ACCEL_Z _IOWR(MAGIC_NUM, 5, char *)
#define IOCTL_GYRO_X _IOWR(MAGIC_NUM, 6, char *)
#define IOCTL_GYRO_Y _IOWR(MAGIC_NUM, 7, char *)
#define IOCTL_GYRO_Z _IOWR(MAGIC_NUM, 8, char *)
#define IOCTL_PRESSURE _IOWR(MAGIC_NUM, 9, char *)

#define DEVICE_FILE_NAME "/dev/myimudrv"

#endif
