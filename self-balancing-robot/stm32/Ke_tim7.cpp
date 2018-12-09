#include "Ke_tim7.h"

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
#include <misc.h>


#define INIT_DELAY

static void(*pfnCallback)();


//计数频率:21 000 000 Hz    经历interval个计数后回调一次
//即：每 (interval/21) us 回调一次
//interval不能为1
//初始化之后需要手动启动定时器
void Ke_TIM7_Init(uint16_t interval, void(*pfnCallback)())
{
	//Tout = ((arr+1)*(psc+1))/Tclk;

	pfnCallback = pfnCallback;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_DeInit(TIM7);
	TIM_TimeBaseStructure.TIM_Period = interval - 1;   //虽然标的uint32_t，实际上是16位的  interval不能为1
	TIM_TimeBaseStructure.TIM_Prescaler = 4 - 1;      //计数频率变为 21 000 000
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);


	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#ifdef INIT_DELAY
	for (uint32_t i = 0; i < 100000; i++);
#endif // INIT_DELAY
}


//Enable后要过指定的间隔才会产生第一个回调，不会立刻产生一个回调。
void Ke_TIM7_Enable()
{
	TIM_Cmd(TIM7, ENABLE);
}


void Ke_TIM7_Disable()
{
	TIM_Cmd(TIM7, DISABLE);
}

void Ke_TIM7_ChangeInterval(uint16_t interval)
{
	TIM7->ARR = interval - 1;
}



extern "C" void TIM7_IRQHandler()           //这个中断不能叠加
{

	if (TIM_GetITStatus(TIM7, TIM_FLAG_Update) != RESET) {

		TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);
		if (pfnCallback) (*pfnCallback)();

	}

}


void Ke_TIM7_CheckIRQ()
{
	TIM7_IRQHandler();

}
