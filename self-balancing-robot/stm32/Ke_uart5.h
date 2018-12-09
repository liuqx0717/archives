#ifndef __KE_UART5_H
#define __KE_UART5_H

#include "stm32f4xx.h"

#define KE_UART5_RECEIVE_BUFFERSIZE 4096
#define KE_UART5_SEND_BUFFERSIZE 1024


//参数：处理接收数据的回调函数地址
void Ke_UART5_Init(uint32_t BaudRate, void(*pfnCallback)(const void *data, uint32_t size_in_bytes));


void Ke_UART5_Send(const void *data, uint32_t size_in_bytes);



//这个函数将：关闭UART5，改波特率，开启UART5
void Ke_UART5_ChangeBaudRate(uint32_t NewBaudRate);

#endif