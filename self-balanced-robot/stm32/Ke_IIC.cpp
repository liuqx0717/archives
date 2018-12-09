#include "Ke_IIC.h"

#include "Ke_AddrDef.h"
#include "Ke_Delay.h"

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>


//配置IO输入输出方式
#define MPU_SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}  
#define MPU_SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;}

#define MPU_IIC_SCL  PBout(8)  //SCL
#define MPU_IIC_SDA  PBout(9)  //SDA OUT
#define MPU_READ_SDA PBin(9)   //SDA IN




//IIC初始化IIC
void MPU_IIC_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟

  	//GPIOB8,B9初始化设置
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化			 
  	MPU_IIC_SCL=1;
  	MPU_IIC_SDA=1;

  	Ke_Delay_Init();


}


//IIC起始信号
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();
	MPU_IIC_SDA=1;
	MPU_IIC_SCL=1;
	Ke_Delay_Delayus(4);
	MPU_IIC_SDA=0;
	Ke_Delay_Delayus(4);
	MPU_IIC_SCL=0;
}

//IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();
	MPU_IIC_SCL=0;
	MPU_IIC_SDA=0;
	Ke_Delay_Delayus(4);
	MPU_IIC_SCL=1;
	MPU_IIC_SDA=1;
	Ke_Delay_Delayus(4);
}

//等待应答信号
//返回：0，接收成功
//      1，接收失败
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ErrTime=0;
	MPU_SDA_IN();
	MPU_IIC_SDA=1;
	Ke_Delay_Delayus(1);
	MPU_IIC_SCL=1;
	Ke_Delay_Delayus(1);
	while(MPU_READ_SDA)
	{
		ErrTime++;
		if(ErrTime>250)
			{
				MPU_IIC_Stop();
				return 1;
			}
	}
	MPU_IIC_SCL=0;
	return 0;
}


//产生ACK应答信号
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=0;
	Ke_Delay_Delayus(2);
	MPU_IIC_SCL=1;
	Ke_Delay_Delayus(2);
	MPU_IIC_SCL=0;
}

//不产生ACK应答信号
void MPU_IIC_Nack(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=1;
	Ke_Delay_Delayus(2);
	MPU_IIC_SCL=1;
	Ke_Delay_Delayus(2);
	MPU_IIC_SCL=0;
}

//IIC发送一个字节
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
	u8 t;   
	MPU_SDA_OUT(); 	    
	MPU_IIC_SCL=0;//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{
		MPU_IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		Ke_Delay_Delayus(2);   
		MPU_IIC_SCL=1;
		Ke_Delay_Delayus(2); 
		MPU_IIC_SCL=0;	
		Ke_Delay_Delayus(2);
    	}	 
} 	    
 
//读一个字节
//ack=1时,发送ACK
//ack=0时，发送Nack
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA设置为输入
	for(i=0;i<8;i++ )
	{
		MPU_IIC_SCL=0; 
		Ke_Delay_Delayus(2);
		MPU_IIC_SCL=1;
		receive<<=1;
		if(MPU_READ_SDA)receive++;   
		Ke_Delay_Delayus(1); 
	}					 
	if (!ack)
		MPU_IIC_Nack();//发送nACK
	else
		MPU_IIC_Ack(); //发送ACK   
	return receive;
}



