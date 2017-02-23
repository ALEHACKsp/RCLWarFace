#include "GamePointer.h"
#include "ModuleTools.h"
#include "MemoryTools.h"

GamePointer::GamePointer()
{
	m_Pointer = NULL ^ XOR_POINTER;
	m_Offset = NULL ^ XOR_OFFSET;
}

GamePointer::GamePointer(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset)
{
	CommonInit((DWORD_PTR)GetModuleHandle(NULL), 0, byte, byte_lenght, mask, offset);
}

GamePointer::GamePointer(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset)
{
	CommonInit(initial_address, search_length, byte, byte_lenght, mask, offset);
}

__declspec(noinline)
DWORD_PTR GamePointer::GetAddress() const
{
	return XOR_POINTER ^ m_Pointer;
}

__declspec(noinline)
DWORD_PTR GamePointer::GetValue() const
{
	if(GetAddress())
	{
		DWORD offset = *(DWORD_PTR*)(GetAddress() + (XOR_OFFSET ^ m_Offset));
		if(offset)
			return *(DWORD_PTR*)offset;
	}
	return NULL;
}

BOOL GamePointer::Valid() const
{
	return GetAddress() != 0;
}

__declspec(noinline)
void GamePointer::CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset)
{
	m_Pointer = NULL ^ XOR_POINTER;
	m_Offset = offset ^ XOR_OFFSET;

	if(!initial_address || !byte || !byte_lenght || !mask)
		return;

	if(!search_length)
	{
		search_length = GetModuleSizeFromHeaders((HMODULE)initial_address);
		if(!search_length)
			return;
	}

	m_Pointer = FindPattern(initial_address, search_length, byte, mask, byte_lenght) ^ XOR_POINTER;
}