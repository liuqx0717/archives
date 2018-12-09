#include "stdafx.h"

#ifdef _WIN64

#include "procOp.h"

namespace lqx {


	bool enummodex(void(*proc)(HMODULE *hModule, DWORD count, HANDLE hProcess), DWORD ProcessID, DWORD FilterFlag)
	{
		DWORD cap = 256, size = 0;
		HMODULE *hm;
		HANDLE hp = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ProcessID);
		if (!hp) return false;
	a:
		hm = new HMODULE[cap];
		if (!EnumProcessModulesEx(hp, hm, cap * sizeof(HMODULE), &size, FilterFlag)) {
			delete[] hm;
			return false;
		}
		size /= sizeof(HMODULE);
		if (size > cap) {
			delete[] hm;
			cap *= 2;
			goto a;
		}

		(*proc)(hm, size, hp);
		delete[] hm;
		return true;
	}



}



#endif