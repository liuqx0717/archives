#ifndef __KE_ADC_H
#define __KE_ADC_H

#include "stm32f4xx.h"

void Ke_ADC_Init();
uint16_t Ke_ADC_GetValue();  //不等待转换结束。所以返回的可能是上次的结果
void Ke_ADC_Refresh();
//void ADC_WaitForConverting();


#endif // !__ADC_H
