// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS

#define ROOT "C:\\刘权兴\\代码\\"

#ifdef _DEBUG
#ifdef _WIN64
#define LL ROOT "lqxstd\\x64\\Debug\\lqxstd.lib"
#define LD ROOT "sydll\\x64\\Debug\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X64\\detours.lib"
#define HAD ROOT "ha\\x64\\Debug\\ha.dll"
#else
#define LL ROOT "lqxstd\\Debug\\lqxstd.lib"
#define LD ROOT "sydll\\Debug\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X86\\detours.lib"
#define HAD ROOT "ha\\Debug\\ha.dll"
#endif
#else
#ifdef _WIN64
#define LL ROOT "lqxstd\\x64\\Release\\lqxstd.lib"
#define LD ROOT "sydll\\x64\\Release\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X64\\detours.lib"
#define HAD ROOT "ha\\x64\\Release\\ha.dll"
#else
#define LL ROOT "lqxstd\\Release\\lqxstd.lib"
#define LD ROOT "sydll\\Release\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X86\\detours.lib"
#define HAD ROOT "ha\\Release\\ha.dll"
#endif
#endif


#include <stdio.h>
#include <tchar.h>


#define MS_EXIT 1
#define MS_LOADDLLA 2
#define MS_LOADDLLW 3
#define MS_PID_ALL 0
#define MS_PID_DEBUG -1

#define T_START 1
#define T_STOP 2

#define SHARED_MEM_BUFFSIZE 10240