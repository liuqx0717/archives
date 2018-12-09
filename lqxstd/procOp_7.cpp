#include "stdafx.h"
#include "procOp.h"
#include <shellapi.h>

#include "string.h"

namespace lqx {

	BOOL IsRunasAdmin()
	{
		BOOL bElevated = FALSE;
		HANDLE hToken = NULL;

		// Get current process token  
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
			return FALSE;

		TOKEN_ELEVATION tokenEle;
		DWORD dwRetLen = 0;

		// Retrieve token elevation information  
		if (GetTokenInformation(hToken, TokenElevation, &tokenEle, sizeof(tokenEle), &dwRetLen))
		{
			if (dwRetLen == sizeof(tokenEle))
			{
				bElevated = tokenEle.TokenIsElevated;
			}
		}

		CloseHandle(hToken);
		return bElevated;
	}


	DWORD RunAsAdminA(const char *ExeFile, int ShowWindow)
	{
		SHELLEXECUTEINFOA sei = { sizeof(SHELLEXECUTEINFOA) };
		char exefile[MAX_PATH];
		strcpy_s(exefile, MAX_PATH, ExeFile);
		sei.lpVerb = "runas";
		sei.lpFile = trima(exefile, "\"\t ");     //去除两边的空格、跳格和双引号
		sei.nShow = SW_SHOWNORMAL;

		ShellExecuteExA(&sei);

		return GetLastError();
	}

	DWORD RunAsAdminW(const wchar_t *ExeFile, int ShowWindow)
	{
		SHELLEXECUTEINFOW sei = { sizeof(SHELLEXECUTEINFOW) };
		wchar_t exefile[MAX_PATH];
		wcscpy_s(exefile, MAX_PATH, ExeFile);
		sei.lpVerb = L"runas";
		sei.lpFile = trimw(exefile, L"\"\t ");     //去除两边的空格、跳格和双引号
		sei.nShow = SW_SHOWNORMAL;

		ShellExecuteExW(&sei);

		return GetLastError();
	}


}
