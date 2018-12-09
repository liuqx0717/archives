#include "Ke_led0.h"

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

void Ke_LED0_Init()
{
	//定义IO初始化结构体   	PE3 : LED0的负极
	GPIO_InitTypeDef GPIO_InitStructure;

	//设置IO口时钟        
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);


	//管脚模式:输出口  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//类型:推挽模式  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	////上拉下拉设置  (输出为什么还要上拉下拉)
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//IO口速度  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	//管脚指定  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	//初始化  
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	Ke_LED0_Reset();
}


void Ke_LED0_Set()  //点亮 
{
	GPIO_WriteBit(GPIOE, GPIO_Pin_3, Bit_RESET);
}

void Ke_LED0_Reset()
{
	GPIO_WriteBit(GPIOE, GPIO_Pin_3, Bit_SET);
}