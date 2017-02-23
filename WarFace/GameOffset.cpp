#include "GameOffset.h"
#include "ModuleTools.h"
#include "MemoryTools.h"

GameOffset::GameOffset()
{
	m_Pointer = NULL ^ XOR_POINTER;
	m_Offset = NULL ^ XOR_OFFSET;
	m_Type = 0;
}

GameOffset::GameOffset(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset)
{
	CommonInit((DWORD_PTR)GetModuleHandle(NULL), 0, byte, byte_lenght, mask, offset, OFFSET_DWORD);
}

GameOffset::GameOffset(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset, int type)
{
	CommonInit((DWORD_PTR)GetModuleHandle(NULL), 0, byte, byte_lenght, mask, offset, type);
}

GameOffset::GameOffset(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset)
{
	CommonInit(initial_address, search_length, byte, byte_lenght, mask, offset, OFFSET_DWORD);
}

GameOffset::GameOffset(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset, int type)
{
	CommonInit(initial_address, search_length, byte, byte_lenght, mask, offset, type);
}

__declspec(noinline)
DWORD_PTR GameOffset::GetAddress() const
{
	return XOR_POINTER ^ m_Pointer;
}

__declspec(noinline)
DWORD GameOffset::GetOffset() const
{
	if(GetAddress())
	{
		switch(m_Type)
		{
		case OFFSET_BYTE:
			return *(BYTE*)(GetAddress() + (XOR_OFFSET ^ m_Offset));
		case OFFSET_WORD:
			return *(WORD*)(GetAddress() + (XOR_OFFSET ^ m_Offset));
		case OFFSET_DWORD:
			return *(DWORD*)(GetAddress() + (XOR_OFFSET ^ m_Offset));
		default:
			break;
		}
	}
	return NULL;
}

BOOL GameOffset::Valid() const
{
	return GetAddress() != 0;
}

__declspec(noinline)
void GameOffset::CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset, int type)
{
	m_Pointer = NULL ^ XOR_POINTER;
	m_Offset = offset ^ XOR_OFFSET;
	m_Type = type;

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