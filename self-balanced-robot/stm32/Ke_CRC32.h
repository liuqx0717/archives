#ifndef __KE_CRC32_H
#define __KE_CRC32_H

#include "stm32f4xx.h"


void Ke_CRC32_Init();




//这个CRC32算法不同于主流算法。
//例如当data是uint8_t数组，其值为：
//0x12, 0x34, 0x56, 0x78,      0x11, 0x22, 0x33, 0x44,      0xAB, 0xCD
//那么此函数计算所得的值与0xFFFFFFFF异或后 等于 主流算法计算下面的数据的值：
//0x78, 0x56, 0x34, 0x12,      0x44, 0x33, 0x22, 0x11,      0x00, 0x00, 0xCD, 0xAB
uint32_t Ke_CRC32_Calc(void *data, uint32_t size_in_bytes);



#endif // !__CRC32_H
