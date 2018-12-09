#ifndef __KE_IIC_H
#define __KE_IIC_H

#include "stm32f4xx.h"



void MPU_IIC_Init(void);  //IIC初始化函数
void MPU_IIC_Start(void); //IIC 开始信号
void MPU_IIC_Stop(void);  //IIC 停止信号
void MPU_IIC_Send_Byte(u8 txd); //IIC发送一字节
u8 MPU_IIC_Read_Byte(unsigned char ack); //IIC读取一字节
u8 MPU_IIC_Wait_Ack(void);  //IIC等待ACK信号
void MPU_IIC_Ack(void);  //发送ACK信号
void MPU_IIC_Nack(void); //不发送ACK信号

#endif
