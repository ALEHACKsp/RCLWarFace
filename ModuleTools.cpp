#include "ModuleTools.h"

#include <psapi.h>
#include <TlHelp32.h>

DWORD GetModuleSizeFromHeaders(HMODULE hModule)
{
	if(!hModule)
		return 0;

	PIMAGE_DOS_HEADER       pImage_Dos_Header = PIMAGE_DOS_HEADER(hModule);
	PIMAGE_NT_HEADERS       pImage_PE_Header = PIMAGE_NT_HEADERS(long(hModule) + pImage_Dos_Header->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pImage_Optional_Header = &pImage_PE_Header->OptionalHeader;

	return pImage_Optional_Header->SizeOfCode + pImage_Optional_Header->SizeOfInitializedData;
}

DWORD GetModuleBaseOfCode(HMODULE hModule)
{
	if(!hModule)
		return 0;

	PIMAGE_DOS_HEADER       pImage_Dos_Header = PIMAGE_DOS_HEADER(hModule);
	PIMAGE_NT_HEADERS       pImage_PE_Header = PIMAGE_NT_HEADERS(long(hModule) + pImage_Dos_Header->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pImage_Optional_Header = &pImage_PE_Header->OptionalHeader;

	return pImage_Optional_Header->BaseOfCode;
}

DWORD GetModuleSizeOfCode(HMODULE hModule)
{
	if(!hModule)
		return 0;

	PIMAGE_DOS_HEADER       pImage_Dos_Header = PIMAGE_DOS_HEADER(hModule);
	PIMAGE_NT_HEADERS       pImage_PE_Header = PIMAGE_NT_HEADERS(long(hModule) + pImage_Dos_Header->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pImage_Optional_Header = &pImage_PE_Header->OptionalHeader;

	return pImage_Optional_Header->SizeOfCode;
}

DWORD GetModuleSize(PTCHAR strModuleName)
{
	MODULEENTRY32	lpme = { 0 };
	DWORD			dwSize = 0;
	DWORD			PID = GetCurrentProcessId();
	BOOL			isMod = 0;
	wchar_t			chModName[256];

	wcsncpy(chModName, strModuleName, sizeof(chModName));
	wcslwr(chModName);

	HANDLE hSnapshotModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	if(hSnapshotModule)
	{
		lpme.dwSize = sizeof(lpme);
		isMod = Module32First(hSnapshotModule, &lpme);
		while(isMod)
		{
			if(wcscmp(lpme.szExePath, chModName))
			{
				dwSize = (DWORD)lpme.modBaseSize;
				CloseHandle(hSnapshotModule);
				return dwSize;
			}
			isMod = Module32Next(hSnapshotModule, &lpme);
		}
	}
	CloseHandle(hSnapshotModule);

	return 0;
}