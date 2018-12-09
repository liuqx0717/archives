#include "Ke_TIM3.h"


#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数


static uint32_t Arr;

void Ke_TIM3_Init(u32 arr, u32 psc)
{
	//此部分需手动修改IO口设置

	Arr = arr;

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTB时钟和PORTC

																					//将PC6复映射为TIM3
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3); //GPIOB0复用为定时器3	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOC6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC6

														//将PC7复映射为TIM3
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3); //GPIOB0复用为定时器3	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC7


	//													//将PB0复映射为TIM3	
	//GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3); //GPIOB0复用为定时器3	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOB0
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	//GPIO_Init(GPIOB, &GPIO_InitStructure);              //初始化PB0

	//													//将PC9复映射为TIM3
	//GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3); //GPIOB0复用为定时器3	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOC9
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	//GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC9


	TIM_TimeBaseStructure.TIM_Prescaler = psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//初始化定时器3

												   //初始化TIM3 Channel 1 PWM模式	  PC6(TIM3_CH1)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器

													   //初始化TIM3 Channel 1 PWM模式	  PC7(TIM3_CH2)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器

	//												   //初始化TIM3 Channel 3 PWM模式	  PB0(TIM3_CH3)
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	//TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC3
	//TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器

	//												   //初始化TIM3 Channel 4 PWM模式	  PC9(TIM3_CH4)
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	//TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC4
	//TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器

	TIM_ARRPreloadConfig(TIM3, ENABLE);//ARPE使能 

	TIM_Cmd(TIM3, ENABLE);  //使能TIM3

	Ke_TIM3_Set1(0);
	Ke_TIM3_Set2(0);

}

//Pwm.c：基于tim3.c，改变pwm占空比
//导出PWM_Init()，初始化
//导出PWM_SetLeft (…)，改变左轮PWM
//导出PWM_SetRright (…)，改变右轮PWM



void Ke_TIM3_Set1(float portion)
{
	u32 b;
	b = (u32)(portion * Arr);
	TIM_SetCompare1(TIM3, b);
}

void Ke_TIM3_Set2(float portion)
{
	u32 b;
	b = (u32)(portion * Arr);
	TIM_SetCompare2(TIM3, b);
}

//void Set3(float a)
//{
//	u32 b;
//	b = (u32)(a * 200);
//	TIM_SetCompare3(TIM3, b);
//}
//
//
//void Set4(float a)
//{
//	u32 b;
//	b = (u32)(a * 200);
//	TIM_SetCompare4(TIM3, b);
//}
