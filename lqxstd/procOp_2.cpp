#include "stdafx.h"

#include "procOp.h"
#include "string.h"
#include <vector>

namespace lqx {

	std::vector<DWORD> _procOp_2_ret;
	LPCTSTR _procOp_2_lpProcessName;


	void procOp_2_proc1(PROCESSENTRY32 *pe32)
	{
		if (lqx::cmpa(pe32->szExeFile, _procOp_2_lpProcessName))
			_procOp_2_ret.push_back(pe32->th32ProcessID);
	}


	DWORD *getPIDex(char *lpProcessName, int *n)
	{
		size_t tmp, i;
		DWORD *tmpret;

		_procOp_2_ret.clear();
		_procOp_2_lpProcessName = (lpProcessName);

		if (!lqx::enumproc(&lqx::procOp_2_proc1))
		{
			if (n) *n = 0;
			return 0;
		}
		tmp = _procOp_2_ret.size();
		if (tmp) {
			tmpret = new DWORD[tmp];
			for (i = 0; i < tmp; ++i)tmpret[i] = _procOp_2_ret[i];
			if (n) *n = tmp;
			return tmpret;
		}
		else {
			if (n) *n = 0;
			return 0;
		}

	}

	BOOL enumproc(void(* proc)(PROCESSENTRY32* pe32))
	{
		PROCESSENTRY32 pe32 = { sizeof(pe32) };
		HANDLE hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessShot == INVALID_HANDLE_VALUE)
			return FALSE;
		if (Process32First(hProcessShot, &pe32))
		{
			do {
				(*proc)(&pe32);
			} while (Process32Next(hProcessShot, &pe32));
		}
		CloseHandle(hProcessShot);
		return TRUE;
	}

}


//DWORD *lqx::getPIDex(LPCTSTR lpProcessName, int *n)//根据进程名查找进程PID 
//{
//	std::vector<int> ret;
//	size_t tmp, i;
//	DWORD *tmpret;
//
//	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//	if (hSnapShot == INVALID_HANDLE_VALUE)
//	{
//		if (n) *n = 0;
//		return 0;
//	}
//
//	PROCESSENTRY32 pe32;//声明进程入口对象 
//	pe32.dwSize = sizeof(PROCESSENTRY32);//填充进程入口对象大小 
//	Process32First(hSnapShot, &pe32);//遍历进程列表 
//	do
//	{
//		if (!lstrcmp(pe32.szExeFile, lpProcessName))//查找指定进程名的PID 
//		{
//			ret.push_back(pe32.th32ProcessID);
//
//		}
//	} while (Process32Next(hSnapShot, &pe32));
//	CloseHandle(hSnapShot);
//	tmp = ret.size();
//	if (tmp) {
//		tmpret = new DWORD[tmp];
//		for (i = 0; i < tmp; ++i)tmpret[i] = ret[i];
//		if (n) *n = tmp;
//		return tmpret;
//	}
//	else {
//		if (n) *n = 0;
//		return 0;
//	}
//
//}