//命令解释器
//收到一组命令后会向消息队列中插入Message_Type_ParsePending消息，主消息循环收到此消息后应立刻调用Cmd_ProcessMsgs()

#include "Cmd.h"
#include "stm32f4xx.h"

#include "StringAlg.h"
#include "Message.h"
#include "Variables.h"

#include "Ke_bluetooth.h"
#include "Ke_CRC32.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static bool Initialized = false;

static bool Echo = true;

static char ReceiveBuffer[CMD_RECEIVEBUFFERSIZE];
static uint32_t ReceiveBufferPos = 0;

static char SendBuffer[CMD_SENDBUFFERSIZE];
static uint32_t SendBufferPos = 0;



//tmp：临时缓存一个(不是全部)var:name1=value1类型的字符串
void Cmd_SendAllVariables(char *tmp)
{
	//char s[256];

	uint32_t n = Variables_GetVariablesCount();
	for (uint32_t i = 0; i < n; i++) {
		//memcpy(s, tmp, 256);
		sprintf(tmp,
			"%s:%s=",
			Message_GetMessageNameFromType(Message_Type_Var),
			Variables_GetNameFromIndex(i)
		);
		//memcpy(s, tmp, 256);
		int len = strlen(tmp);                //"VAR:name1="这个字符串有多长
		Variables_GetValueFromIndex(i, tmp + len);
		//memcpy(s, tmp, 256);
		Cmd_AddSingleCmd(tmp);            //向发送缓存中添加一条命令
	}

	Cmd_Send();                     //发送上述缓存的命令
}



//处理成功返回true，处理失败返回false
//在主消息循环中调用这个函数
bool Cmd_ProcessSingleCmd(char *FullCmd)
{
	char *Parts[CMD_MAX_PARAM_COUNT + 1];    //Parts[0]：命令     Parts[i]：第i个参数(i>0)

	unsigned int n = StringAlg_Split(FullCmd, ":,", Parts, CMD_MAX_PARAM_COUNT + 1, false, '\0', '\0');

	//因为之前已经除去空字符串了，所以这里的 n 一定大于等于 1

	for (unsigned int i = 0; i < n; i++) {         //除去命令或者参数两遍的空格、跳格、回车符、换行符
		StringAlg_TrimA(Parts[i], " \t\r\n", StringAlg_TRIM_BOTH);
	}
	
	//switch语句中要用的变量
	char tmpstr[CMD_MAX_SENDVARCMD_LENGTH];               //保存一个var:name1=value1类型的字符串
	uint32_t tmpn;
	float tmpf;


	switch (Message_GetMessageTypeFromName(Parts[0]))
	{
	case Message_Type_Echo:     //echo      echo:on     echo:off
		if (n == 1) {
			if (Echo) {
				Cmd_AddSingleCmd("echo on.");
				Cmd_Send();
				return true;
			}
			else if(!Echo){
				Cmd_AddSingleCmd("echo off.");
				Cmd_Send();
				return true;
			}
		}
		else if (n == 2) {
			if (StringAlg_CmpA(Parts[1], "on")) {
				Echo = true;
				return true;
			}
			else if (StringAlg_CmpA(Parts[1], "off")) {
				Echo = false;
				return true;
			}
		}
		return false;
		break;

	case Message_Type_Var:          //接收：var      var:name1,name2,...      var:name1=value,name2=value2,...       只读变量以@开头
		                            //发送：var:name1=value1;var:name2=value2;...
		if (n == 1) {
			Cmd_SendAllVariables(tmpstr);    //发送所有变量
			return true;
		}
		else {
			char *substr[2];              //以"="分割。（只以第一个"="分割）
			unsigned int nsubstr;
			for (int i = 1; i < n; i++) {
				nsubstr = StringAlg_Split(Parts[i], "=", substr, 2, false, '\0', '\0');
				if (nsubstr == 1) {                         //没有"="，则返回相应的变量的值
					sprintf(tmpstr, "%s:%s=", Message_GetMessageNameFromType(Message_Type_Var), Parts[i]);
					int len = strlen(tmpstr);                //"VAR:name1="这个字符串有多长
					if (Variables_GetValueFromName(Parts[i], tmpstr + len)) {   
						//如果找到相应变量，就向发送缓存中添加一条命令
						Cmd_AddSingleCmd(tmpstr);
					}
				}
				else {                                     //有"="，则设置相应变量的值
					Variables_SetValueByName(substr[0], substr[1]);
				}

			}
			Cmd_Send();                   //发送上述缓存的命令
			return true;
		}
		return false;
		break;


	case Message_Type_Delay:             //delay:<延迟几个interval>
		if (n == 2) {
			Message_SendMessage(Message_Type_Delay, atoi(Parts[1]), 0);
			return true;
		}

		return false;
		break;

	case Message_Type_LED:              //led:<编号>,on       led:<编号>,off
		if (n == 3) {
			if (StringAlg_CmpA(Parts[2], "on")) {
				Message_SendMessage(Message_Type_LED, atoi(Parts[1]), (void *)true);
				return true;
			}
			else if (StringAlg_CmpA(Parts[2], "off")) {
				Message_SendMessage(Message_Type_LED, atoi(Parts[1]), (void *)false);
				return true;
			}
		}

		return false;
		break;

	case Message_Type_QueryMessageQueue:    //没有参数
		if (n == 1) {
			tmpn = Message_QueryDelayBuffer();
			sprintf(tmpstr, "%u command(s) remaining.", tmpn);
			Cmd_AddSingleCmd(tmpstr);
			Cmd_Send();
			return true;
		}

		return false;
		break;

	case Message_Type_Clear:                //没有参数
		if (n == 1) {
			Message_ClearDelayBuffer();
			return true;
		}

		return false;
		break;

	case Message_Type_Left:
		tmpf = atoff(Parts[1]);
		//Message_SendMessage()

		break;


	case Message_Type_Right:


		break;



	default:
		break;
	}

	return false;

}


