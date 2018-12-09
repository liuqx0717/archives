#ifndef __KE_TIM7_H
#define __KE_TIM7_H

#include "stm32f4xx.h"

//计数频率:21 000 000 Hz    经历interval个计数后回调一次
//即：每 (interval/21) us 回调一次
//interval不能为1
//初始化之后需要手动启动定时器
void Ke_TIM7_Init(uint16_t interval, void(*pfnCallback)());


//Enable后要过指定的间隔才会产生第一个回调，不会立刻产生一个回调。
void Ke_TIM7_Enable();
void Ke_TIM7_Disable();

//可以在计数的同时修改
void Ke_TIM7_ChangeInterval(uint16_t interval);


//防止因中断丢帧而造成delay无法退出
void Ke_TIM7_CheckIRQ();

#endif // !__TIM6_H
