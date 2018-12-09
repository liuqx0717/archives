#include "Ke_TIM5.h"

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>


void Ke_TIM5_Init()
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);                        //使能TIM2时钟  

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

	//PA0 TIM5_CH1
	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	//PA1 TIM5_CH2
	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	TIM5->CCMR1 = 0;
	TIM5->CCER = 0;
	TIM5->SMCR = 0;

	TIM5->CCMR1 |= (1)/*CC1S*/ + (1 << 8)/*CC2S*/;
	TIM5->CCER |= (0 << 1)/*CC1P*/ + (0 << 3)/*CC1NP*/;
	TIM5->CCMR1 |= (0 << 4)/*IC1F*/;
	TIM5->CCER |= (0 << 5)/*CC2P*/ + (0 << 7)/*CC2NP*/;
	TIM5->CCMR1 |= (0 << 12)/*IC2F*/;
	TIM5->SMCR = 3/*SMS*/;

	TIM5->CR1 = 1/*CEN*/;

}


uint32_t Ke_TIM5_GetCount()
{
	return TIM5->CNT;
}