#include "MemoryTools.h"

DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bByte, BYTE* bMask, int MaskLen)
{
	for(DWORD i = 0; i < dwLen; i++)
		if(bCompare((BYTE*)(dwAddress + i), bByte, bMask, MaskLen))
			return (DWORD)(dwAddress + i);

	return 0;
}

bool bCompare(const BYTE* pData, const BYTE* bByte, const BYTE* bMask, int MaskLen)
{
	for(int i = 0; i < MaskLen; bMask++, pData++, bByte++, i++)
	{
		if(*bMask == 0)
			continue;

		if(*pData != *bByte)
			return false;
	}

	return true;
}

void* DetourFunction(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp;
	DWORD dwback;
	DWORD jumpto, newjump;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwback);

	if(src[0] == 0xE9)
	{
		jmp = (BYTE*)malloc(10);
		jumpto = (*(DWORD*)(src + 1)) + ((DWORD)src) + 5;
		newjump = (jumpto - (DWORD)(jmp + 5));
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = newjump;
		jmp += 5;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = (DWORD)(src - jmp);
	}
	else
	{
		jmp = (BYTE*)malloc(5 + len);
		memcpy(jmp, src, len);
		jmp += len;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	}
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

	for(int i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwback, &dwback);
	return (jmp - len);
}

void DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
	DWORD dwback;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwback);
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
	VirtualProtect(src, len, dwback, &dwback);
}

void MEMwrite(DWORD adr, char* ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect((void *)(adr), size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy((void *)(adr), ptr, size);
	VirtualProtect((void *)(adr), size, OldProtection, &OldProtection);
}