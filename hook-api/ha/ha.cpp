// sydll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include <Psapi.h>

void ha();
void ha_d();

extern lqx::memshare ms;

typedef int(__stdcall *pf_msgbox)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType);
pf_msgbox ori_msgbox = &MessageBoxA;
int __stdcall fake_msgbox(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType)
{
	(*ori_msgbox)(NULL, "!!!", "!!!", 64);
	return 0;

}

typedef BOOL(__stdcall *pf_TerminateProcess)(HANDLE h, UINT u);
pf_TerminateProcess ori_TerminateProcess = &TerminateProcess;
BOOL __stdcall fake_TerminateProcess(HANDLE h, UINT u)
{
	return 0;
}




//typedef int (__stdcall *pf_showcursor) (BOOL b);
//pf_showcursor ori_showcursor = &ShowCursor;
//int __stdcall fake_showcursor(BOOL b)
//{
//	if (b) return 1;
//	else return -1;
//}


typedef HMODULE(__stdcall *pf_loadlibrarya)(LPCSTR name);
pf_loadlibrarya ori_loadlibrarya = &LoadLibraryA;
HMODULE __stdcall fake_loadlibrarya(LPCSTR name)
{
	ms.write(000, strlen(name) + 1, (void *)name);
	ms.sendevent(MS_LOADDLLA, MS_PID_DEBUG, 0, 0);
	
	return ori_loadlibrarya(name);
}

typedef HMODULE(__stdcall *pf_loadlibraryw)(LPCWSTR name);
pf_loadlibraryw ori_loadlibraryw = &LoadLibraryW;
HMODULE __stdcall fake_loadlibraryw(LPCWSTR name)
{
	ms.write(0, lstrlenW(name)*2 + 2, (void *)name);
	ms.sendevent(MS_LOADDLLW, MS_PID_DEBUG, 0, 0);
	return ori_loadlibraryw(name);
}



typedef HANDLE(__stdcall *pf_createfilew)(
	_In_ LPCWSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	);
pf_createfilew ori_createfilew = &CreateFileW;
HANDLE __stdcall fake_createfilew(
	_In_ LPCWSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	)
{
	if (wcsstr(lpFileName, L"librdi_commonxillic")) {
		return (*ori_createfilew)(
			L"D:\\Xilinx\\Vivado\\2015.4\\lib\\win64.o\\librdi_commonxillic_0.dll",
			dwDesiredAccess,
			dwShareMode,
			lpSecurityAttributes,
			dwCreationDisposition,
			dwFlagsAndAttributes,
			hTemplateFile
			);
	}
	else {
		return (*ori_createfilew)(
			lpFileName,
			dwDesiredAccess,
			dwShareMode,
			lpSecurityAttributes,
			dwCreationDisposition,
			dwFlagsAndAttributes,
			hTemplateFile
			);
	}
}

void ha()
{
	
	//DetourAttach((void**)&ori_msgbox, &fake_msgbox);
	//DetourAttach((void**)&ori_TerminateProcess, &fake_TerminateProcess);
	//DetourAttach((void**)&ori_loadlibrarya, &fake_loadlibrarya);
	//DetourAttach((void**)&ori_loadlibraryw, &fake_loadlibraryw);
	//DetourAttach((void**)&ori_createfilew, &fake_createfilew);

}

void ha_d()
{
	//DetourDetach((void**)&ori_msgbox, &fake_msgbox);
	//DetourDetach((void**)&ori_TerminateProcess, &fake_TerminateProcess);

}