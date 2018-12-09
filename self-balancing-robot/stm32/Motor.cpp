#include "Motor.h"

#include "Ke_MotorControl.h"
#include "Ke_TIM3.h"

#include "math.h"



//in1=1,in2=0,pwm2  you
//in3 = 1, in4 = 0, pwm1  zuo

static float base = 0.55;


static bool Initialized = false;


void Motor_Init()
{

	if (!Initialized) {
		Initialized = true;

		Ke_TIM3_Init(3360 - 1, 0);        //pwm频率：25kHz    速度取值个数：3360
		Ke_MotorControl_Init();

	}


}


void Motor_SetLeftSpeed(float speed)
{
	Motor_Init();

	if (speed >= 0.0) {
		if (speed > 1) speed = 1;
		Ke_MotorControl_SetIN3();
		Ke_MotorControl_ResetIN4();
	}
	else {
		speed = -speed;
		if (speed > 1.0) speed = 1;
		Ke_MotorControl_ResetIN3();
		Ke_MotorControl_SetIN4();
	}

	speed = base + (1.0 - base)*speed;
	Ke_TIM3_Set1(speed);


}



void Motor_SetRightSpeed(float speed)
{
	Motor_Init();

	if (speed >= 0.0) {
		if (speed > 1) speed = 1;
		Ke_MotorControl_SetIN1();
		Ke_MotorControl_ResetIN2();
	}
	else {
		speed = -speed;
		if (speed > 1.0) speed = 1;
		Ke_MotorControl_ResetIN1();
		Ke_MotorControl_SetIN2();
	}

	speed = base + (1.0 - base)*speed;
	Ke_TIM3_Set2(speed);
}
