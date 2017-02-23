#pragma once

#include "Base.h"

/*
GameOffset:
����� ��� �������� � ������ �������� � �������.

Parameters:
initial_address - ������ ������
search_length - ������� ������
byte - ������� ������������������ ������
byte_lenght - ������ ������� � �������
mask - ����� (1 = XX, 0 = ??)
offset - �������� ��� ������ ��������� *(DWORD_PTR*)(m_Pointer + offset)

Remarks:
�� ������������ ��� ������ ������� � ������ �����.
*/

class GameOffset
{
public:
	enum
	{
		OFFSET_BYTE,
		OFFSET_WORD,
		OFFSET_DWORD
	};

	GameOffset();
	GameOffset(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);
	GameOffset(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset, int type);
	GameOffset(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);
	GameOffset(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset, int type);

	DWORD_PTR GetAddress() const; // �������� ����� �������� ���������� � ������
	DWORD GetOffset() const; // �������� ��������
	BOOL Valid() const;

	operator bool() const
	{
		return Valid();
	}

private:
	void CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset, int type);

	DWORD_PTR		m_Pointer;
	DWORD			m_Offset;
	int				m_Type;
};
