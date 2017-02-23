#pragma once

#include "Base.h"

/*
GameOffset:
 ласс дл€ хранени€ и поиска смещений в классах.

Parameters:
initial_address - начало поиска
search_length - область поиска
byte - искома€ последовательность байтов
byte_lenght - размер массива с байтами
mask - маска (1 = XX, 0 = ??)
offset - смещение дл€ чтени€ указател€ *(DWORD_PTR*)(m_Pointer + offset)

Remarks:
Ќе предназначен дл€ поиска функций и прочей фигни.
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

	DWORD_PTR GetAddress() const; // ѕолучает адрес читаемой переменной в пам€ти
	DWORD GetOffset() const; // ѕолучает смещение
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
