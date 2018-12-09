#include "stdafx.h"


#ifndef _HOOKAPI_H_
#define _HOOKAPI_H_

#ifndef _WIN64

#include <Windows.h>

namespace lqx {

	PVOID HookFunction(PCHAR ModuleName, PCHAR FunctionName, PVOID pNewFunction);

	BOOL UnHookFunction(PCHAR ModuleName, PCHAR FunctionName, PVOID pProxyFunction);

	BOOL IsFuncHooked(PCHAR ModuleName, PCHAR FunctionName);

}

#endif

#endif