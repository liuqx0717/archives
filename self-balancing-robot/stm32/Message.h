//消息队列，可以实现延迟的功能


#ifndef __MESSAGE_H
#define __MESSAGE_H

#include "stm32f4xx.h"


//主消息队列的缓存长度
#define MESSAGE_MAINBUFFERSIZE 256


//延迟消息队列的缓存长度
#define MESSAGE_DELAYBUFFERSIZE 512


enum Message_Types {
	//调用一个函数（由定时器发出的消息）
    //wParam: 无用               lParam : 函数指针
	Message_Type_CallFunc = 1,      

	//回显查询及设置
	//在Cmd.cpp中处理了，主消息循环不会收到此消息。
	Message_Type_Echo,              

	//变量查询及设置
	//在Cmd.cpp中处理了，主消息循环不会收到此消息。
	Message_Type_Var,               

	//处理收到的命令。主消息循环收到此消息后应立刻调用Cmd_ProcessMsgs()
	//wParam: char *MsgStr       lParam:char *CRC32Str
	Message_Type_ParsePending,   

	//命令解析情况反馈
	//在Cmd.cpp中处理了，主消息循环不会收到此消息。
	Message_Type_Parsed,            

	//延迟命令
	//在Message.cpp中处理了，主消息循环不会收到此消息。
	Message_Type_Delay, 

	//控制LED
	//wParam: uint32_t id                 lParam: bool SwitchOn
	Message_Type_LED,

	//清空延迟消息队列
	//在Cmd.cpp中处理了，主消息循环不会收到此消息。
	Message_Type_Clear,

	//查询延迟消息队列中剩余多少条消息
	//在Cmd.cpp中处理了，主消息循环不会收到此消息。
	Message_Type_QueryMessageQueue,

	Message_Type_Left,

	Message_Type_Right,




	__Message_Type_Enum_End
};


#ifdef __MESSAGE_C

//消息的字符串名称，数组以 0 结束。
//构造命令字符串时不允许直接在代码中写命令名称，而应通过Message_GetMessageNameFromType()得到命令名称，便于管理。
//"!"开头的是内部命令，不允许在电脑和单片机之间发送此类命令。
const char *_Message_MsgNames[] = {
	"!NoMatch",
	"!CallFunc",
	"ECHO",
	"VAR",
	"!ParsePending",
	"PARSED",
	"DELAY",
	"LED",
	"CLEAR",
	"QUERY",
	"LEFT",
	"RIGHT",

	0
};


//受Delay命令影响的消息，以 0 结束。
//受Delay影响的命令只能从发送到主消息循环的命令中选，不能选诸如 Message_Type_Echo 等等在Cmd.c中处理的命令。
uint32_t _Message_DelayEnabledMessages[] = {
	Message_Type_Delay,                        //必须有这条消息，否则延迟系统无法正常工作
	Message_Type_LED,
	Message_Type_Left,
	Message_Type_Right,

	0
};





#endif // __MESSAGE_C






struct Message_MessageDef
{
	uint32_t Type;
	uint32_t wParam;
	void *lParam;
};


//若当前没有消息，就返回NULL
Message_MessageDef *Message_GetMessage();

//发消息
void Message_SendMessage(uint32_t Type, uint32_t wParam, void *lParam);

//解析字符串，若没有找到对应消息类型，则返回 0
uint32_t Message_GetMessageTypeFromName(const char *Str);


//Type序号超出范围，会返回NULL。
const char* Message_GetMessageNameFromType(uint32_t Type);


//清空延迟消息队列
void Message_ClearDelayBuffer();

//查询延迟消息队列中还有多少待处理的消息
uint32_t Message_QueryDelayBuffer();



#endif // !__MESSAGE_H
