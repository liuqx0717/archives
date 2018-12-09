#include "stdafx.h"

#include "procOp.h"

#include <tchar.h>

bool lqx::InjectDll(const TCHAR* ptszDllFile, DWORD dwProcessId)
{
	// ������Ч    
	//if (NULL == ptszDllFile || 0 == ::_tcslen(ptszDllFile))
	//{
	//	return false;
	//}
	// ָ�� Dll �ļ�������    
	//if (-1 == _taccess(ptszDllFile, 0))    
	//{    
	//    return false;    
	//}    
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	DWORD dwSize = 0;
	TCHAR* ptszRemoteBuf = NULL;
	LPTHREAD_START_ROUTINE lpThreadFun = NULL;
	// ��ȡĿ����̾��    
	hProcess = ::OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessId);
	if (NULL == hProcess)
	{
		return false;
	}
	// ��Ŀ������з����ڴ�ռ�    
	dwSize = (DWORD)::_tcslen(ptszDllFile) + 1;
	ptszRemoteBuf = (TCHAR*)::VirtualAllocEx(hProcess, NULL, dwSize * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
	if (NULL == ptszRemoteBuf)
	{
		::CloseHandle(hProcess);
		return false;
	}
	// ��Ŀ����̵��ڴ�ռ���д���������(ģ����)    
	if (FALSE == ::WriteProcessMemory(hProcess, ptszRemoteBuf, (LPVOID)ptszDllFile, dwSize * sizeof(TCHAR), NULL))
	{
		::VirtualFreeEx(hProcess, ptszRemoteBuf, dwSize, MEM_DECOMMIT);
		::CloseHandle(hProcess);
		return false;
	}
	// �� Kernel32.dll �л�ȡ LoadLibrary ������ַ    
#ifdef _UNICODE    
	lpThreadFun = (PTHREAD_START_ROUTINE)::GetProcAddress(::GetModuleHandle(_T("Kernel32")), "LoadLibraryW");
#else    
	lpThreadFun = (PTHREAD_START_ROUTINE)::GetProcAddress(::GetModuleHandle(_T("Kernel32")), "LoadLibraryA");
#endif    
	if (NULL == lpThreadFun)
	{
		::VirtualFreeEx(hProcess, ptszRemoteBuf, dwSize, MEM_DECOMMIT);
		::CloseHandle(hProcess);
		return false;
	}
	// ����Զ���̵߳��� LoadLibrary    
	hThread = ::CreateRemoteThread(hProcess, NULL, 0, lpThreadFun, ptszRemoteBuf, 0, NULL);
	if (NULL == hThread)
	{
		::VirtualFreeEx(hProcess, ptszRemoteBuf, dwSize, MEM_DECOMMIT);
		::CloseHandle(hProcess);
		return false;
	}
	// �ȴ�Զ���߳̽���    
	::WaitForSingleObject(hThread, INFINITE);
	// ����    
	::VirtualFreeEx(hProcess, ptszRemoteBuf, dwSize, MEM_DECOMMIT);
	::CloseHandle(hThread);
	::CloseHandle(hProcess);
	return true;
}

bool lqx::UnInjectDll(const TCHAR* ptszDllFile, DWORD dwProcessId)
{
	// ������Ч    
	//if (NULL == ptszDllFile || 0 == ::_tcslen(ptszDllFile))
	//{
	//	return false;
	//}
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	// ��ȡģ�����    
	hModuleSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (INVALID_HANDLE_VALUE == hModuleSnap)
	{
		return false;
	}
	MODULEENTRY32 me32;
	memset(&me32, 0, sizeof(MODULEENTRY32));
	me32.dwSize = sizeof(MODULEENTRY32);
	// ��ʼ����    
	if (FALSE == ::Module32First(hModuleSnap, &me32))
	{
		::CloseHandle(hModuleSnap);
		return false;
	}
	// ��������ָ��ģ��    
	bool isFound = false;
	do
	{
		isFound = (0 == ::_tcsicmp(me32.szModule, ptszDllFile) || 0 == ::_tcsicmp(me32.szExePath, ptszDllFile));
		if (isFound) // �ҵ�ָ��ģ��    
		{
			break;
		}
	} while (TRUE == ::Module32Next(hModuleSnap, &me32));
	::CloseHandle(hModuleSnap);
	if (false == isFound)
	{
		return false;
	}
	// ��ȡĿ����̾��    
	hProcess = ::OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION, FALSE, dwProcessId);
	if (NULL == hProcess)
	{
		return false;
	}
	// �� Kernel32.dll �л�ȡ FreeLibrary ������ַ    
	LPTHREAD_START_ROUTINE lpThreadFun = (PTHREAD_START_ROUTINE)::GetProcAddress(::GetModuleHandle(_T("Kernel32")), "FreeLibrary");
	if (NULL == lpThreadFun)
	{
		::CloseHandle(hProcess);
		return false;
	}
	// ����Զ���̵߳��� FreeLibrary    
	hThread = ::CreateRemoteThread(hProcess, NULL, 0, lpThreadFun, me32.modBaseAddr /* ģ���ַ */, 0, NULL);
	if (NULL == hThread)
	{
		::CloseHandle(hProcess);
		return false;
	}
	// �ȴ�Զ���߳̽���    
	::WaitForSingleObject(hThread, INFINITE);
	// ����    
	::CloseHandle(hThread);
	::CloseHandle(hProcess);
	return true;
}

BOOL lqx::AdjustPriv(LPCSTR name, bool bEnable)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;
	BOOL ret;
	DWORD err;
	//�򿪽������ƻ�
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	//��ý��̱���ΨһID
	LookupPrivilegeValue(NULL, name, &luid);

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = (bEnable ? SE_PRIVILEGE_ENABLED : 0);
	tp.Privileges[0].Luid = luid;
	//����Ȩ��
	ret = AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
	err = GetLastError();
	//FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&s, 0, NULL);
	//std::cout << s;
	CloseHandle(hToken);
	return (ret && (!err));

}