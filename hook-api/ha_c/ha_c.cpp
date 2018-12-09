// ha_c.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include <lqxstd/procOp.h>
#include <lqxstd/memshare.h>
#pragma comment(lib,LL)

using std::cout;
using std::cin;
using std::string;


lqx::memshare ms;
lqx::memshare ms_g;

void e(int n, int w, int lh, int ll)
{
	char str1[500];
	wchar_t wstr1[500];
	switch (n)
	{
	case MS_LOADDLLA:
		ms.read(0, 499, (void*)str1);
		cout << "A  "<< str1  << '\n' ;
		break;
	case MS_LOADDLLW:
		ms.read(0, 499 * 2, (void*)wstr1);
		std::wcout << "W  " << wstr1 << '\n' ;
		break;
	default:
		break;
	}
}

void e_g(int n, int w, int lh, int ll)
{
	
}

int main()
{
	ms.init("ha", 10240, &e, false);
	ms_g.init("ha_g", 10240, &e_g,true);
	ms.wait();
    return 0;
}

