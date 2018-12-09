#ifndef __KE_USART3_H
#define __KE_USART3_H

#include "stm32f4xx.h"


#define KE_USART3_RECEIVE_BUFFERSIZE 8192
#define KE_USART3_SEND_BUFFERSIZE 2048


//参数：处理接收数据的回调函数地址
void Ke_USART3_Init(uint32_t BaudRate, void(*pfnCallback)(const void *data, uint32_t size_in_bytes));


void Ke_USART3_Send(const void *data, uint32_t size_in_bytes);


//这个函数将：关闭USART3，改波特率，开启USART3
void Ke_USART3_ChangeBaudRate(uint32_t NewBaudRate);




#endif