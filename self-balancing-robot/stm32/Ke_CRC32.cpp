#include "Ke_CRC32.h"

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_crc.h>


void Ke_CRC32_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
}




//这个CRC32算法不同于主流算法。
//例如当data是uint8_t数组，其值为：
//0x12, 0x34, 0x56, 0x78,      0x11, 0x22, 0x33, 0x44,      0xAB, 0xCD
//那么此函数计算所得的值与0xFFFFFFFF异或后 等于 主流算法计算下面的数据的值：
//0x78, 0x56, 0x34, 0x12,      0x44, 0x33, 0x22, 0x11,      0x00, 0x00, 0xCD, 0xAB
uint32_t Ke_CRC32_Calc(void *data, uint32_t size_in_bytes)
{
	CRC->CR = CRC_CR_RESET;

	uint32_t n = size_in_bytes / 4;
	uint32_t i;

	for (i = 0; i < n; i++) {     //每4字节处理一次
		CRC->DR = *((uint32_t*)data + i);
	}

	n = size_in_bytes - 4 * i;

	if (n > 0) {                  //处理最后几个字节

		uint8_t *CurrentPos = (uint8_t*)data + 4 * i;
		uint32_t last = 0;        //最后四个字节清零

		for (i = 0; i < n; i++) {     
			((uint8_t*)(&last))[i] = CurrentPos[i];
		}

		CRC->DR = last;
	}

	return CRC->DR;
	
}