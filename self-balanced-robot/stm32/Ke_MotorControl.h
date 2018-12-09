#ifndef __KE_MOTORCONTROL_H
#define __KE_MOTORCONTROL_H

#include <stm32f4xx_gpio.h>


//       IN1         IN2        电机
//       X           X          停止
//       0           0          制动
//       0           1          正转
//       1           0          反转
//       1           1          制动




void Ke_MotorControl_Init();

inline void Ke_MotorControl_SetIN1()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
}

inline void Ke_MotorControl_ResetIN1()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
}

inline void Ke_MotorControl_SetIN2()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}

inline void Ke_MotorControl_ResetIN2()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

inline void Ke_MotorControl_SetIN3()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET);
}

inline void Ke_MotorControl_ResetIN3()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET);
}

inline void Ke_MotorControl_SetIN4()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_SET);
}

inline void Ke_MotorControl_ResetIN4()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_RESET);
}
#endif // !__KE_MOTORCONTROL_H
