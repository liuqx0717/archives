#include "stdafx.h"

#ifndef _PROCOP_H_
#define _PROCOP_H_

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

namespace lqx{


	BOOL enumproc(void (* proc)(PROCESSENTRY32* pe32));   //ö�ٵ�ǰ���н���
	DWORD *getPIDex(char *lpProcessName/*�����ִ�Сд��ǰ��Ҫ�пո�*/, int *n = 0); // ���ݽ��������ҽ���PID ע��ʹ����Ҫ delete[] <����ֵ> ����
	inline DWORD getPID(char *lpProcessName/*�����ִ�Сд��ǰ��Ҫ�пո�*/) {  //���ݽ��������ҽ���PID 
		DWORD r = 0; 
		DWORD *tmp = getPIDex(lpProcessName);
		if (tmp) {
			r = tmp[0];
			delete[] tmp;
		}
		return r;
	}



	BOOL enumthr(void(*proc)(THREADENTRY32 *te32));     //ö�ٵ�ǰ�����߳�
	DWORD *getTIDex(DWORD ProcessID, int *n);   //����ĳ�������ڵ������߳� ע��ʹ����Ҫ delete[] <����ֵ> ����




	BOOL enummod(void(*proc)(MODULEENTRY32 *me32), DWORD ProcessID);
	DWORD getModUsgCount(DWORD ProcessID, const char* ModNameOrFullPath/*�����ִ�Сд��ǰ��Ҫ�пո�*/);
#ifdef _WIN64
	bool enummodex(void(*proc)(HMODULE *hModule, DWORD count, HANDLE hProcess), DWORD ProcessID, DWORD FilterFlag = LIST_MODULES_ALL);
#endif




	BOOL AdjustPriv(LPCSTR name, bool bEnable);  //����Ȩ�ޣ�SE_DEBUG_NAME
	bool InjectDll(const TCHAR* ptszDllFile, DWORD dwProcessId);
	bool UnInjectDll(const TCHAR* ptszDllFile, DWORD dwProcessId);



	BOOL IsRunasAdmin();
	DWORD RunAsAdminA(const char *ExeFile, int ShowWindow = SW_SHOWNORMAL);    //�Զ�ȥ��Exefile���ߵĿո������˫���š�    
	DWORD RunAsAdminW(const wchar_t *ExeFile, int ShowWindow = SW_SHOWNORMAL);  //����ֵ����Ϊ��ERROR_SUCCESS      ERROR_CANCELLED    ERROR_FILE_NOT_FOUND




	//�鿴ĳ�����̵�CPUʹ����� 
	//ԭ������GetProcessTimes()�������ϴε��õõ��Ľ����������õ�ĳ��ʱ����CPU��ʹ��ʱ��
	class CPUusage {
	private:
		typedef long long          int64_t;
		typedef unsigned long long uint64_t;

		HANDLE _hProcess;
		int _processor;    //cpu����  
		int64_t _last_time;         //��һ�ε�ʱ��  
		int64_t _last_system_time;


		// ʱ��ת��  
		uint64_t file_time_2_utc(const FILETIME* ftime);

		// ���CPU�ĺ���  
		int get_processor_number();

		//��ʼ��
		void init()
		{
			_last_system_time = 0;
			_last_time = 0;
			_hProcess = 0;
		}

		//�رս��̾��
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

		//����ֵΪ���̾�������ж�OpenProcess�Ƿ�ɹ�
		HANDLE setpid(DWORD ProcessID) {
			clear();    //���֮ǰ���ӹ���һ�����̣����ȹر����ľ��
			init();
			return _hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ProcessID);
		}

		//-1 ��Ϊʧ�ܻ�������˳��� ����ɹ����״ε��û᷵��-2����;��setpid������PID���״ε���Ҳ�᷵��-2��
		float get_cpu_usage();
	};

}

#endif