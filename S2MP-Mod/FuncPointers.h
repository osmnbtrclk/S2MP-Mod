#pragma once
//#include "Structs.h"
class Functions {
public:
	typedef void(__cdecl* Sys_EnterCriticalSection)(int critSect);
	static Sys_EnterCriticalSection _Sys_EnterCriticalSection;
	
	typedef void(__cdecl* Sys_LeaveCriticalSection)(int critSect);
	static Sys_LeaveCriticalSection _Sys_LeaveCriticalSection;
};
