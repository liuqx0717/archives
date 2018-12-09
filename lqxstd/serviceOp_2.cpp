#include "stdafx.h"

#include "serviceOp.h"




namespace lqx {

	//0:ʧ��  1:�ɹ�  2:��ʱ
	int WaitForServiceStatusW(SC_HANDLE schService, DWORD Status, int TimeOut/*��λ����*/)
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

	DWORD ChangeServiceStatusW(const wchar_t *Name, bool Start, int TimeOut/*��λ����*/)
	{
		SERVICE_STATUS status;
		SC_HANDLE schSCManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);   // �򿪷�����ƹ�
																					  //�����ݿ⣬�����ط�����ƹ������ݿ�ľ��
		int ret;
		if (schSCManager == NULL)
		{
			return FALSE;
		}
		SC_HANDLE schService = OpenServiceW(schSCManager, Name, SERVICE_ALL_ACCESS);    // ��÷�����
		if (schService == NULL)
		{
			return FALSE;
		}
		//QueryServiceStatus(schService, &status);   // ��÷���ĵ�ǰ״̬
		//if (status.dwCurrentState = SERVICE_STOPPED)   // ���������ֹͣ״̬������״̬����Ϊ����״̬
		//	StartService(schService, 0, NULL);   //��������
		if (Start) {
			if (!StartServiceW(schService, 0, NULL)) {
				return GetLastError();
			}
			ret = WaitForServiceStatusW(schService, SERVICE_RUNNING, TimeOut);

		}
		else {
			if (!ControlService(schService, SERVICE_CONTROL_STOP, &status)) {
				return GetLastError();
			}
			ret = WaitForServiceStatusW(schService, SERVICE_STOPPED, TimeOut);
		}

		CloseServiceHandle(schSCManager);   // �رշ�����
		CloseServiceHandle(schService);

		if (!ret) return GetLastError();
		if (ret == 2) return ERROR_SERVICE_REQUEST_TIMEOUT;
		return ERROR_SUCCESS;

	}


}