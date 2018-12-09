#ifndef __KE_TIM3_H
#define __KE_TIM3_H

#include "stm32f4xx.h"


//时钟频率：84M/(psc+1)
void Ke_TIM3_Init(u32 arr, u32 psc);

void Ke_TIM3_Set1(float portion);
void Ke_TIM3_Set2(float portion);



#endif // !__KE_TIM3_H
