#include "Ke_TIM2.h"

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>



//void Ke_TIM2_Init()
//{
//
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                        //使能TIM2时钟  
//
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
//
//	//PA5 TIM2_CH1
//	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//
//	//PB3 TIM2_CH2
//	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//
//
//	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//使用编码器模式3，上升下降都计数
//	//TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3，上升下降都计数
//
//	
//	//TIM_ICStructInit(&TIM_ICInitStructure);//将结构体中的内容缺省输入
//	//TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//	//TIM_ICInitStructure.TIM_ICFilter = 6;  //选择输入比较滤波器 
//	//TIM_ICInit(TIM2, &TIM_ICInitStructure);//将TIM_ICInitStructure中的指定参数初始化TIM2
//
//	//TIM_ICStructInit(&TIM_ICInitStructure);//将结构体中的内容缺省输入
//	//TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	//TIM_ICInitStructure.TIM_ICFilter = 6;  //选择输入比较滤波器 
//	//TIM_ICInit(TIM2, &TIM_ICInitStructure);//将TIM_ICInitStructure中的指定参数初始化TIM2
//
//	TIM_ICStructInit(&TIM_ICInitStructure);//将结构体中的内容缺省输入
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择通道1     
//												  //TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Falling; //下降沿捕获 
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //IC1映射到TI1上 
//																 //TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;  //配置输入分频，不分频
//																 //TIM_ICInitStruct.TIM_ICFilter=0X00;//配置输入滤波器 不滤波
//	TIM_ICInit(TIM2, &TIM_ICInitStructure);
//
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //选择通道1     
//												  //TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Falling; //下降沿捕获 
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //IC2映射到TI2上
//	TIM_ICInit(TIM2, &TIM_ICInitStructure);
//
//
//
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//
//	TIM_DeInit(TIM2);
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;  //设定计数器重装值 
//	TIM_TimeBaseStructure.TIM_Prescaler = 65535; //TIM3时钟预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数 
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//
//
//	//Reset counter
//	TIM2->CNT = 0;//
//
//	TIM_Cmd(TIM2, ENABLE);   //启动TIM2定时器
//
//
//
//}

//void Ke_TIM2_Init()
//{
//
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);                        //使能TIM2时钟  
//
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM2);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM2);
//
//	//PA5 TIM2_CH1
//	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//
//	//PB3 TIM2_CH2
//	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//
//
//	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//使用编码器模式3，上升下降都计数
//
//
//	TIM_ICStructInit(&TIM_ICInitStructure);//将结构体中的内容缺省输入
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//	TIM_ICInitStructure.TIM_ICFilter = 6;  //选择输入比较滤波器 
//	TIM_ICInit(TIM4, &TIM_ICInitStructure);//将TIM_ICInitStructure中的指定参数初始化TIM2
//
//	TIM_ICStructInit(&TIM_ICInitStructure);//将结构体中的内容缺省输入
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICInitStructure.TIM_ICFilter = 6;  //选择输入比较滤波器 
//	TIM_ICInit(TIM4, &TIM_ICInitStructure);//将TIM_ICInitStructure中的指定参数初始化TIM2
//
//
//
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//
//	TIM_DeInit(TIM4);
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  //设定计数器重装值 
//	TIM_TimeBaseStructure.TIM_Prescaler = 65535; //TIM3时钟预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数 
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//
//
//	//Reset counter
//	TIM4->CNT = 0;//
//
//	TIM_Cmd(TIM4, ENABLE);   //启动TIM2定时器
//
//
//
//}



//void Ke_TIM2_Init()
//{
//
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                        //使能TIM2时钟  
//
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
//
//	//PA5 TIM2_CH1
//	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//
//	//PB3 TIM2_CH2
//	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//
//
//	//TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//使用编码器模式3，上升下降都计数
//	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3，上升下降都计数
//																											 //TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3，上升下降都计数
//
//																			 //TIM_ICInit(TIM2, &TIM_ICInitStructure);//将TIM_ICInitStructure中的指定参数初始化TIM2
//
//	TIM_ICStructInit(&TIM_ICInitStructure);//将结构体中的内容缺省输入
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择通道1     
//	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling; //下降沿捕获 
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //IC1映射到TI1上 
//	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;  //配置输入分频，不分频
//	TIM_ICInitStructure.TIM_ICFilter=0X00;//配置输入滤波器 不滤波
//	TIM_ICInit(TIM3, &TIM_ICInitStructure);
//
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //选择通道2     
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; //下降沿捕获 
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //IC1映射到TI1上 
//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  //配置输入分频，不分频
//	TIM_ICInitStructure.TIM_ICFilter = 0X00;//配置输入滤波器 不滤波
//	TIM_ICInit(TIM3, &TIM_ICInitStructure);
//
//
//
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//
//	TIM_DeInit(TIM3);
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  //设定计数器重装值 
//	TIM_TimeBaseStructure.TIM_Prescaler = 65535; //TIM3时钟预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数 
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//
//
//	//Reset counter
//	TIM3->CNT = 0;//
//
//	TIM_Cmd(TIM3, ENABLE);   //启动TIM2定时器
//
//
//
//}

void Ke_TIM2_Init()
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                        //使能TIM2时钟  


	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

	//PA5 TIM2_CH1
	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	//PB3 TIM2_CH2
	GPIO_StructInit(&GPIO_InitStructure);              //将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);



	TIM2->CCMR1 = 0;
	TIM2->CCER = 0;
	TIM2->SMCR = 0;

	TIM2->CCMR1 |= (1)/*CC1S*/ + (1 << 8)/*CC2S*/; 
	TIM2->CCER |= (0 << 1)/*CC1P*/ + (0 << 3)/*CC1NP*/;
	TIM2->CCMR1 |= (0 << 4)/*IC1F*/;
	TIM2->CCER |= (0 << 5)/*CC2P*/ + (0 << 7)/*CC2NP*/;
	TIM2->CCMR1 |= (0 << 12)/*IC2F*/;
	TIM2->SMCR = 3/*SMS*/;

	TIM2->CCER|=

	TIM2->CR1 |= 1/*CEN*/;



}



uint32_t Ke_TIM2_GetCount()
{
	return TIM2->CNT;
}





