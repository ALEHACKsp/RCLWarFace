#pragma once

#include "Base.h"

DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bByte, BYTE* bMask, int MaskLen);
bool bCompare(const BYTE* pData, const BYTE* bByte, const BYTE* bMask, int MaskLen);
void* DetourFunction(BYTE *src, const BYTE *dst, const int len);
void DetourCreate(BYTE *src, const BYTE *dst, const int len);
void MEMwrite(DWORD adr, char* ptr, int size);
