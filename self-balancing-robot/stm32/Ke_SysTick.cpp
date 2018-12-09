#include "Ke_SysTick.h"

#include <stm32f4xx_rcc.h>

//回调函数的地址
static void(*pfnCallback)();

//从上一次Enable开始，经历了多少次回调
//回调函数处理时间不能超过回调周期，否则Ticks会不可靠（丢帧了）
static uint32_t Ticks;

uint32_t Ke_SysTick_Init(uint32_t TickFreq, void(*pfnCallback)())
{
	uint32_t ticks = 168000000 / 8 / TickFreq;
	pfnCallback = pfnCallback;

	//ticks最大位数为24位，超出范围就返回 1
	if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk) { return (1UL); }    /* Reload value impossible */

	SysTick->LOAD = (uint32_t)(ticks - 1UL);                         /* set reload register */
	NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
	SysTick->VAL = 0UL;                                             /* Load the SysTick Counter Value */
	SysTick->CTRL = 
		(0UL << SysTick_CTRL_CLKSOURCE_Pos) |   //时钟源 0为HCLK/8   1为HCLK
		(1UL << SysTick_CTRL_TICKINT_Pos) |     //是否启用中断   1为启用    0为禁用
		(0UL << SysTick_CTRL_ENABLE_Pos);       //是否开启计时器 1为启用    0为禁用                  
	return (0UL);                                                     /* Function successful */
}


//Enable后要过指定的间隔才会产生第一个回调，不会立刻产生一个回调。
void Ke_SysTick_Enable()
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void Ke_SysTick_Disable()
{
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

uint32_t Ke_SysTick_GetTicks()
{
	return Ticks;
}

extern "C" void SysTick_Handler()     //这个中断不能叠加，如果处理时间过长可能发生丢帧现象
{
	Ticks++;
	if(pfnCallback) (*pfnCallback)();
}
