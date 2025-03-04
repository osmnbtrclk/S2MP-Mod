#include "pch.h"
#include "FuncPointers.h"
//IDA Base: 0x7FF731281000
//Offset = base + (IDA Addr - IDA Base)
uintptr_t base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;
Functions::Sys_EnterCriticalSection Functions::_Sys_EnterCriticalSection = (Functions::Sys_EnterCriticalSection)(base + 0x7D6B50);
Functions::Sys_LeaveCriticalSection Functions::_Sys_LeaveCriticalSection = (Functions::Sys_LeaveCriticalSection)(base + 0x7D6BC0);
Functions::Sys_Cwd Functions::_Sys_Cwd = (Functions::Sys_Cwd)(base + 0x7D6980);
Functions::Dvar_FindVar Functions::_Dvar_FindVar = (Functions::Dvar_FindVar)(base + 0x108C30);
Functions::SEH_SafeTranslateString Functions::_SEH_SafeTranslateString = (Functions::SEH_SafeTranslateString)(base + 0x7934D0);
Functions::SEH_StringEd_GetString Functions::_SEH_StringEd_GetString = (Functions::SEH_StringEd_GetString)(base + 0x793520);

