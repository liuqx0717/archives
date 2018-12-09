#include "Ke_MotorControl.h"


#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>


void Ke_MotorControl_Init()
{
	//PC12: IN1
	//PC13: IN2
	//PC14: IN3
	//PC15: IN4


	//       IN1         IN2        电机
	//       X           X          停止
	//       0           0          制动
	//       0           1          正转
	//       1           0          反转
	//       1           1          制动


	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTB时钟和PORTC
																					//将PC6复映射为TIM3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           //GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC12

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;           //GPIOC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC13

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOC14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC14

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;           //GPIOC15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化PC15

	Ke_MotorControl_ResetIN1();
	Ke_MotorControl_ResetIN2();
	Ke_MotorControl_ResetIN3();
	Ke_MotorControl_ResetIN4();

}

