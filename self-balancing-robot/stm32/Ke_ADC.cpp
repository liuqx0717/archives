#include "Ke_ADC.h"

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_adc.h>
#include <misc.h>



/*

解决方法：在校准ADC之前，不要使能DMA，即二者的初始化顺序如下：
DMA_Cmd(DMA1_Channel1, ENABLE);
ADC_SoftwareStartConvCmd(ADC1, ENABLE);
原因：如果在初始化AD的时候DMA被触发了一次，但是此时并没有采样，但是DMA目的地址已经发生了自加，当你采样第一路的时候，数据却填充到了第二路。
校准AD的时候会触发DMA导致通道错位，因此校准AD基准前不要启用DMA。

*/


static uint16_t Value;

void Ke_ADC_Init()
{


	////设置IO口时钟        
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//													
	//GPIO_InitTypeDef GPIO_InitStructure;     //定义IO初始化结构体   	PC4 : ADC1_IN14

	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//不带上下拉
	//GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  


	//ADC_CommonInitTypeDef ADC_CommonInitStructure;

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	  //ADC1复位
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);	//复位结束	 

	//ADC_DeInit();
	//ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	//ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	//ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	//ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	//ADC_CommonInit(&ADC_CommonInitStructure);//初始化


	//ADC_InitTypeDef       ADC_InitStructure;

	//ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	//ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	//ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
	//ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	//ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	//ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中
	//ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期

	//ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
	//ADC_DMACmd(ADC1, ENABLE);

	//DMA_InitTypeDef DMA_InitStructure;

	////启动DMA时钟   DMA2_Stream4_Channel0
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	////DMA通道配置  
	//DMA_DeInit(DMA2_Stream4);
	//DMA_StructInit(&DMA_InitStructure);
	//DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	////外设地址  
	//DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(ADC1) + 0x4C;
	////内存地址  
	//DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Value;
	////dma传输方向  
	//DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	////内存中用于存放DMA数据的长度
	//DMA_InitStructure.DMA_BufferSize = 16;
	////内存数据字长  
	//DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	////外设数据字长  
	//DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	////设置DMA的外设递增模式，一个外设  
	//DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	////内存地址自增不允许
	//DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	////设置DMA的传输模式  
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	////设置DMA的优先级别  
	//DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	////指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
	//DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	////指定了FIFO阈值水平  (这里好像没卵用)
	//DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	////指定的Burst转移配置内存传输  (这里好像没卵用)
	//DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	////指定的Burst转移配置外围转移  (这里好像没卵用)  
	//DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	////配置DMA1的通道           

	//DMA_Init(DMA2_Stream4, &DMA_InitStructure);
	//DMA_Cmd(DMA2_Stream4, ENABLE);

	//NVIC_InitTypeDef NVIC_InitStructure;

	//NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream4_IRQn;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);
	////使能中断  
	//DMA_ITConfig(DMA2_Stream4, DMA_IT_TC, ENABLE);   //传输完成中断

	//ADC_SoftwareStartConv(ADC1);
	


	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

														 //先初始化ADC1通道5 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PA5 通道5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//不带上下拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);	//复位结束	 


	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道

	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	


}


uint16_t Ke_ADC_GetValue()
{
	//设置指定ADC的规则组通道，一个序列，采样时间
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    

	//ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	

	//while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

//uint16_t ADC_GetValue()
//
//	return Value;
//}

void Ke_ADC_Refresh()
{
	ADC_SoftwareStartConv(ADC1);

}

//extern "C" void DMA2_Stream4_IRQHandler()   //发送DMA中断   这个中断不能叠加
//{
//	if (DMA_GetITStatus(DMA2_Stream4, DMA_IT_TCIF4) != RESET) {    //传输完成中断
//																   //清除标志位  
//		DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_TCIF4);
//
//	}
//}
