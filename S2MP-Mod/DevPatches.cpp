//Development Patches
//temporary patches for testing stuff

#include "pch.h"
#include "DevPatches.hpp"
#include "Console.h"
#include "Hook.hpp"
#include "FuncPointers.h"

uintptr_t DevPatches::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;

char* SEH_StringEd_GetString(const char* pszReference) {
	Console::labelPrint("[LOC]", std::string(pszReference));
	return Functions::_SEH_StringEd_GetString(pszReference);
}

void DevPatches::init() {
	Console::infoPrint("DevPatches::init()");
	//Hook::installHook((void*)(base + 0x7934D9), SEH_StringEd_GetString);
}