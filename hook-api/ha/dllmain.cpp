// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include <process.h>
//#include <cstdlib>



#pragma comment(lib,"legacy_stdio_definitions.lib")

char dllfilea[MAX_PATH];
lqx::memshare ms;
HMODULE hm;
int pid;
//wchar_t dllfilew[MAX_PATH];
void ha();
void ha_d();
void eventproc(int n, int w, int lh, int ll);

typedef BOOL (__stdcall *pf_CreateProcessA)(
	_In_opt_ LPCSTR lpApplicationName,
	_Inout_opt_ LPSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOA lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	);
pf_CreateProcessA ori_CreateProcessA = &CreateProcessA;
BOOL __stdcall fake_CreateProcessA(
	_In_opt_ LPCSTR lpApplicationName,
	_Inout_opt_ LPSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOA lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	)
{
	//MessageBoxA(NULL, "A", "A", 64);
	BOOL ret= DetourCreateProcessWithDllExA(
		lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation,
		dllfilea,
		ori_CreateProcessA);
	//if (!ret) MessageBoxA(NULL, lqx::formatmsg(GetLastError()),"A",64);
	//else MessageBoxA(NULL, "TRUE", "A", 64);
	return ret;
}
typedef BOOL(__stdcall *pf_CreateProcessW)(
	_In_opt_ LPCWSTR lpApplicationName,
	_Inout_opt_ LPWSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCWSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOW lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	);
pf_CreateProcessW ori_CreateProcessW = &CreateProcessW;
BOOL __stdcall fake_CreateProcessW(
	_In_opt_ LPCWSTR lpApplicationName,
	_Inout_opt_ LPWSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCWSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOW lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	)
{
	//MessageBoxA(NULL, "W", "W", 64);
	BOOL ret = DetourCreateProcessWithDllExW(
		lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation,
		dllfilea,
		ori_CreateProcessW);
	//if (!ret) MessageBoxA(NULL, lqx::formatmsg(GetLastError()), "W", 64);
	//else MessageBoxA(NULL, "TRUE", "W", 64);
	return ret;
}



unsigned __stdcall t(void *p)
{
	DWORD usgcnt;
	switch ((size_t)p)
	{
	case T_START:
		//MessageBox(NULL, "t start.", "dll", 64);
		//if(!ms.init("ha_g", SHARED_MEM_BUFFSIZE, eventproc, true))
		//	ms.init("ha", SHARED_MEM_BUFFSIZE, eventproc, false);
		if (!ms.init("ha_g", SHARED_MEM_BUFFSIZE, eventproc, true)) {
			ms.init("ha", SHARED_MEM_BUFFSIZE, eventproc, false);
		}
		//ms.sendevent(123, -1, pid, 0);
		break;
	case T_STOP:
		ms.clear();
		usgcnt = lqx::getModUsgCount(0, dllfilea);
		while(usgcnt-->1) FreeLibrary(hm);
		break;
	default:
		break;
	}
	return 0;
}


void eventproc(int n, int w, int lh, int ll)
{
	DWORD *tid;
	int ntid;
	if (w == MS_PID_ALL || w == pid) {
		switch (n)
		{
		case MS_EXIT:
			MessageBox(NULL, "clearstart", "dll", 64);

			tid = lqx::getTIDex(GetCurrentProcessId(), &ntid);
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			HANDLE tmp;
			for (int i = 0; i < ntid; i++) {
				if (tid[i] == GetCurrentThreadId()) continue;
				tmp = OpenThread(THREAD_ALL_ACCESS, false, tid[i]);
				//ms.sendevent(2, 0, (size_t)tmp);
				DetourUpdateThread(tmp);
			}
			delete[] tid;
			DetourDetach((void**)&ori_CreateProcessA, &fake_CreateProcessA);
			DetourDetach((void**)&ori_CreateProcessW, &fake_CreateProcessW);
			ha_d();
			DetourTransactionCommit();
			_beginthreadex(NULL, 0, &t, (void*)T_STOP, 0, NULL);
			//MessageBox(NULL, "clearend", "dll", 64);
			break;
		default:
			break;
		}
	}
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (DetourIsHelperProcess()) return true;


		//MessageBox(NULL, "attach", "dll", 64);
		GetModuleFileNameA(hModule, dllfilea, MAX_PATH);
		hm = hModule;
		pid = GetCurrentProcessId();
		//GetModuleFileNameW(hModule, dllfilew, MAX_PATH);

		//ShowCursor(0);
		//_beginthreadex(NULL, 0, &t, NULL, 0, NULL);


		//DetourTransactionBegin();
		//DetourUpdateThread(GetCurrentThread());
		//DetourAttach((void **)&ori_showcursor, &fake_showcursor);
		//DetourTransactionCommit();


		DetourRestoreAfterWith();

		DetourTransactionBegin();
		//DetourUpdateThread(GetCurrentThread());
		DetourAttach((void**)&ori_CreateProcessA, &fake_CreateProcessA);
		DetourAttach((void**)&ori_CreateProcessW, &fake_CreateProcessW);
		ha();
		DetourTransactionCommit();

		_beginthreadex(NULL, 0, &t, (void*)T_START, 0, NULL);

		break;
	case DLL_THREAD_ATTACH:

		break;
	case DLL_THREAD_DETACH:

		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL, "detach", "dll", 64);

		break;
	}
	return TRUE;
}



extern "C" void __stdcall f(HWND a, HINSTANCE b, LPSTR c, INT d)
{
	DetourFinishHelperProcess(a, b, c, d);

}
