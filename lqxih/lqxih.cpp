// lqxih.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"


PIMAGE_DOS_HEADER         pDosHeader;
PIMAGE_NT_HEADERS         pNTHeaders;
PIMAGE_OPTIONAL_HEADER    pOptHeader;
PIMAGE_IMPORT_DESCRIPTOR  pImportDescriptor;
PIMAGE_THUNK_DATA         pThunkData;
PIMAGE_IMPORT_BY_NAME     pImportByName;
HMODULE hMod;


HANDLE * addr;        //���溯������ڵ�ַ
HANDLE * myaddr;
extern HMODULE hk;

// ����MessageBoxA����ԭ��
typedef HANDLE(WINAPI *PFNOPENPROCESS)(DWORD, BOOL, DWORD);
HANDLE WINAPI OpenProcessProxy(IN DWORD a, IN BOOL b, IN DWORD c);


void ThreadProc(void *param);

//�̺߳������޸�IAT��ַ

void ThreadProc(void *param)
{
	addr = (HANDLE *)GetProcAddress(hk, "OpenProcess");
	myaddr = (HANDLE *)OpenProcessProxy;
	if (addr == NULL) MessageBoxA(NULL, "hk=NULL", "hook", 16);
	hMod = GetModuleHandle(NULL);
	//------------hook api----------------
	pDosHeader = (PIMAGE_DOS_HEADER)hMod;
	pNTHeaders = (PIMAGE_NT_HEADERS)((BYTE *)hMod + pDosHeader->e_lfanew);
	pOptHeader = (PIMAGE_OPTIONAL_HEADER)&(pNTHeaders->OptionalHeader);

	pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE *)hMod + pOptHeader->DataDirectory[1].VirtualAddress);

	while (pImportDescriptor->FirstThunk)
	{
		char * dllname = (char *)((BYTE *)hMod + pImportDescriptor->Name);

		pThunkData = (PIMAGE_THUNK_DATA)((BYTE *)hMod + pImportDescriptor->OriginalFirstThunk);

		int no = 1;
		while (pThunkData->u1.Function)
		{
			char * funname = (char *)((BYTE *)hMod + (DWORD)pThunkData->u1.AddressOfData + 2);
			PDWORD lpAddr = (DWORD *)((BYTE *)hMod + (DWORD)pImportDescriptor->FirstThunk) + (no - 1);

			//�޸��ڴ�Ĳ���
			if ((*lpAddr) == (int)addr)
			{
				//�޸��ڴ�ҳ������
				DWORD dwOLD;
				MEMORY_BASIC_INFORMATION  mbi;
				VirtualQuery(lpAddr, &mbi, sizeof(mbi));
				VirtualProtect(lpAddr, sizeof(DWORD), PAGE_READWRITE, &dwOLD);
				SIZE_T w;//test
				WriteProcessMemory(GetCurrentProcess(),
					lpAddr, &myaddr, sizeof(DWORD), &w);    //�˴����޸���IAT�ĵ�ַΪ�����Լ����庯���ĵ�ַ
				if (w == NULL) MessageBoxW(NULL, L"failed.", L"failed.", 64);

				//�ָ��ڴ�ҳ������
				VirtualProtect(lpAddr, sizeof(DWORD), dwOLD, 0);
			}
			//---------
			no++;
			pThunkData++;
		}

		pImportDescriptor++;
	}
	MessageBoxA(NULL, "hooked.", "hook", 64);
	//-------------------HOOK END-----------------
}

//new messagebox function
HANDLE WINAPI OpenProcessProxy(IN DWORD a, IN BOOL b, IN DWORD c)
{
	MessageBoxA(NULL, "myaddr", "hook", 64);
	if (c == 27012) {
		return ((PFNOPENPROCESS)addr)(a, b, 26860);
	}
	else {
		return ((PFNOPENPROCESS)addr)(a, b, c);
	}
	//����ط�����д�������API�����Ĵ������
}