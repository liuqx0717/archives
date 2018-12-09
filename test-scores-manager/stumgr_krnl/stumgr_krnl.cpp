// stumgr_krnl.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include <tchar.h>
#include <fstream>
#include "md5.h"
#include "stumgr_krnl.h"


using std::fstream;
using std::ios;

FileHeader header;
fstream file;
bool file_opened=false;


extern "C" __declspec(dllexport) ErrorType __stdcall OpenDataFile(
	__in TCHAR *filename,
	__in TCHAR *password,
	__out int *nSubject,
	__out int *nStudent
	)
{
	if (file_opened) file.close();
	MD5 md5;
	file.open(filename,ios::in|ios::binary);
	if (!file) return FILE_ERROR;
	file.read((char*)&header, sizeof(FileHeader));
	if (!file) return FILE_ERROR;
	md5.update(password);
	md5.digest();

	*nSubject = header.nSubject;
	*nStudent = header.nStudent;
	file_opened = true;
	if (md5.toString().compare(header.PasswordDigest))
		return INCORRECT_PASSWORD;
	return SUCCEEDED;
}

extern "C" __declspec(dllexport) ErrorType __stdcall LoadDataFile(
	__out char *SubjectNames,
	__out StudentInfo *StudentInfos,
	__out float *scores
	)
{
	if (!file_opened) return FILE_ERROR;
	file.read(SubjectNames, MAX_SUBJECT_WIDTH*header.nSubject);
	if (!file) return FILE_ERROR;
	file.read((char*)StudentInfos, sizeof(StudentInfo)*header.nStudent);
	if (!file) return FILE_ERROR;
	file.read((char*)scores, sizeof(float)*header.nStudent*header.nSubject);
	if (!file) return FILE_ERROR;
	file.close();
	return SUCCEEDED;
}

extern "C" __declspec(dllexport) ErrorType __stdcall SaveDataFile(
	__in TCHAR *filename,
	__in int nSubject,
	__in int nStudent,
	__in char *password,
	__in TCHAR *SubjectNames,
	__in StudentInfo *StudentInfos,
	__in float *scores
	)
{
	FileHeader header;
	MD5 md5;
	int i;
	fstream file(filename, ios::binary | ios::out | ios::trunc);
	if (!file) return FILE_ERROR;
	md5.update(password);
	md5.digest();
	header.nStudent = nStudent;
	header.nSubject = nSubject;
	strcpy(header.PasswordDigest, md5.toString().c_str());
	file.write((char*)&header, sizeof(FileHeader));
	file.write((char*)SubjectNames, nSubject*MAX_SUBJECT_WIDTH);
	file.write((char*)StudentInfos, sizeof(StudentInfo)*nStudent);
	file.write((char*)scores, sizeof(float)*nStudent*nSubject);
	if (!file) return FILE_ERROR;
	return SUCCEEDED;
}
