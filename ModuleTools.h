#pragma once

#include "Base.h"

DWORD GetModuleSizeFromHeaders(HMODULE hModule);
DWORD GetModuleBaseOfCode(HMODULE hModule);
DWORD GetModuleSizeOfCode(HMODULE hModule);
DWORD GetModuleSize(LPSTR strModuleName);