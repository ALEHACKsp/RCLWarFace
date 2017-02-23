#pragma once

#include "Base.h"

/*
GamePointer:
Класс для хранения и поиска указателей на переменные.

Parameters:
initial_address - начало поиска
search_length - область поиска
byte - искомая последовательность байтов
byte_lenght - размер массива с байтами
mask - маска (1 = XX, 0 = ??)
offset - смещение для чтения указателя *(DWORD_PTR*)(m_Pointer + offset)

Remarks:
Не предназначен для поиска функций и прочей фигни, только получение адреса переменных и значений в них.
*/

class GamePointer
{
public:
	GamePointer();
	GamePointer(BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);
	GamePointer(DWORD_PTR initial_address, DWORD search_length, BYTE* byte, int byte_lenght, BYTE* mask, DWORD offset);

	DWORD_PTR GetAddress() const; // Получает адрес читаемой переменной в памяти
	DWORD_PTR GetValue() const; // Получает значение переменной в читаемом адресе
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

