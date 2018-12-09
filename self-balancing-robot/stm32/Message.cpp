//消息队列，可以实现延迟的功能


#define _C
#include "Message.h"


#include "StringAlg.h"
#include "timer.h"


static bool Initialized = false;


static Message_MessageDef MainBuffer[MESSAGE_MAINBUFFERSIZE];
static uint32_t MainBufferCurrentPos = 0;   //现在该处理的消息的位置，处理完之后将其加 1
static uint32_t MainBufferEndPos = 0;       //最后一条消息的下一条消息处


static Message_MessageDef DelayBuffer[MESSAGE_DELAYBUFFERSIZE];
static uint32_t DelayBufferCurrentPos = 0;   //现在该处理的消息的位置，处理完之后将其加 1
static uint32_t DelayBufferEndPos = 0;       //最后一条消息的下一条消息处
static uint32_t DelayCount = 0;              //还需过多久才开始继续处理延迟消息序列



static uint32_t TypeCount;              //总共有多少种消息类型（保存MsgNames数组的长度）



//每10ms调用一次
void Message_CheckDelayBuffer()
{

	if (DelayCount) {     //如果计数器没有到0，说明延迟没有结束，先退出。
		DelayCount--;
		return;
	}

	//因为是环形缓冲区，所以不能直接比较 DelayBufferCurrentPos 与 DelayBufferEndPos 的大小
	while (DelayBufferCurrentPos != DelayBufferEndPos) {


		Message_MessageDef *CurrentMsg = DelayBuffer + DelayBufferCurrentPos;
		DelayBufferCurrentPos++;
		if (DelayBufferCurrentPos == MESSAGE_DELAYBUFFERSIZE) {
			DelayBufferCurrentPos = 0;
		}


		// Message_Type_Delay：   延迟，以0.01s为单位    wParam : n      lParam : 无用
		if (CurrentMsg->Type == Message_Type_Delay) {

			//不能延迟0ms，至少延迟1个interval（因为这里直接return了，下一个命令起码要过interval）
			//所以 Delay:0 相当于 Delay:1
			if (CurrentMsg->wParam == 0) {
				//如果命令为 Delay:0
				return;
			}
			else {
				DelayCount += CurrentMsg->wParam - 1;              //增加延迟计数器
				return;
			}
		}
		else {
			MainBuffer[MainBufferEndPos].Type = CurrentMsg->Type;      //写入主消息序列
			MainBuffer[MainBufferEndPos].wParam = CurrentMsg->wParam;
			MainBuffer[MainBufferEndPos].lParam = CurrentMsg->lParam;

			MainBufferEndPos++;
			if (MainBufferEndPos == MESSAGE_MAINBUFFERSIZE)
				MainBufferEndPos = 0;
		}


	}

}




void Message_Init()
{
	if (!Initialized) {
		Initialized = true;
		for (TypeCount = 0; MsgNames[TypeCount]; TypeCount++);

		//每10ms调用一次Message_CheckDelayBuffer()
		Timer_AddFunc(5, &Message_CheckDelayBuffer);
	}
}


//若当前没有消息，就返回NULL
Message_MessageDef *Message_GetMessage()
{
	if (MainBufferEndPos == MainBufferCurrentPos) return 0;

	Message_MessageDef *ret = MainBuffer + MainBufferCurrentPos;

	MainBufferCurrentPos++;
	if (MainBufferCurrentPos == MESSAGE_MAINBUFFERSIZE)
		MainBufferCurrentPos = 0;

	return ret;

	
}


void Message_SendMessage(uint32_t Type, uint32_t wParam, void *lParam)
{
	for (int i = 0; DelayEnabledMessages[i]; i++) {

		//如果是受Delay命令影响的命令，写入延迟消息序列
		if (Type == DelayEnabledMessages[i]) {       
			Message_Init();
			DelayBuffer[DelayBufferEndPos].Type = Type;
			DelayBuffer[DelayBufferEndPos].wParam = wParam;
			DelayBuffer[DelayBufferEndPos].lParam = lParam;

			DelayBufferEndPos++;
			if (DelayBufferEndPos == MESSAGE_DELAYBUFFERSIZE)
				DelayBufferEndPos = 0;

			return;

		}
	}


	//不受Delay影响的命令，直接写入主消息序列
	MainBuffer[MainBufferEndPos].Type = Type;
	MainBuffer[MainBufferEndPos].wParam = wParam;
	MainBuffer[MainBufferEndPos].lParam = lParam;

	MainBufferEndPos++;
	if (MainBufferEndPos == MESSAGE_MAINBUFFERSIZE)
		MainBufferEndPos = 0;
}


uint32_t Message_GetMessageTypeFromName(const char *Str)
{
	for (uint32_t i = 0; MsgNames[i]; i++) {
		if (StringAlg_CmpA(MsgNames[i], Str)) {
			return i;
		}
	}

	//如果没找到
	return 0;
}


//Type序号超出范围，会返回NULL。
const char* Message_GetMessageNameFromType(uint32_t Type)
{
	Message_Init();   //初始化TypeCount的值

	//参数检查
	if (Type < TypeCount) {
		return MsgNames[Type];
	}
	else {
		return 0;
	}
}



//清空延迟消息队列
void Message_ClearDelayBuffer()
{
	DelayBufferCurrentPos =
		DelayBufferEndPos =
		DelayCount = 0;


}


//查询延迟消息队列中还有多少待处理的消息
uint32_t Message_QueryDelayBuffer()
{

	//因为是环形缓冲区，所以要分情况讨论
	if (DelayBufferCurrentPos <= DelayBufferEndPos) {
		return DelayBufferEndPos - DelayBufferCurrentPos;
	}
	else {
		return MESSAGE_DELAYBUFFERSIZE - (DelayBufferCurrentPos - DelayBufferEndPos);
	}
}
