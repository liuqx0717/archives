#include "stdafx.h"

#include "procOp.h"
#include <vector>

namespace lqx {

	std::vector<DWORD> _procOp_3_ret;
	DWORD _procOp_3_ProcessID;


	void procOp_3_proc1(THREADENTRY32 *te32)
	{
		if (te32->th32OwnerProcessID == _procOp_3_ProcessID)
			_procOp_3_ret.push_back(te32->th32ThreadID);
	}

	BOOL enumthr(void(*proc)(THREADENTRY32 *te32))
	{

		THREADENTRY32 te32 = { sizeof(THREADENTRY32) };

		HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (hThreadSnap == INVALID_HANDLE_VALUE)
			return FALSE;

		if (Thread32First(hThreadSnap, &te32))
		{
			do {
				(*proc)(&te32);
			} while (Thread32Next(hThreadSnap, &te32));
		}

		CloseHandle(hThreadSnap);
		return TRUE;
	}

	DWORD *getTIDex(DWORD ProcessID, int *n)
	{
		size_t tmp, i;
		DWORD *tmpret;

		_procOp_3_ret.clear();
		_procOp_3_ProcessID = ProcessID;

		if (!enumthr(&procOp_3_proc1))
		{
			if (n) *n = 0;
			return 0;
		}
		tmp = _procOp_3_ret.size();
		if (tmp) {
			tmpret = new DWORD[tmp];
			for (i = 0; i < tmp; ++i)tmpret[i] = _procOp_3_ret[i];
			if (n) *n = tmp;
			return tmpret;
		}
		else {
			if (n) *n = 0;
			return 0;
		}

	}

}