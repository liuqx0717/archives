#include "Ke_Delay.h"

#include "stm32f4xx.h"

#include "Ke_tim7.h"



static int32_t Delay_Count;


void Ke_Delay_Tim7CallBack()
{
	Delay_Count--;

}


void Ke_Delay_Init()
{
	Ke_TIM7_Init(21, &Ke_Delay_Tim7CallBack);
}



void Ke_Delay_Delayus(int32_t us)
{
	Delay_Count = us;
	Ke_TIM7_Enable();

	// 不能写while(Delay_Count); ，
	//因为如果计数过快，又有别的中断打断的话，可能再次读Delay_Count的时候它已经减成负数了。
	while (Delay_Count > 0) Ke_TIM7_CheckIRQ();
	Ke_TIM7_Disable();
}
