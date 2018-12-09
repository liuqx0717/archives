#ifndef __KE_SYSTICK_H
#define __KE_SYSTICK_H

#include "stm32f4xx.h"

//时钟源为HCLK/8 = 168000000/8
//(HCLK/8/TickFreq)要为整数，最大为0xFFFFFFUL(24位)  
//此处没有开启Systick，要用Systick_Enable手动开
//回调函数处理时间不能超过回调周期，否则Ke_SysTick_GetTicks的返回值会不可靠（丢帧了）
uint32_t Ke_SysTick_Init(uint32_t TickFreq, void(*pfnCallback)());


//Enable后要过指定的间隔才会产生第一个回调，不会立刻产生一个回调。
void Ke_SysTick_Enable();
void Ke_SysTick_Disable();

//从上一次Enable开始，经历了多少次回调
uint32_t Ke_SysTick_GetTicks();


#endif // !__SYSTICK_H
