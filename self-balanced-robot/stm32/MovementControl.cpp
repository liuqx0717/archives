#include "MovementControl.h"


#include "PID.hpp"
#include "timer.h"
#include "Encoder.h"
#include "Motor.h"
#include "Variables.h"
#include "AngleCalc.h"

#include <cmath>


#define MovementControl_MovingAverageFilterOrder1 5
static float buffer1[MovementControl_MovingAverageFilterOrder1];
static MovingAverageFilter<float> filter1;

#define MovementControl_MovingAverageFilterOrder2 5
static float buffer2[MovementControl_MovingAverageFilterOrder2];
static MovingAverageFilter<float> filter2;

#define MovementControl_MovingAverageFilterOrder3 5
static float buffer3[MovementControl_MovingAverageFilterOrder3];
static MovingAverageFilter<float> filter3;

#define MovementControl_MovingAverageFilterOrder4 5
static float buffer4[MovementControl_MovingAverageFilterOrder4];
static MovingAverageFilter<float> filter4;

#define MovementControl_MovingAverageFilterOrder5 5
static float buffer5[MovementControl_MovingAverageFilterOrder5];
static MovingAverageFilter<float> filter5;

static bool Initialized = false;


static float CurrentSpeed = 0;
static float MaxSpeed = 10;
static float k1 = 0;            //TargetAcc=k3*(tan(CurrentAngle)+k1*CurrentAngularSpeed)   k1正
static float k2 = 0;            //速度控制（正）
static float k3 = 0;            //
static float k4 = 0;            //DeltaAcc的系数，以便转化为DeltaPWM
static float D = 0;             //这个常数乘上CurrentSpeed之后为阻力引起的加速度

static float AngleThreshold = 0;

static float TargeSpeed = 0;





void MovementControl_Update()
{
	static float LeftPWM = 0;
	static float RightPWM = 0;

	Encoder_Update();
	static float FormerAngle;
	float CurrentAngle = AngleCalc_GetAngle();
	float CurrentAngularSpeed = filter1.update(CurrentAngle - FormerAngle);
	FormerAngle = CurrentAngle;
	float t = Encoder_GetLeftPosition();
	//float CurrentLeftSpeed = filter2.update(Encoder_GetLeftSpeed() / MaxSpeed);
	//float CurrentRightSpeed = filter3.update(Encoder_GetRightSpeed() / MaxSpeed);
	float CurrentLeftSpeed = filter2.update(Encoder_GetLeftSpeed() / 50.0);
	float CurrentRightSpeed = filter3.update(Encoder_GetRightSpeed() / 50.0);
	CurrentSpeed = (CurrentLeftSpeed + CurrentRightSpeed) / 2.0;
	float CurrentLeftAcc = filter4.update(Encoder_GetLeftAcc() / 50.0);
	float CurrentRightAcc = filter5.update(Encoder_GetRightAcc() / 50.0);
	float CurrentAcc = (CurrentLeftAcc + CurrentRightAcc) / 2.0;


	if (fabs(CurrentAngle) < AngleThreshold) {
		CurrentAngle -= k2*(CurrentSpeed - TargeSpeed);
	}

	float TargetAcc = k3*(tanf(CurrentAngle) + k1*CurrentAngularSpeed);

	float DeltaPWM = (TargetAcc - CurrentAcc)*k4;

	DeltaPWM += D*CurrentSpeed;

	LeftPWM += DeltaPWM;
	RightPWM += DeltaPWM;
	if (LeftPWM > 1)LeftPWM = 1;
	if (LeftPWM < -1)LeftPWM = -1;
	if (RightPWM > 1)RightPWM = 1;
	if (RightPWM < -1)RightPWM = -1;


	//LeftSpeed = CurrentSpeed + DeltaSpeed;
	//RightSpeed = CurrentSpeed + DeltaSpeed;

	


	Motor_SetLeftSpeed(LeftPWM);
	Motor_SetRightSpeed(RightPWM);
	

}




void MovementControl_Init()
{
	if (!Initialized) {
		Initialized = true;

		AngleCalc_Init(MOVEMENTCONTROL_INTERVAL_IN_SECONDS);

		Variables_Register("@CurrentSpeed", Variables_Type_float, &CurrentSpeed);
		Variables_Register("MaxSpeed", Variables_Type_float, &MaxSpeed);
		Variables_Register("k1", Variables_Type_float, &k1);
		Variables_Register("k2", Variables_Type_float, &k2);
		Variables_Register("k3", Variables_Type_float, &k3);
		Variables_Register("k4", Variables_Type_float, &k4);
		Variables_Register("D", Variables_Type_float, &D);
		Variables_Register("AngleThreshold", Variables_Type_float, &AngleThreshold);



		filter1.init(MovementControl_MovingAverageFilterOrder1, buffer1);
		filter2.init(MovementControl_MovingAverageFilterOrder2, buffer2);
		filter3.init(MovementControl_MovingAverageFilterOrder3, buffer3);
		filter4.init(MovementControl_MovingAverageFilterOrder4, buffer4);
		filter5.init(MovementControl_MovingAverageFilterOrder5, buffer5);


		Timer_AddFunc(MOVEMENTCONTROL_INTERVAL_COUNT, &MovementControl_Update);

	}


}


































