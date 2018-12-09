#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f4xx.h"

int32_t Encoder_GetLeftPosition();

int32_t Encoder_GetRightPosition();

int32_t Encoder_GetLeftSpeed();

int32_t Encoder_GetRightSpeed();

int32_t Encoder_GetLeftAcc();

int32_t Encoder_GetRightAcc();

//每隔一定的时间调用，否则上面几个函数的返回值不会变。
void Encoder_Update();


#endif // !__ENCODER_H
