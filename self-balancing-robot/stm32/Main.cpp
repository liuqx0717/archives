#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>


#include "Ke_SysTick.h"
#include "Ke_bluetooth.h"


#include "StringAlg.h"
#include "AngleCalc.h"
#include "Variables.h"
#include "Message.h"
#include "Cmd.h"
#include "timer.h"
#include "MovementControl.h"
#include "Encoder.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>






void t()
{
	//static bool enabled;

	//if (enabled) {
	//	enabled = false;
	//	LED_Reset(0);
	//}
	//else {
	//	enabled = true;
	//	LED_Set(0);
	//}

	//static int n;
	//static float result;



}


extern float _Motor_base;

int main()
{


	Cmd_StartListening();
	//MovementControl_StartPIDInnerErrect();
	//MovementControl_StartPIDErrect();
	//MovementControl_StartPIDSpeed();
	MovementControl_Init();

	Variables_Register("base", Variables_Type_float, &_Motor_base);

	for (;;) {
		Message_MessageDef *Msg = Message_GetMessage();
		if (!Msg) continue;    //没有新消息


		switch (Msg->Type)
		{
		case Message_Type_CallFunc:
			(*(void(*)())(Msg->lParam))();
			break;

		case Message_Type_ParsePending:
			Cmd_ProcessMsgs((char*)(Msg->wParam), (char*)(Msg->lParam));
			break;



		//case Message_Type_LED:
		//	if ((bool)(Msg->lParam)) 
		//		LED_Set(Msg->wParam);
		//	else
		//		LED_Reset(Msg->wParam);



		default:
			break;
		}


	}


	
	


}



























//陀螺仪测试
//
//float angle2 = 0;
//
//void t()
//{
//	char str[256];
//	char f1[16];
//	char f2[16];
//	char f3[16];
//
//
//	float angle1 = AngleCalc_GetAngleFromAccelerometer();
//	StringAlg_ftoa(angle1, f1, 4);
//
//	angle2 += AngleCalc_GetDeltaAngleFromGyroscope();
//	StringAlg_ftoa(angle2, f2, 4);
//
//	float angle = AngleCalc_GetAngle();
//	StringAlg_ftoa(angle, f3, 4);
//
//	sprintf(str, "A:%s    G:%s    T:%s\r\n", f1, f2, f3);
//
//	Ke_Bluetooth_SendString(str);
//
//}
//
//int main()
//{
//	Ke_Bluetooth_Init(115200, NULL);
//	AngleCalc_Init(0.05);
//	Ke_SysTick_Init(20, &t);
//	Ke_SysTick_Enable();
//
//
//}








//Encoder.cpp测试
//void t()
//{
//
//
//	char str[256];
//	Encoder_Update();
//	int32_t pos1 = Encoder_GetLeftSpeed();
//	int32_t pos2 = Encoder_GetRightSpeed();
//	sprintf(str, "left: %d\t\tright:%d\r\n", pos1, pos2);
//	Ke_Bluetooth_SendString(str);
//
//}
//
//int main()
//{
//	
//	Ke_Bluetooth_Init(115200, NULL);
//	
//	Ke_SysTick_Init(10, &t);
//	Ke_SysTick_Enable();
//
//
//}









//寻找倾角机械零点
//void t()
//{
//char str[256];
//float angle2 = AngleCalc_GetAngle();
//StringAlg_ftoa(angle2, str, 4);
//strcat(str, "\r\n");
//Ke_Bluetooth_SendString(str);
//
//}
//
//int main()
//{
//	Ke_Bluetooth_Init(115200, NULL);
//	AngleCalc_Init(0.05, 0, 0, 0.5);
//	Ke_SysTick_Init(20, &t);
//	Ke_SysTick_Enable();
//
//
//}












//编码器测试
//void t()
//{
//	//static bool enabled;
//
//	//if (enabled) {
//	//	enabled = false;
//	//	LED_Reset(0);
//	//}
//	//else {
//	//	enabled = true;
//	//	LED_Set(0);
//	//}
//
//	//static int n;
//	//static float result;
//
//
//
//
//	char str[256];
//	int32_t pos = (int32_t)Ke_TIM5_GetCount();
//	itoa(pos, str, 10);
//	strcat(str, "\r\n");
//	Ke_Bluetooth_SendString(str);
//
//}
//
//int main()
//{
//	Ke_TIM5_Init();
//	Ke_Bluetooth_Init(115200, NULL);
//	AngleCalc_Init(0.1);
//	Ke_SysTick_Init(10, &t);
//	Ke_SysTick_Enable();
//
//
//}







//测试电机方向、转速
//uint32_t in1 = 1;
//uint32_t in2 = 0;
//uint32_t in3 = 0;
//uint32_t in4 = 0;
//
//float pwm1 = 0;
//float pwm2 = 0;
//
//
//void t()
//{
//
//
//	if (in1) Ke_MotorControl_SetIN1();
//	else Ke_MotorControl_ResetIN1();
//
//	if (in2) Ke_MotorControl_SetIN2();
//	else Ke_MotorControl_ResetIN2();
//
//	if (in3) Ke_MotorControl_SetIN3();
//	else Ke_MotorControl_ResetIN3();
//
//	if (in4) Ke_MotorControl_SetIN4();
//	else Ke_MotorControl_ResetIN4();
//
//	Ke_TIM3_Set1(pwm1);
//	Ke_TIM3_Set2(pwm2);
//
//
//}
//
//
//
//int main()
//{
//
//
//	Ke_TIM3_Init(3360 - 1, 0);
//	Ke_MotorControl_Init();
//
//	Variables_Register("in1", Variables_Type_uint32_t, &in1);
//	Variables_Register("in2", Variables_Type_uint32_t, &in2);
//	Variables_Register("in3", Variables_Type_uint32_t, &in3);
//	Variables_Register("in4", Variables_Type_uint32_t, &in4);
//	Variables_Register("pwm1", Variables_Type_float, &pwm1);
//	Variables_Register("pwm2", Variables_Type_float, &pwm2);
//
//	Timer_AddFunc(500, &t);
//	Cmd_StartListening();
//
//	for (;;) {
//		Message_MessageDef *Msg = Message_GetMessage();
//		if (!Msg) continue;    //没有新消息
//
//
//		switch (Msg->Type)
//		{
//		case Message_Type_CallFunc:
//			(*(void(*)())(Msg->lParam))();
//			break;
//
//		case Message_Type_ParsePending:
//			Cmd_ProcessMsgs((char*)(Msg->wParam), (char*)(Msg->lParam));
//
//			//case Message_Type_LED:
//			//	if ((bool)(Msg->lParam)) 
//			//		LED_Set(Msg->wParam);
//			//	else
//			//		LED_Reset(Msg->wParam);
//
//
//
//		default:
//			break;
//		}
//
//
//	}
//
//
//
//
//
//
//}
