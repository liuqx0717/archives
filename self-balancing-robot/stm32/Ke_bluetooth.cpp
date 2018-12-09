#include "Ke_bluetooth.h"
#include "Ke_usart3.h"

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#include <string.h>





void Ke_Bluetooth_Init(uint32_t BaudRate, void(*pfnCallback)(const void *data, uint32_t size_in_bytes))
{

	////定义IO初始化结构体   	 PF13 : STATE;    PF12 : EN(一般用不到)
	//GPIO_InitTypeDef GPIO_InitStructure;

	////设置IO口时钟 
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	////管脚模式:输入口  
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	////上拉下拉设置  
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	////IO口速度  
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	////管脚指定  
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	////初始化  
	//GPIO_Init(GPIOF, &GPIO_InitStructure);


	//串口初始化
	Ke_USART3_Init(BaudRate, pfnCallback);


}


void Ke_Bluetooth_Send(const void *data, uint32_t size_in_bytes)
{
	Ke_USART3_Send(data, size_in_bytes);
}

void Ke_Bluetooth_SendString(const char *str)
{
	Ke_Bluetooth_Send(str, strlen(str) + 1);   //字符串结束标志'\0'也要发
}

void Ke_Bluetooth_ChangeUSARTBaudRate(uint32_t BaudRate)
{
	Ke_USART3_ChangeBaudRate(BaudRate);
}

//uint8_t Ke_Bluetooth_IsConnected()
//{
//	return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13);
//}