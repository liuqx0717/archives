#include "stdafx.h"

#include "serviceOp.h"




namespace lqx {


	//0:ʧ��  1:�ɹ�  2:��ʱ
	int WaitForServiceStatusA(SC_HANDLE schService, DWORD Status, int TimeOut/*��λ����*/)
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

	DWORD ChangeServiceStatusA(const char *Name, bool Start, int TimeOut/*��λ����*/)
	{
		SERVICE_STATUS status;
		SC_HANDLE schSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);   // �򿪷�����ƹ�
																					  //�����ݿ⣬�����ط�����ƹ������ݿ�ľ��
		int ret;
		if (schSCManager == NULL)
		{
			return FALSE;
		}
		SC_HANDLE schService = OpenServiceA(schSCManager, Name, SERVICE_ALL_ACCESS);    // ��÷�����
		if (schService == NULL)
		{
			return FALSE;
		}
		//QueryServiceStatus(schService, &status);   // ��÷���ĵ�ǰ״̬
		//if (status.dwCurrentState = SERVICE_STOPPED)   // ���������ֹͣ״̬������״̬����Ϊ����״̬
		//	StartService(schService, 0, NULL);   //��������
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

		CloseServiceHandle(schSCManager);   // �رշ�����
		CloseServiceHandle(schService);

		if (!ret) return GetLastError();
		if (ret == 2) return ERROR_SERVICE_REQUEST_TIMEOUT;
		return ERROR_SUCCESS;

	}




}