#include "Encoder.h"

#include "Ke_TIM2.h"
#include "Ke_TIM5.h"





static bool Initialized = false;

static int32_t FormerLeftPosition = 0;
static int32_t FormerRightPosition = 0;
static int32_t FormerLeftSpeed = 0;
static int32_t FormerRightSpeed = 0;


static int32_t LeftSpeed = 0;
static int32_t RightSpeed = 0;
static int32_t LeftAcc = 0;
static int32_t RightAcc = 0;




void Encoder_Init()
{

	if (!Initialized) {
		Initialized = true;

		Ke_TIM2_Init();
		Ke_TIM5_Init();

	}



}



int32_t Encoder_GetLeftPosition()
{
	Encoder_Init();

	return (int32_t)Ke_TIM2_GetCount();

}


int32_t Encoder_GetRightPosition()
{
	Encoder_Init();

	return (int32_t)Ke_TIM5_GetCount();

}



int32_t Encoder_GetLeftSpeed()
{
	return LeftSpeed;
}

int32_t Encoder_GetRightSpeed()
{
	return RightSpeed;
}

int32_t Encoder_GetLeftAcc()
{
	return LeftAcc;
}

int32_t Encoder_GetRightAcc()
{
	return RightAcc;
}





//每隔一定的时间调用
void Encoder_Update()
{
	Encoder_Init();
	
	int32_t left = (int32_t)Ke_TIM2_GetCount();
	int32_t right = (int32_t)Ke_TIM5_GetCount();


	LeftSpeed = left - FormerLeftPosition;
	RightSpeed = right - FormerRightPosition;
	LeftAcc = LeftSpeed - FormerLeftSpeed;
	RightAcc = RightSpeed - FormerRightSpeed;


	FormerLeftPosition = left;
	FormerRightPosition = right;
	FormerLeftSpeed = LeftSpeed;
	FormerRightSpeed = RightSpeed;


	


}
