#pragma once

#include "Base.h"

/*
GameFucntion:
Класс для хранения и поиска указателей на функции.

Parameters:
initial_address - начало поиска
search_length - область поиска
byte - искомая последовательность байтов
byte_lenght - размер массива с байтами
mask - маска (1 = XX, 0 = ??)

Remarks:
*/

class GameFunction
{
public:
	GameFunction();
	GameFunction(BYTE* byte, int byte_lenght, BYTE* mask);
	GameFunction(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask);

	DWORD_PTR GetAddress() const; // Получает адрес функции
	BOOL Valid() const;

	operator bool() const
	{
		return Valid();
	}

private:
	void CommonInit(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask);

	DWORD_PTR		m_Pointer;
};

