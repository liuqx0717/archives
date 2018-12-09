// GetForewindow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Psapi.h>
#include <cstdio>
#include <clocale>

#ifdef WINXP
#pragma comment(lib,"Psapi.Lib")

#endif


class WindowInfo {
public:
	HWND handle;
	DWORD pid;
	DWORD tid;
	WCHAR procfilename[MAX_PATH];
	WCHAR title[MAX_PATH];
	WCHAR classname[MAX_PATH];

	bool operator==(const WindowInfo &info) const;

};
void output(WindowInfo info);

int main()
{
	setlocale(LC_ALL, "chs");

	for (;;) {
		WindowInfo info;
		ZeroMemory(&info, sizeof(WindowInfo));

		info.handle = GetForegroundWindow();
		info.tid = GetWindowThreadProcessId(info.handle, &info.pid);
		HANDLE hp = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, info.pid);
		if (!hp) {
			wcscpy_s(info.procfilename, MAX_PATH, L"无法获取");
		}
		else {
			if (!GetModuleFileNameEx(hp, NULL, info.procfilename, MAX_PATH)) {
				wcscpy_s(info.procfilename, MAX_PATH, L"无法获取");
			}
		}
		if (!GetWindowText(info.handle, info.title, MAX_PATH)) {
			wcscpy_s(info.title, MAX_PATH, L"<null>");
		}
		if (!GetClassName(info.handle, info.classname, MAX_PATH)) {
			wcscpy_s(info.classname, MAX_PATH, L"无法获取");
		}

		output(info);

		Sleep(100);

	}



    return 0;
}


void output(WindowInfo info)
{
	static WindowInfo formerinfo;

	if (formerinfo == info) {
		return;
	}

	SYSTEMTIME time;
	GetLocalTime(&time);

	wprintf(
		L"%02d:%02d:%02d.%02d    handle: %u  pid: %d  tid: %d  process: %lS  title: %lS  class: %lS\n\n",
		time.wHour,
		time.wMinute,
		time.wSecond,
		time.wMilliseconds / 10,
		info.handle,
		info.pid,
		info.tid,
		info.procfilename,
		info.title,
		info.classname
	);

	formerinfo = info;


}



bool WindowInfo::operator==(const WindowInfo &info) const
{
	if (handle != info.handle) return false;
	if (pid != info.pid) return false;
	if (tid != info.tid) return false;
	if (wcscmp(procfilename, info.procfilename)) return false;
	if (wcscmp(title, info.title)) return false;
	if (wcscmp(classname, info.classname)) return false;

	return true;
}