#include "stdafx.h"

#include "serviceOp.h"




namespace lqx {


	//0:失败  1:成功  2:超时
	int WaitForServiceStatusA(SC_HANDLE schService, DWORD Status, int TimeOut/*单位：秒*/)
	{
		SERVICE_STATUS status;
		BOOL ret;
		int n = 0;
		while (n<TimeOut * 2) {
			Sleep(500);
			n++;
			ret = QueryServiceStatus(schService, &status);
			if (!ret) return 0;
			if (status.dwCurrentState == Status) return 1;
		}

		return 2;

	}

	DWORD ChangeServiceStatusA(const char *Name, bool Start, int TimeOut/*单位：秒*/)
	{
		SERVICE_STATUS status;
		SC_HANDLE schSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);   // 打开服务控制管
																					  //理数据库，并返回服务控制管理数据库的句柄
		int ret;
		if (schSCManager == NULL)
		{
			return FALSE;
		}
		SC_HANDLE schService = OpenServiceA(schSCManager, Name, SERVICE_ALL_ACCESS);    // 获得服务句柄
		if (schService == NULL)
		{
			return FALSE;
		}
		//QueryServiceStatus(schService, &status);   // 获得服务的当前状态
		//if (status.dwCurrentState = SERVICE_STOPPED)   // 如果服务处于停止状态，则将其状态设置为启动状态
		//	StartService(schService, 0, NULL);   //启动服务
		if (Start) {
			if (!StartServiceA(schService, 0, NULL)) {
				return GetLastError();
			}
			ret = WaitForServiceStatusA(schService, SERVICE_RUNNING, TimeOut);

		}
		else {
			if (!ControlService(schService, SERVICE_CONTROL_STOP, &status)) {
				return GetLastError();
			}
			ret = WaitForServiceStatusA(schService, SERVICE_STOPPED, TimeOut);
		}

		CloseServiceHandle(schSCManager);   // 关闭服务句柄
		CloseServiceHandle(schService);

		if (!ret) return GetLastError();
		if (ret == 2) return ERROR_SERVICE_REQUEST_TIMEOUT;
		return ERROR_SUCCESS;

	}




}