#include <Windows.h>

#define AM_STOP (WM_APP+1)

#pragma data_seg("memsh")
DWORD tid = 0;
DWORD tid2 = 0;
#pragma data_seg()
#pragma comment(linker,"/SECTION:memsh,RWS")

bool cmp(wchar_t *str1, wchar_t *str2);
void ShowNotify(const wchar_t *title, const wchar_t *info);

bool reg();
void unreg();
void hotkey1();
void hotkey2();
void hotkey3();
void hotkey4();
void hotkey5();
void hotkey6();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	MSG msg;

	if (*lpCmdLine == 0) {
		if (tid) {
			if (MessageBox(NULL, L"The application is running.\nSend a message to stop it?", L"Message", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2 | MB_SETFOREGROUND) == IDYES)
				goto stop;
			return 0;
		}
		tid = GetCurrentThreadId();
		if (!reg()) {
			MessageBox(NULL, L"RegisterHotkey() failed.", L"Error", MB_ICONERROR | MB_SETFOREGROUND);
			return 1;
		}
		else 
			MessageBox(NULL, L"The application started successfully.", L"Message", MB_ICONINFORMATION | MB_SETFOREGROUND);

	}
	else if (cmp(lpCmdLine, L"/start")) {
		if (tid) return 0;
		tid = GetCurrentThreadId();
		if (!reg()) return 1;
	}
	else if (cmp(lpCmdLine, L"/stop")) {
	stop:
		if (tid) {
			tid2 = GetCurrentThreadId();
			if (!PostThreadMessage(tid, AM_STOP, 0, 0)) {
				MessageBox(NULL, L"PostThreadMessage() failed.", L"Error", MB_ICONERROR | MB_SETFOREGROUND);
				return 1;
			}
			for (int i = 0; i < 25; i++) {
				if (PeekMessage(&msg, (HWND)-1, AM_STOP, AM_STOP, PM_REMOVE)) {
					MessageBox(NULL, L"The application stoped successfully.", L"Message", MB_ICONINFORMATION | MB_SETFOREGROUND);
					return 0;
				}
				Sleep(200);
			}
			MessageBox(NULL, L"The running application doesn't give any response.", L"Error", MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			return 1;
		}
		else {
			MessageBox(NULL, L"The application is not running.", L"Message", MB_ICONINFORMATION | MB_SETFOREGROUND);
			return 0;
		}
	}
	else if (cmp(lpCmdLine, L"/stop-q")) {
		if (tid) {
			tid2 = GetCurrentThreadId();
			if (!PostThreadMessage(tid, AM_STOP, 0, 0))
				return 1;
			for (int i = 0; i < 25; i++) {
				if (PeekMessage(&msg, (HWND)-1, AM_STOP, AM_STOP, PM_REMOVE)) return 0;
				Sleep(200);
			}
			return 1;
		}
		else 
			return 0;
	}
	else {
		MessageBox(NULL, 
			L"USAGE: lqxHotkeys [command]\n"
			"command can be any one of the following commands:\n"
			"/start\tstarts the application quietly.\n"
			"/stop\tstops the application.\n"
			"/stop-q\tstops the application quietly.\n\n"
			"The commands are case-insensitive.\n"
			"The application will return 1 if an error occurs.",
			L"Message", MB_ICONINFORMATION | MB_SETFOREGROUND);
		return 1;
	}
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_HOTKEY) {
			switch (msg.wParam)
			{
			case 1:
				hotkey1();
				break;
			case 2:
				hotkey2();
				break;
			case 3:
				hotkey3();
				break;
			case 4:
				hotkey4();
				break;
			case 5:
				hotkey5();
				break;
			case 6:
				hotkey6();
				break;
			default:
				break;
			}
		}
		else if (msg.message == AM_STOP) {
			unreg();
			PostThreadMessage(tid2, AM_STOP, 0, 0);
			return 0;
		}
	}
	return 0;
}

bool cmp(wchar_t *str1, wchar_t *str2)
{
	int i;
	for (i = 0; str1[i] && str2[i]; i++)
		if (str1[i] != str2[i] && str1[i] != str2[i] + ('A' - 'a') && str1[i] != str2[i] - ('A' - 'a')) return false;
	if (str1[i] || str2[i]) return false;
	return true;
}

void ShowNotify(const wchar_t *title, const wchar_t *info)
{
	NOTIFYICONDATAW d;
	ZeroMemory(&d, sizeof(NOTIFYICONDATA));
	d.cbSize = sizeof(NOTIFYICONDATA);
	d.uID = 1U;
	d.uFlags = NIF_INFO;
	wcscpy_s(d.szInfoTitle, 64, title);
	wcscpy_s(d.szInfo, 64, info);
	d.dwInfoFlags = NIIF_INFO;

	Shell_NotifyIcon(NIM_ADD, &d);
	Shell_NotifyIcon(NIM_DELETE, &d);
}


