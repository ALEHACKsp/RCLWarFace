#include "Exceptions.h"

#include "MemoryTools.h"
#include "ModuleTools.h"
#include "Distormx/distormx.h"

PBYTE g_KiUserExceptionDispatcher;

#include <iostream>

void _stdcall UserExceptionHandler(PEXCEPTION_RECORD pExcptRec, PCONTEXT pContext)
{
	char ExceptionMessage[500];
	PVOID address = pExcptRec->ExceptionAddress;
	if(HMODULE ocevogyv = GetModuleHandleA("ocevogyv.dll"))
	{
		DWORD base = GetModuleBaseOfCode(ocevogyv);
		DWORD size = GetModuleSizeOfCode(ocevogyv);
		if(base < (DWORD)address && (DWORD)address > base + size)
			return;
	}

	sprintf(ExceptionMessage, "ExceptionCode = 0x%X\nExceptionFlags = 0x%X\nExceptionAddress = 0x%X",
			pExcptRec->ExceptionCode, pExcptRec->ExceptionFlags, pExcptRec->ExceptionAddress);
	MessageBoxA(NULL, ExceptionMessage, "Exception!", NULL);

	ExitProcess(0);
}

__declspec(naked)
void HookKiUserExceptionDispatcher()
{
	__asm
	{
 		cld
		mov ecx, [esp + 0x4]
 		mov ebx, [esp]
		pushad
		push ecx
		push ebx
		call UserExceptionHandler
		popad
		jmp g_KiUserExceptionDispatcher
	}
}

bool SetHookKiUserExceptionDispatcher()
{
	HMODULE ntdll = GetModuleHandleA("ntdll.dll");
	if(!ntdll)
		return false;

	FARPROC pKiUserExceptionDispatcher = GetProcAddress(ntdll, "KiUserExceptionDispatcher");
	if(!pKiUserExceptionDispatcher)
		return false;

	DetourCreate((PBYTE)pKiUserExceptionDispatcher, (PBYTE)HookKiUserExceptionDispatcher, 5);
	g_KiUserExceptionDispatcher = (PBYTE)pKiUserExceptionDispatcher + 5;

	return true;
}