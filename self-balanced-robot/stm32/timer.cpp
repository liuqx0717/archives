//定时器，可以注册一系列函数，分别以不同的间隔调用
//向消息队列中插入一条消息，由主消息循环调用回调函数。

#include "timer.h"

#include "Message.h"

#include "Ke_SysTick.h"

//最多有多少个回调函数
#define MAXFUNC 16


//是否初始化了
static bool Initialized = false;

struct CallBackFuncs
{
	void(*CallBackFunc)();
	uint32_t TickCount;
	uint32_t Threshold;
};


//回调函数列表
static CallBackFuncs CallBackList[MAXFUNC];
static uint32_t CallBackListCurrentPos;



void Timer_KeCallBack()
{
	//不能在这个函数里直接调用回调列表中的函数。
	//如果这个函数处理的总时间超过SysTick中断周期，会导致SysTick中断“丢帧”，进而导致延时不准确以及Timer_GetTickCount()的值不可靠。
	//所以向消息队列中插入“调用”消息，由主消息循环调用，以尽快退出SysTick中断。


	for (uint32_t i = 0; i < CallBackListCurrentPos; i++) {
		if (CallBackList[i].CallBackFunc) {
			CallBackList[i].TickCount++;
			if (CallBackList[i].TickCount == CallBackList[i].Threshold) {
				CallBackList[i].TickCount = 0;
				Message_SendMessage(Message_Type_CallFunc, 0, (void *)(CallBackList[i].CallBackFunc));
			}
		}
	}
}

void Timer_Init()
{
	if (!Initialized) {
		Initialized = true;
		CallBackListCurrentPos = 0;
		for (uint32_t i = 0; i < MAXFUNC; i++) {
			//清空列表
			CallBackList[i].CallBackFunc = 0;
		}

		Ke_SysTick_Init(500, &Timer_KeCallBack);       //配置 interval 为 2ms
		Ke_SysTick_Enable();
	}
}


//返回序号，供清除回调函数的时候用。同一时刻最多有16个回调函数。失败返回-1
uint32_t Timer_AddFunc(uint32_t interval_count, void(*CallBack)())
{
	Timer_Init();

	if (CallBackListCurrentPos < MAXFUNC) {
		CallBackList[CallBackListCurrentPos].CallBackFunc = CallBack;
		CallBackList[CallBackListCurrentPos].Threshold = interval_count;
		CallBackList[CallBackListCurrentPos].TickCount = 0;
		CallBackListCurrentPos++;
		return CallBackListCurrentPos - 1;
	}
	else {
		return -1;
	}

}


//成功返回true，失败返回false
bool Timer_RemoveFunc(uint32_t id)
{

	if (id < CallBackListCurrentPos) {
		CallBackList[id].CallBackFunc = 0;
		return true;
	}
	else {
		return false;
	}
}


//经历了多少个interval
uint32_t Timer_GetTickCount()
{
	Timer_Init();

	return Ke_SysTick_GetTicks();
}
