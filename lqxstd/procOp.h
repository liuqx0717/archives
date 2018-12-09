#include "stdafx.h"

#ifndef _PROCOP_H_
#define _PROCOP_H_

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

namespace lqx{


	BOOL enumproc(void (* proc)(PROCESSENTRY32* pe32));   //枚举当前所有进程
	DWORD *getPIDex(char *lpProcessName/*不区分大小写，前后不要有空格*/, int *n = 0); // 根据进程名查找进程PID 注：使用完要 delete[] <返回值> ！！
	inline DWORD getPID(char *lpProcessName/*不区分大小写，前后不要有空格*/) {  //根据进程名查找进程PID 
		DWORD r = 0; 
		DWORD *tmp = getPIDex(lpProcessName);
		if (tmp) {
			r = tmp[0];
			delete[] tmp;
		}
		return r;
	}



	BOOL enumthr(void(*proc)(THREADENTRY32 *te32));     //枚举当前所有线程
	DWORD *getTIDex(DWORD ProcessID, int *n);   //查找某个进程内的所有线程 注：使用完要 delete[] <返回值> ！！




	BOOL enummod(void(*proc)(MODULEENTRY32 *me32), DWORD ProcessID);
	DWORD getModUsgCount(DWORD ProcessID, const char* ModNameOrFullPath/*不区分大小写，前后不要有空格*/);
#ifdef _WIN64
	bool enummodex(void(*proc)(HMODULE *hModule, DWORD count, HANDLE hProcess), DWORD ProcessID, DWORD FilterFlag = LIST_MODULES_ALL);
#endif




	BOOL AdjustPriv(LPCSTR name, bool bEnable);  //调试权限：SE_DEBUG_NAME
	bool InjectDll(const TCHAR* ptszDllFile, DWORD dwProcessId);
	bool UnInjectDll(const TCHAR* ptszDllFile, DWORD dwProcessId);



	BOOL IsRunasAdmin();
	DWORD RunAsAdminA(const char *ExeFile, int ShowWindow = SW_SHOWNORMAL);    //自动去除Exefile两边的空格、跳格和双引号。    
	DWORD RunAsAdminW(const wchar_t *ExeFile, int ShowWindow = SW_SHOWNORMAL);  //返回值可能为：ERROR_SUCCESS      ERROR_CANCELLED    ERROR_FILE_NOT_FOUND




	//查看某个进程的CPU使用情况 
	//原理：调用GetProcessTimes()，并与上次调用得到的结果相减，即得到某段时间内CPU的使用时间
	class CPUusage {
	private:
		typedef long long          int64_t;
		typedef unsigned long long uint64_t;

		HANDLE _hProcess;
		int _processor;    //cpu数量  
		int64_t _last_time;         //上一次的时间  
		int64_t _last_system_time;


		// 时间转换  
		uint64_t file_time_2_utc(const FILETIME* ftime);

		// 获得CPU的核数  
		int get_processor_number();

		//初始化
		void init()
		{
			_last_system_time = 0;
			_last_time = 0;
			_hProcess = 0;
		}

		//关闭进程句柄
		void clear()
		{
			if (_hProcess) {
				CloseHandle(_hProcess);
				_hProcess = 0;
			}
		}

	public:
		CPUusage(DWORD ProcessID) {
			init();
			_processor = get_processor_number();
			setpid(ProcessID);
		}
		CPUusage() { init(); _processor = get_processor_number(); }
		~CPUusage() { clear(); }

		//返回值为进程句柄，可判断OpenProcess是否成功
		HANDLE setpid(DWORD ProcessID) {
			clear();    //如果之前监视过另一个进程，就先关闭它的句柄
			init();
			return _hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ProcessID);
		}

		//-1 即为失败或进程已退出； 如果成功，首次调用会返回-2（中途用setpid更改了PID后首次调用也会返回-2）
		float get_cpu_usage();
	};

}

#endif