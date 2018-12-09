#include "stdafx.h"

#ifndef _OTHERS_H
#define _OTHERS_H

#include <Windows.h>

namespace lqx {

	inline char *formatmsg(DWORD msgid) {
		char *str;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, msgid, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&str, 0, NULL);
		return str;
	}











}

#endif