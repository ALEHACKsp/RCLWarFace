#include "GameFunction.h"
#include "ModuleTools.h"
#include "MemoryTools.h"

GameFunction::GameFunction()
{
	m_Pointer = NULL ^ XOR_POINTER;
}

GameFunction::GameFunction(BYTE* byte, int byte_lenght, BYTE* mask)
{
	CommonInit((DWORD_PTR)GetModuleHandle(NULL), 0, byte, byte_lenght, mask);
}

GameFunction::GameFunction(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask)
{
	CommonInit(initial_address, search_length, byte, byte_lenght, mask);
}

__declspec(noinline)
DWORD_PTR GameFunction::GetAddress() const
{
	return XOR_POINTER ^ m_Pointer;
}

BOOL GameFunction::Valid() const
{
	return GetAddress() != 0;
}

__declspec(noinline)
void GameFunction::CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask)
{
	m_Pointer = NULL ^ XOR_POINTER;

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