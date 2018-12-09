//变量管理器
//通过命令来修改变量的值

#ifndef __VARIABLES_H
#define __VARIABLES_H


//最多注册多少个变量
#define VARIABLES_MAX_COUNT 64


#include "stm32f4xx.h"



enum Variables_Types {
	Variables_Type_uint32_t = 0,
	Variables_Type_float,

	__Variables_Type_Enum_End
};


//只读变量以"@"开头
//一定要传全局变量，不能传入局部变量
bool Variables_Register(const char *Name, Variables_Types Type, void *Address);

bool Variables_GetValueFromIndex(uint32_t index, char *Dest);


//获取变量的值，以字符串表示，写入Dest中。
//名称区分大小写，不会自动去除首尾的空白
//只读变量以"@"开头，查询的时候也要加上"@"
//如果没找到，返回false
bool Variables_GetValueFromName(const char *Name, char *Dest);



bool Variables_SetValueByIndex(uint32_t index, const char *Value);

//如果没找到，返回false
bool Variables_SetValueByName(const char *Name, const char *Value);


uint32_t Variables_GetVariablesCount();

//索引超出范围会返回NULL
const char *Variables_GetNameFromIndex(uint32_t index);




#endif // !__VARIABLES_H
