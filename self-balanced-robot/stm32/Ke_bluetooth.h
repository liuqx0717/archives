#ifndef __KE_BLUETOOTH_H
#define __KE_BLUETOOTH_H

#include "stm32f4xx.h"


void Ke_Bluetooth_Init(uint32_t BaudRate, void(*pfnCallback)(const void *data, uint32_t size_in_bytes));

void Ke_Bluetooth_Send(const void *data, uint32_t size_in_bytes);

void Ke_Bluetooth_SendString(const char *str);

void Ke_Bluetooth_ChangeUSARTBaudRate(uint32_t BaudRate);


//这里没用到这个函数，把它注释掉
//uint8_t Ke_Bluetooth_IsConnected();





#endif