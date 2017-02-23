#pragma once

#include "Base.h"

/*
GameFucntion:
����� ��� �������� � ������ ���������� �� �������.

Parameters:
initial_address - ������ ������
search_length - ������� ������
byte - ������� ������������������ ������
byte_lenght - ������ ������� � �������
mask - ����� (1 = XX, 0 = ??)

Remarks:
*/

class GameFunction
{
public:
	GameFunction();
	GameFunction(BYTE* byte, int byte_lenght, BYTE* mask);
	GameFunction(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask);

	DWORD_PTR GetAddress() const; // �������� ����� �������
	BOOL Valid() const;

	operator bool() const
	{
		return Valid();
	}

private:
	void CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask);

	DWORD_PTR		m_Pointer;
};

