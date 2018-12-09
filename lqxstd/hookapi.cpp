#include "stdafx.h"

#ifndef _WIN64

#include "hookapi.h"
#include "LDasm.h"

namespace lqx {

	PVOID HookFunction(PCHAR ModuleName, PCHAR FunctionName, PVOID pNewFunction)
	{

		UCHAR JumpCode[6] = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 };     //push xxxxxxxx ret
		UCHAR JumpBackCode[6] = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 }; //push xxxxxxxx ret

		PVOID pSourceFunction = GetProcAddress(GetModuleHandleA(ModuleName), FunctionName);
		if (!pSourceFunction)return NULL;

		*(ULONG *)((ULONG)JumpCode + 1) = (ULONG)pNewFunction;


		PVOID pProxyFunction = 0;
		PUCHAR pOpCode;
		ULONG BackupLength = 0;


		while (BackupLength < 6)
		{
			BackupLength += SizeOfCode((PVOID)((ULONG)pSourceFunction + BackupLength), &pOpCode);
		}


		pProxyFunction = VirtualAlloc(NULL, BackupLength + 6, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (!pProxyFunction)return NULL;

		*(ULONG *)((ULONG)JumpBackCode + 1) = (ULONG)pSourceFunction + BackupLength;

		RtlCopyMemory(pProxyFunction, pSourceFunction, BackupLength);
		RtlCopyMemory((PVOID)((ULONG)pProxyFunction + BackupLength), JumpBackCode, 6);

		FlushInstructionCache((HANDLE)-1, pProxyFunction, BackupLength + 6);

		DWORD OldProtect = 0;
		VirtualProtect(pSourceFunction, 6, PAGE_EXECUTE_READWRITE, &OldProtect);

		RtlCopyMemory(pSourceFunction, JumpCode, 6);

		VirtualProtect(pSourceFunction, 6, OldProtect, &OldProtect);

		FlushInstructionCache((HANDLE)-1, pSourceFunction, 6);

		return pProxyFunction;


	}




	BOOL UnHookFunction(PCHAR ModuleName, PCHAR FunctionName, PVOID pProxyFunction)
	{

		PVOID pSourceFunction = GetProcAddress(GetModuleHandleA(ModuleName), FunctionName);
		if (!pSourceFunction)return FALSE;

		DWORD OldProtect = 0;
		VirtualProtect(pSourceFunction, 6, PAGE_EXECUTE_READWRITE, &OldProtect);

		RtlCopyMemory(pSourceFunction, pProxyFunction, 6);

		VirtualProtect(pSourceFunction, 6, OldProtect, &OldProtect);

		FlushInstructionCache((HANDLE)-1, pSourceFunction, 6);

		BOOL res = VirtualFree(pProxyFunction, NULL, MEM_RELEASE);
		if (!res)return FALSE;

		return TRUE;

	}




	BOOL IsFuncHooked(PCHAR ModuleName, PCHAR FunctionName)
	{
		PVOID pFunction = GetProcAddress(GetModuleHandleA(ModuleName), FunctionName);

		if (!pFunction)return FALSE;

		DWORD OldProtect = 0;
		VirtualProtect(pFunction, 6, PAGE_EXECUTE_READWRITE, &OldProtect);

		UCHAR chas = *(UCHAR *)((ULONG)pFunction + 5);

		if (((*(UCHAR *)pFunction == 0x68) && (*(UCHAR *)((ULONG)pFunction + 5) == 0xC3)) || (*(UCHAR *)pFunction == 0xEB) || (*(UCHAR *)pFunction == 0xEA))
		{
			VirtualProtect(pFunction, 6, OldProtect, &OldProtect);
			return TRUE;
		}
		else
		{
			VirtualProtect(pFunction, 6, OldProtect, &OldProtect);
			return FALSE;
		}

	}

}


#endif