//处理一组命令，并向电脑端发送命令解析情况（成功解析多少条）
void Cmd_ProcessMsgs(char *MsgStr, char *CRC32Str)
{
	char *Cmds[CMD_MAXCOUNT];
	unsigned int n = StringAlg_Split(MsgStr, ";", Cmds, CMD_MAXCOUNT, true, '\0', '\0');

	uint32_t nSucceeded = 0;

	for (unsigned int i = 0; i < n; i++) {
		if (Cmd_ProcessSingleCmd(Cmds[i])) {
			nSucceeded++;
		}
	}

	if (Echo) {         //回显开启的话
							//PARSED:CRC32, nSucceeded, nTotal
		char cmd[32];

		sprintf(cmd,
			"%s:%s,%u,%u",
			Message_GetMessageNameFromType(Message_Type_Parsed), 
			CRC32Str, 
			nSucceeded,
			n
		);

		Cmd_AddSingleCmd(cmd);
		Cmd_Send();
	}
}



void Cmd_BluetoothCallback(const void *data, uint32_t size_in_bytes)
{
	//命令格式： abc:p1,p2,...\0<长度为8位的CRC32字符串>\0\0

	for (uint32_t i = 0; i < size_in_bytes; i++) {

		char c = ((char*)data)[i];
		ReceiveBuffer[ReceiveBufferPos] = c;

		if (c != '\0') {
			ReceiveBufferPos++;
			continue;
		}
		else {
			if (ReceiveBufferPos == 0) continue;           //刚开始就收到'\0'，则忽略

			if (ReceiveBuffer[ReceiveBufferPos - 1] == '\0') {  //收到连续的两个'\0'，则结束
				if (ReceiveBufferPos < 11) {               //最短的消息加上crc32校验的长度为11
					ReceiveBufferPos = 0;
					continue;
				}

				char *MsgStr = ReceiveBuffer;                                //消息内容
				char *CRC32Str = ReceiveBuffer + ReceiveBufferPos - 9;  //消息校验

				uint32_t CRC32 = Ke_CRC32_Calc(MsgStr, ReceiveBufferPos - 9);  //消息内容结束字符'\0'也计算在内

				char tmpCRC32Str[16];
				char tmpCRC32Str2[16];
				utoa(CRC32, tmpCRC32Str, 16);
				StringAlg_CharFillStrLeftA(tmpCRC32Str2, tmpCRC32Str, '0', 8);     //CRC32字符串前面补0

				if (StringAlg_CmpA(CRC32Str, tmpCRC32Str2)) {                   //如果CRC32校验值匹配
					//由主消息循环批量处理，以尽快退出中断
					Message_SendMessage(Message_Type_ParsePending, (uint32_t)MsgStr, tmpCRC32Str2);   
				}

				ReceiveBufferPos = 0;
				continue;


			}
		}

		ReceiveBufferPos++;
		if (ReceiveBufferPos == CMD_RECEIVEBUFFERSIZE)
			ReceiveBufferPos = 0;

	}
}


void Cmd_Init()
{
	if (!Initialized) {
		Initialized = true;

		Ke_Bluetooth_Init(115200, &Cmd_BluetoothCallback);
		Ke_CRC32_Init();
	}
}


void Cmd_StartListening()
{
	Cmd_Init();
}

//向发送消息的缓存中添加一条命令（无需以";"结尾，会自动添加）
bool Cmd_AddSingleCmd(const char *FullCmd)
{
	int i;
	for (i = 0; FullCmd[i]; i++) {
		if (SendBufferPos + i > CMD_SENDBUFFERSIZE - 12) {    //消息过长
			return false;
		}
		SendBuffer[SendBufferPos + i] = FullCmd[i];
	}
	SendBuffer[SendBufferPos + i] = ';';
	SendBufferPos += i + 1;

	return true;

}





//将发送消息缓存中的消息发送出去
void Cmd_Send()
{
	Cmd_Init();

	SendBuffer[SendBufferPos] = '\0';                             //写入结束符
	SendBufferPos++;
	uint32_t CRC32 = Ke_CRC32_Calc(SendBuffer, SendBufferPos);    //字符串结束标志'\0'也计算在内

	char tmpCRC32Str[16];
	char tmpCRC32Str2[16];
	utoa(CRC32, tmpCRC32Str, 16);
	StringAlg_CharFillStrLeftA(tmpCRC32Str2, tmpCRC32Str, '0', 8);  //左边补0，填充为8个字符

	for (int j = 0; j < 8; j++) {
		SendBuffer[SendBufferPos] = tmpCRC32Str2[j];
		SendBufferPos++;
	}

	SendBuffer[SendBufferPos] = '\0';                  //补最后的两个'\0'
	SendBufferPos++;
	SendBuffer[SendBufferPos] = '\0';
	SendBufferPos++;

	Ke_Bluetooth_Send(SendBuffer, SendBufferPos);       //发送

	SendBufferPos = 0;
}