bool reg()
{
	if (!RegisterHotKey(NULL, 1, MOD_ALT | MOD_CONTROL, 'X')) return false;
	if (!RegisterHotKey(NULL, 2, MOD_WIN, 192)) return false;
	if (!RegisterHotKey(NULL, 3, MOD_ALT | MOD_CONTROL, 'W')) return false;
	if (!RegisterHotKey(NULL, 4, MOD_ALT | MOD_CONTROL, 'A')) return false;
	if (!RegisterHotKey(NULL, 5, MOD_ALT | MOD_CONTROL, 'C')) return false;
	if (!RegisterHotKey(NULL, 6, MOD_ALT | MOD_CONTROL, 'B')) return false;

	return true;
}

void unreg()
{
	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL, 2);
	UnregisterHotKey(NULL, 3);
	UnregisterHotKey(NULL, 4);
	UnregisterHotKey(NULL, 5);
	UnregisterHotKey(NULL, 6);

}

void hotkey1()
{
	wchar_t classname[MAX_PATH];
	HWND hw = GetForegroundWindow();
	if (!hw) return;
	GetClassNameW(hw, classname, MAX_PATH);
	if (cmp(classname, L"WorkerW")) return;
	PostMessage(hw, WM_SYSCOMMAND, SC_MINIMIZE, 0);



}

void hotkey2()
{
	HWND hw = GetForegroundWindow();
	LONG wl = GetWindowLong(hw, GWL_EXSTYLE);
	if (wl&WS_EX_TOPMOST)
		SetWindowPos(hw, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else 
		SetWindowPos(hw, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}


void hotkey3()
{
	HANDLE hEvent = CreateEventW(NULL, TRUE, FALSE, L"Local\\LIUQX_WIFISHARE_EVENT_START");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		SetEvent(hEvent);
		ResetEvent(hEvent);
		CloseHandle(hEvent);
	}
	else {
		CloseHandle(hEvent);
		WinExec("\"C:\\刘权兴\\wifishare64.exe\"", SW_SHOW);

	}

}

void hotkey4()
{

	WinExec("\"C:\\Windows\\system32\\SnippingTool.exe\"", SW_SHOW);
	
}



DWORD _hotkey5_pid = 0;
HWND _hotkey5_hwnd = 0;

BOOL CALLBACK hotkey5_EnumCallBack(HWND hWnd, LPARAM lParam)
{
	wchar_t classname[MAX_PATH];
	DWORD pid;
	GetClassNameW(hWnd, classname, MAX_PATH);
	if (cmp(classname, L"ConsoleWindowClass")) {
		GetWindowThreadProcessId(hWnd, &pid);
		if (pid == _hotkey5_pid) {
			_hotkey5_hwnd = hWnd;
			return FALSE;
		}
	}
	return TRUE;
}

//DWORD __stdcall hotkey5_wait(LPVOID p)
//{
//
//}


void hotkey5()
{
	static HWND originalhwnd;
	HWND currenthwnd;


	_hotkey5_hwnd = 0;
	EnumWindows(&hotkey5_EnumCallBack, NULL);

	if (_hotkey5_hwnd) {
		
		currenthwnd = GetForegroundWindow();             //当前活动的窗口
		if (currenthwnd == _hotkey5_hwnd) {              //如果当前活动的窗口就是之前的cmd窗口
			SwitchToThisWindow(originalhwnd, TRUE);
		}
		else {
			originalhwnd = currenthwnd;
			SwitchToThisWindow(_hotkey5_hwnd, TRUE);
		}

	}
	else {
		//WinExec("\"C:\\Windows\\system32\\cmd.exe\" /k cd E:\\刘权兴\\Program Files && e:", SW_SHOW);
		//wchar_t cmdline[MAX_PATH] = L"\"C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe\" -noexit -command cd $env:lp";
		wchar_t cmdline[MAX_PATH] = L"\"C:\\Windows\\system32\\cmd.exe\" /k cd %c%";

		originalhwnd = GetForegroundWindow();

		STARTUPINFOW si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (CreateProcessW(NULL, cmdline, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
			_hotkey5_pid = pi.dwProcessId;
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}


}



void hotkey6()
{
	static bool suspended;

	wchar_t cmdline1[MAX_PATH] = L"pssuspend64 baidunetdisk.exe";
	wchar_t cmdline2[MAX_PATH] = L"pssuspend64 -r baidunetdisk.exe";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	if(!suspended){
		if (CreateProcessW(NULL, cmdline1, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			ShowNotify(L"lqxHotkeys", L"[baidunetdisk.exe] suspended");
			suspended = true;
		}
	
	}
	else {
		if (CreateProcessW(NULL, cmdline2, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			ShowNotify(L"lqxHotkeys", L"[baidunetdisk.exe] resumed");
			suspended = false;
		}


	}




}