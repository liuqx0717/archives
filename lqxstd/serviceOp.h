#include "stdafx.h"

#ifndef _LQXSTD_SERVICEOP_
#define _LQXSTD_SERVICEOP_


#include <Windows.h>

namespace lqx {

	//ERROR_ACCESS_DENIED The handle does not have the SERVICE_START access right.
	//ERROR_INVALID_HANDLE The handle is invalid.
	//ERROR_PATH_NOT_FOUND The service binary file could not be found.
	//ERROR_SERVICE_ALREADY_RUNNING An instance of the service is already running.
	//ERROR_SERVICE_DATABASE_LOCKED The database is locked.
	//ERROR_SERVICE_DEPENDENCY_DELETED The service depends on a service that does not exist or has been marked for deletion.
	//ERROR_SERVICE_DEPENDENCY_FAIL The service depends on another service that has failed to start.
	//ERROR_SERVICE_DISABLED The service has been disabled.
	//ERROR_SERVICE_LOGON_FAILED The service did not start due to a logon failure. This error occurs if the service is configured to run under an account that does not have the "Log on as a service" right.
	//ERROR_SERVICE_MARKED_FOR_DELETE The service has been marked for deletion.
	//ERROR_SERVICE_NO_THREAD A thread could not be created for the service.
	//ERROR_SERVICE_REQUEST_TIMEOUT 
	//ERROR_SERVICE_NOT_ACTIVE  关闭一个本来已经关闭的服务时
	//返回值如上
	DWORD ChangeServiceStatusA(const char *Name, bool Start, int TimeOut/*单位：秒*/);
	DWORD ChangeServiceStatusW(const wchar_t *Name, bool Start, int TimeOut/*单位：秒*/);


}






#endif