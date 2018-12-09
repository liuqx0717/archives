#include "LED.h"

#include "stm32f4xx.h"

#include "Ke_led0.h"

//是否初始化了
bool Initialized = false;


void LED_Init()
{
	if (!Initialized) {
		Initialized = true;
		
		Ke_LED0_Init();



	}
}



void LED_Set(uint32_t id)
{
	LED_Init();

	switch (id)
	{
	case 0:
		Ke_LED0_Set();
		break;

	default:
		break;
	}
}


void LED_Reset(uint32_t id)
{
	LED_Init();

	switch (id)
	{
	case 0:
		Ke_LED0_Reset();
		break;

	default:
		break;
	}
}
