// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS

#define ROOT "C:\\��Ȩ��\\����\\"

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


#include <stdio.h>
#include <tchar.h>




// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
