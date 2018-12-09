//命令解释器
//收到一组命令后会向消息队列中插入Message_Type_ParsePending消息，主消息循环收到此消息后应立刻调用Cmd_ProcessMsgs()

#ifndef __CMD_H
#define __CMD_H


//接收的一组命令中最多有几条命令
#define CMD_MAX_CMD_COUNT 512


//接收的单条命令最多有多少参数
#define CMD_MAX_PARAM_COUNT 64


//接收的一组命令的最大长度
#define CMD_RECEIVEBUFFERSIZE 8192




//发送的一组命令的最大长度
#define CMD_SENDBUFFERSIZE 2048

//发送一条var:name1=value1这种类型的消息的最大长度
#define CMD_MAX_SENDVARCMD_LENGTH 256




//主消息循环中收到PARSE命令后调用这个函数处理接收到的消息，而不是在中断调用这个函数
//只能在主消息循环中自动调用这个函数，不能手动直接调用！
void Cmd_ProcessMsgs(char *MsgStr, char *CRC32Str);


void Cmd_StartListening();


//向发送消息的缓存中添加一条命令（无需以";"结尾，会自动添加）
bool Cmd_AddSingleCmd(const char *FullCmd);


//将发送消息缓存中的消息发送出去
void Cmd_Send();


#endif // !__CMD_H
