#pragma once

#include "Base.h"

/*
GamePointer:
����� ��� �������� � ������ ���������� �� ����������.

Parameters:
initial_address - ������ ������
search_length - ������� ������
byte - ������� ������������������ ������
byte_lenght - ������ ������� � �������
mask - ����� (1 = XX, 0 = ??)
offset - �������� ��� ������ ��������� *(DWORD_PTR*)(m_Pointer + offset)

Remarks:
�� ������������ ��� ������ ������� � ������ �����, ������ ��������� ������ ���������� � �������� � ���.
*/

class GamePointer
{
public:
	GamePointer();
	GamePointer(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);
	GamePointer(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);

	DWORD_PTR GetAddress() const; // �������� ����� �������� ���������� � ������
	DWORD_PTR GetValue() const; // �������� �������� ���������� � �������� ������
	BOOL Valid() const;

	operator bool() const
	{
		return Valid();
	}

private:
	void CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);

	DWORD_PTR		m_Pointer;
	DWORD			m_Offset;
};

