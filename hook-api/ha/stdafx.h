// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#define _CRT_SECURE_NO_WARNINGS
// Windows 头文件: 
#include <windows.h>


#define ROOT "C:\\刘权兴\\代码\\"

#ifdef _DEBUG
#ifdef _WIN64
#define LL ROOT "lqxstd\\x64\\Debug\\lqxstd.lib"
#define LD ROOT "sydll\\x64\\Debug\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X64\\detours.lib"
#else
#define LL ROOT "lqxstd\\Debug\\lqxstd.lib"
#define LD ROOT "sydll\\Debug\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X86\\detours.lib"
#endif
#else
#ifdef _WIN64
#define LL ROOT "lqxstd\\x64\\Release\\lqxstd.lib"
#define LD ROOT "sydll\\x64\\Release\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X64\\detours.lib"
#else
#define LL ROOT "lqxstd\\Release\\lqxstd.lib"
#define LD ROOT "sydll\\Release\\sydll.dll"
#define DL ROOT "DetoursPro\\lib.X86\\detours.lib"
#endif
#endif

#include <lqxstd/procOp.h>
#include <lqxstd/memshare.h>
#include <detours.h>
#pragma comment(lib,LL)
#pragma comment(lib,DL)

#define MS_EXIT 1
#define MS_LOADDLLA 2
#define MS_LOADDLLW 3
#define MS_PID_ALL 0
#define MS_PID_DEBUG -1

#define T_START 1
#define T_STOP 2

#define SHARED_MEM_BUFFSIZE 10240

// TODO:  在此处引用程序需要的其他头文件
