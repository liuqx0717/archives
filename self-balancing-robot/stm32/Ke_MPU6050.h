////By Jason Yan

#ifndef __KE_MPU6050_H
#define __KE_MPU6050_H

#include "stm32f4xx.h"

//初始化MPU6050
u8 MPU_Init(void);

short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);  //gx、gy、gz为陀螺仪原始读数
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);  //ax、ay、az为加速度计原始读数

#endif