//#include "MovementControl.h"
//
//
//#include "PID.hpp"
//#include "timer.h"
//#include "Encoder.h"
//#include "Motor.h"
//#include "Variables.h"
//#include "AngleCalc.h"
//
//
//
//static bool Initialized = false;
//
//
//
//
//static bool PIDErrectStarted = false;
//static PID<float> PIDErrect;
//static float CurrentAngular = 0;
//static float FormerAngular = 0;
//
//
//static bool PIDErrectInnerStarted = false;
//static PID<float> PIDErrectInner;
//static float CurrentAngularSpeed;
//
//static bool PIDSpeedStarted = false;
//static PID<float> PIDSpeed;
//static float LeftSpeed;
//static float RightSpeed;
//static float Speed;
//
//
//
//
//void MovementControl_Update()
//{
//	float LeftSPeed = 0;                  //最终输出的两个速度
//	float RightSPeed = 0;
//
//	float PIDResult;     //临时保存PID返回值
//
//
//
//
//	//更新当前测量值
//	Encoder_Update();
//	FormerAngular = CurrentAngular;
//	CurrentAngular = AngleCalc_GetAngle();
//	CurrentAngularSpeed = CurrentAngular - FormerAngular;
//	LeftSpeed = Encoder_GetLeftSpeed();
//	LeftSpeed = Encoder_GetRightSpeed();
//	Speed = (LeftSpeed + LeftSpeed) / 2;
//	CurrentAngularSpeed = AngleCalc_GetDeltaAngleFromGyroscope();
//
//
//
//
//
//
//	PIDSpeed.SetTarget(0);
//	PIDErrect.SetTarget(0);
//	PIDErrectInner.SetTarget(0);
//
//
//	if (PIDSpeedStarted) {
//		PIDResult = PIDSpeed.Update();
//		//PIDErrect.IncreaseTarget(PIDResult);
//		LeftSPeed += PIDResult;
//		RightSPeed += PIDResult;
//
//	}
//
//
//	if (PIDErrectStarted) {
//		PIDResult = PIDErrect.Update();
//		PIDErrectInner.IncreaseTarget(PIDResult);
//	}
//
//
//	if (PIDErrectInnerStarted) {
//		PIDResult = PIDErrectInner.Update();
//		LeftSPeed += PIDResult;
//		RightSPeed += PIDResult;
//
//	}
//
//
//
//
//
//	Motor_SetLeftSpeed(LeftSPeed);
//	Motor_SetRightSpeed(RightSPeed);
//
//
//}
//
//
//
//
//void MovementControl_Init()
//{
//	if (!Initialized) {
//		Initialized = true;
//
//		AngleCalc_Init(MOVEMENTCONTROL_INTERVAL_IN_SECONDS);
//
//		PIDErrect.init(0, 0, 0, &CurrentAngular, 0, 0);
//		Variables_Register("PIDErrect_En", Variables_Type_uint32_t, &PIDErrectStarted);
//		Variables_Register("PIDErrect_Kp", Variables_Type_float, &PIDErrect._Kp);
//		Variables_Register("PIDErrect_Ki", Variables_Type_float, &PIDErrect._Ki);
//		Variables_Register("PIDErrect_Kd", Variables_Type_float, &PIDErrect._Kd);
//
//		PIDErrectInner.init(0, 0, 0, &CurrentAngularSpeed, 0, 0);
//		Variables_Register("PIDInner_En", Variables_Type_uint32_t, &PIDErrectInnerStarted);
//		Variables_Register("PIDInner_Kp", Variables_Type_float, &PIDErrectInner._Kp);
//		Variables_Register("PIDInner_Ki", Variables_Type_float, &PIDErrectInner._Ki);
//		Variables_Register("PIDInner_Kd", Variables_Type_float, &PIDErrectInner._Kd);
//
//
//
//		PIDSpeed.init(0, 0, 0, &Speed, 0, 0.5);
//		Variables_Register("PIDSpeed_En", Variables_Type_uint32_t, &PIDSpeedStarted);
//		Variables_Register("PIDSpeed_Kp", Variables_Type_float, &PIDSpeed._Kp);
//		Variables_Register("PIDSpeed_Ki", Variables_Type_float, &PIDSpeed._Ki);
//		Variables_Register("PIDSpeed_Kd", Variables_Type_float, &PIDSpeed._Kd);
//		Variables_Register("PIDSpeed_SumMax", Variables_Type_float, &PIDSpeed._SumMax);
//
//
//		Timer_AddFunc(MOVEMENTCONTROL_INTERVAL_COUNT, &MovementControl_Update);
//
//	}
//
//
//}
//
//
//
//void MovementControl_StartPIDErrect()
//{
//
//	MovementControl_Init();
//	PIDErrectStarted = true;
//
//
//}
//
//
//
//void MovementControl_StopPIDErrect()
//{
//	PIDErrectStarted = false;
//
//}
//
//
//void MovementControl_StartPIDSpeed()
//{
//
//	MovementControl_Init();
//	PIDSpeedStarted = true;
//
//
//}
//
//void MovementControl_StopPIDSpeed()
//{
//
//	PIDSpeedStarted = false;
//
//
//}
//
//void MovementControl_StartPIDInnerErrect()
//{
//
//	MovementControl_Init();
//	PIDErrectInnerStarted = true;
//
//
//}
//
//
//
//void MovementControl_StopPIDInnerErrect()
//{
//	PIDErrectInnerStarted = false;
//
//}
//
