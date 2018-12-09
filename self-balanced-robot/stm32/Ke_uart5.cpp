#include "Ke_uart5.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_dma.h>
#include <misc.h>
#include <string.h>


static uint8_t ReceiveBuffer[KE_UART5_RECEIVE_BUFFERSIZE];
static uint8_t SendBuffer[KE_UART5_SEND_BUFFERSIZE];

//回调函数地址
static void(*pfnCallback)(const void *data, uint32_t size_in_bytes);

//上一次传输到了ReceiveBuffer中的第几个字节
static uint32_t LastPos;    

//当前是否正在发送
static bool Sending; 


void Ke_UART5_Init(uint32_t BaudRate, void(*pfnCallback)(const void *data, uint32_t size_in_bytes))
{
	pfnCallback = pfnCallback;

	//定义中断结构体  
	NVIC_InitTypeDef NVIC_InitStructure;

	//定义IO初始化结构体   	PC12 : UART5_TX;   PD2 : UART5_RX
	GPIO_InitTypeDef GPIO_InitStructure;

	//设置IO口时钟        
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

	//管脚模式:输出口  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//类型:推挽模式  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	////上拉下拉设置  (输出为什么还要上拉下拉)
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//IO口速度  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	//管脚指定  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	//初始化  
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//管脚模式:输入口  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//上拉下拉设置  
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//IO口速度  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	//管脚指定  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	//初始化  
	GPIO_Init(GPIOD, &GPIO_InitStructure);




	//定义串口结构体    
	USART_InitTypeDef USART_InitStructure;

	//打开串口对应的外设时钟    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	//初始化串口参数    
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate = BaudRate;
	//初始化串口   
	USART_Init(UART5, &USART_InitStructure);

	//中断配置  
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;               //通道设置为串口中断 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //中断占先等级  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
	NVIC_Init(&NVIC_InitStructure);

	//使能中断  
	USART_ITConfig(UART5, USART_IT_TC, DISABLE);        //发送完成
	USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);      //准备好读取接收到的数据
	USART_ITConfig(UART5, USART_IT_TXE, DISABLE);       //发送数据寄存器为空
	USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);       //检测到空闲线路




	//定义DMA结构体          
	DMA_InitTypeDef DMA_InitStructure;

	//串口发DMA配置    UART5_TX : stream7,channel4;     UART5_RX : stream0,channel4
	//启动DMA时钟  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	//DMA通道配置  
	DMA_DeInit(DMA1_Stream7);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	//外设地址  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART5->DR);
	//内存地址  
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)SendBuffer;
	//dma传输方向  
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	//内存中用于存放DMA数据的长度
	DMA_InitStructure.DMA_BufferSize = KE_UART5_SEND_BUFFERSIZE;
	//内存数据字长  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	//设置DMA的内存递增模式  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//外设数据字长  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//设置DMA的外设递增模式，一个外设  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//设置DMA的传输模式  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//设置DMA的优先级别  
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	//指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	//指定了FIFO阈值水平  (这里好像没卵用)
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	//指定的Burst转移配置内存传输  (这里好像没卵用)
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	//指定的Burst转移配置外围转移  (这里好像没卵用)  
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	//配置DMA1的通道           
	DMA_Init(DMA1_Stream7, &DMA_InitStructure);
	//DMA发送中断设置  
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream7_IRQn;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//使能中断  
	DMA_ITConfig(DMA1_Stream7, DMA_IT_TC, ENABLE);   //传输完成中断


	//串口收DMA配置    
	//DMA通道配置  
	DMA_DeInit(DMA1_Stream0);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	//外设地址  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART5->DR);
	//内存地址  
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ReceiveBuffer;
	//dma传输方向  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	//内存中用于存放DMA数据的长度，存满了之后会触发接收DMA的传输完成中断
	DMA_InitStructure.DMA_BufferSize = KE_UART5_RECEIVE_BUFFERSIZE;
	//内存数据字长  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	//设置DMA的内存递增模式  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//外设数据字长  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//设置DMA的外设递增模式，一个外设  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//设置DMA的传输模式  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//设置DMA的优先级别  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	//指定了FIFO阈值水平  (这里好像没卵用)
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	//指定的Burst转移配置内存传输  (这里好像没卵用)
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	//指定的Burst转移配置外围转移  (这里好像没卵用) 
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	//配置DMA1的通道           
	DMA_Init(DMA1_Stream0, &DMA_InitStructure);
	
	//DMA接收中断设置  
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//使能中断  
	DMA_ITConfig(DMA1_Stream0, DMA_IT_TC, ENABLE);   //传输完成中断

	//使能接收DMA 
	DMA_Cmd(DMA1_Stream0, ENABLE);

	Sending = false;


	//采用DMA方式发送  
	USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);
	//采用DMA方式接收  
	USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);


	//启动串口    
	USART_Cmd(UART5, ENABLE);

}


void Ke_UART5_Send(const void *data, uint32_t size_in_bytes)
{
	//防止 size_in_bytes 超出范围
	size_in_bytes = size_in_bytes <= KE_UART5_SEND_BUFFERSIZE ? size_in_bytes : KE_UART5_SEND_BUFFERSIZE;

	//如果当前有数据正在发送，就等待其完成
	while (Sending);

	Sending = true;
	memcpy(SendBuffer, data, size_in_bytes);
	DMA_SetCurrDataCounter(DMA1_Stream7, size_in_bytes);
	DMA_Cmd(DMA1_Stream7, ENABLE);

}


void Ke_UART5_ChangeBaudRate(uint32_t NewBaudRate)
{

	USART_Cmd(UART5, DISABLE);


	USART_InitTypeDef USART_InitStructure;

	//初始化串口参数    
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate = NewBaudRate;
	//初始化串口   
	USART_Init(UART5, &USART_InitStructure);


	USART_Cmd(UART5, ENABLE);
}



extern "C" void DMA1_Stream7_IRQHandler()   //发送DMA中断   这个中断不能叠加
{
	if (DMA_GetITStatus(DMA1_Stream7, DMA_IT_TCIF7) != RESET) {    //传输完成中断
		//清除标志位  
		DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_TCIF7);

		Sending = false;
	}
}

extern "C" void DMA1_Stream0_IRQHandler()   //接收DMA中断(当ReceiveBuffer满的时候会触发)  这个中断不能叠加
{
	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0) != RESET) {
		//清除标志位  
		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);

		uint16_t size_to_read = KE_UART5_RECEIVE_BUFFERSIZE - LastPos;
		if (pfnCallback&&size_to_read)   
			(*pfnCallback)(ReceiveBuffer + LastPos, size_to_read);
		LastPos = 0;

	}
}


extern "C" void UART5_IRQHandler()           //串口传输空闲中断（每当一段连续的数据接收完成后会触发一次） 这个中断不能叠加
{
	
	if (USART_GetITStatus(UART5, USART_IT_IDLE) != RESET) {
		UART5->SR;
		UART5->DR;   //清除中断标识

		uint16_t size_to_read = KE_UART5_RECEIVE_BUFFERSIZE - DMA_GetCurrDataCounter(DMA1_Stream0) - LastPos;
		if (pfnCallback&&size_to_read) 
			(*pfnCallback)(ReceiveBuffer + LastPos, size_to_read);
		LastPos += size_to_read;
	}

}
