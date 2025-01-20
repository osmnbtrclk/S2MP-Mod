#include "pch.h"
#include "FuncPointers.h"
//IDA Base: 0x7FF731281000 
//Offset = base + (IDA Addr - IDA Base)
uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
Functions::Sys_EnterCriticalSection Functions::_Sys_EnterCriticalSection = (Functions::Sys_EnterCriticalSection)(base + 0x7D6B50);
Functions::Sys_LeaveCriticalSection Functions::_Sys_LeaveCriticalSection = (Functions::Sys_LeaveCriticalSection)(base + 0x7D6BC0);

