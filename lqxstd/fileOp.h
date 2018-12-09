#include "stdafx.h"

#ifndef _FILEOP_H_
#define _FILEOP_H_

#include <functional>
#include <io.h>
#include <string>

namespace lqx {

	enum enumflags {
		ENUM_FILE = 1,
		ENUM_DIR,
		ENUM_BOTH
	};

	bool enumsubfiles(

		const std::wstring &dir_with_back_slant,        //for example: L"C:\\", L"E:\\test\\"
		const std::wstring &filename,                   //for example: L"*", L"123.txt", L"*.exe", L"123.???"
		unsigned int maxdepth,                 //0 means not searching subdirectories, 1 means maximum depth of subdirectories is 1,
											   //    pass -1 to search all the subdirectories.
		enumflags flags,                       //search files, directories, or both.
		std::function<bool(const std::wstring &dir_with_back_slant, _wfinddata_t &attrib)> callback
	);
}


#endif

/*

int _tmain(int argc, _TCHAR* argv[])
{

	//the default code page of my console window is 936
	setlocale(CP_ACP, ".936");

	enumsubfiles(L"C:\\", L"*.exe", 1, ENUM_FILE,[](const std::wstring &dir_with_back_slant, _wfinddata_t &attrib)->bool
	{
		std::wcout << dir_with_back_slant << attrib.name << '\n';
		return true;          //return true to continue, return false to abort searching.
	});




	return 0;
}


*/