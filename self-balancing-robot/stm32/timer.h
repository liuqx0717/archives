//定时器，可以注册一系列函数，分别以不同的间隔调用。
//向消息队列中插入一条消息，由主消息循环调用回调函数。


#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f4xx.h"

//向消息队列中插入一条消息，由主消息循环调用回调函数。
//返回序号，供清除回调函数的时候用。同一时刻最多有16个回调函数。失败返回-1
//当前 interval 配置的为 2ms ，每隔 interval_count * interval 的时间会调用一次相应函数。
uint32_t Timer_AddFunc(uint32_t interval_count, void(*CallBack)());


//清除回调函数，成功返回true，失败返回false
bool Timer_RemoveFunc(uint32_t id);


uint32_t Timer_GetTickCount();



#endif // !__TIMER_H
