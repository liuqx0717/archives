#include "stdafx.h"

#include "procOp.h"
#include "string.h"
#include <vector>

namespace lqx {

	const char *_procOp_4_ModNameOrFullPath;
	DWORD _procOp_4_ret;

	void procOp_4_proc1(MODULEENTRY32 *te32)
	{
		if (cmpa(te32->szModule, _procOp_4_ModNameOrFullPath)||cmpa(te32->szExePath, _procOp_4_ModNameOrFullPath))
			_procOp_4_ret = te32->ProccntUsage;
	}

	BOOL enummod(void(*proc)(MODULEENTRY32 *me32), DWORD ProcessID)
	{

		MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };

		HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
		if (hModuleSnap == INVALID_HANDLE_VALUE)
			return FALSE;

		if (Module32First(hModuleSnap, &me32))
		{
			do {
				(*proc)(&me32);
			} while (Module32Next(hModuleSnap, &me32));
		}

		CloseHandle(hModuleSnap);
		return TRUE;
	}

	DWORD getModUsgCount(DWORD ProcessID, const char* ModNameOrFullPath)
	{
		_procOp_4_ModNameOrFullPath = ModNameOrFullPath;
		_procOp_4_ret = 0;
		if (!enummod(&procOp_4_proc1, ProcessID))
		{
			return 0;
		}
		return _procOp_4_ret;

	}

}