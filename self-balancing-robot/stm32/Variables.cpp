//变量管理器
//通过命令来修改变量的值

#include "Variables.h"
#include "StringAlg.h"

#include "stm32f4xx.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>            //sprintf不能转换小数

struct VariableTypeDef
{
	const char *name;
	Variables_Types format;    
	void *address;
};


static VariableTypeDef Buffer[VARIABLES_MAX_COUNT];
static uint32_t BufferPos = 0;




bool Variables_GetValueFromIndex(uint32_t index, char *Dest)
{
	if (index < BufferPos) {
		VariableTypeDef var = Buffer[index];
		switch (var.format)
		{
		case Variables_Type_uint32_t:
			utoa(*((uint32_t*)var.address), Dest, 10);
			break;

		case Variables_Type_float:
			StringAlg_ftoa(*((float*)var.address), Dest, 6);
			
			break;

		default:
			strcpy(Dest, "<UnknownType>");
			break;
		}
		return true;
	}
	else {
		return false;
	}
}


bool Variables_SetValueByIndex(uint32_t index, const char *Value)
{
	uint32_t u;
	float f;

	if (index < BufferPos) {
		VariableTypeDef var = Buffer[index];
		switch (var.format)
		{
		case Variables_Type_uint32_t:
			u = atol(Value);
			*((uint32_t*)var.address) = u;
			break;

		case Variables_Type_float:
			f = atof(Value);
			*((float*)var.address) = f;
			break;

		default:
			break;
		}
		return true;

		

	}
	else {
		return false;
	}
}



//只读变量以"@"开头
//一定要传全局变量，不能传入局部变量
bool Variables_Register(const char *Name, Variables_Types Type, void *Address)
{
	if (BufferPos < VARIABLES_MAX_COUNT) {
		Buffer[BufferPos].name = Name;
		Buffer[BufferPos].format = Type;
		Buffer[BufferPos].address = Address;
		BufferPos++;
		return true;
	}
	else {
		return false;
	}
}



//获取变量的值，以字符串表示，写入Dest中。
//名称区分大小写，不会自动去除首尾的空白
//只读变量以"@"开头，查询的时候也要加上"@"
//如果没找到，返回false
bool Variables_GetValueFromName(const char *Name, char *Dest)
{
	for (int i = 0; i < BufferPos; i++) {
		if (!strcmp(Buffer[i].name, Name)) {      //如果名称一致
			return Variables_GetValueFromIndex(i, Dest);
		}
	}

	return false;

	
}



//如果没找到，返回false
bool Variables_SetValueByName(const char *Name, const char *Value)
{
	for (int i = 0; i < BufferPos; i++) {
		if (!strcmp(Buffer[i].name, Name)) {      //如果名称一致
			return Variables_SetValueByIndex(i, Value);
		}
	}

	return false;
}

uint32_t Variables_GetVariablesCount()
{
	return BufferPos;
}

//索引超出范围会返回NULL
const char *Variables_GetNameFromIndex(uint32_t index)
{
	if (index < BufferPos) {
		return Buffer[index].name;
	}
	else {
		return NULL;
	}
}
