#include "pch.h"
#include "Console.h"
#include "PrintPatches.hpp"
#include <MinHook.h>

uintptr_t PrintPatches::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;

typedef void (*FS_Startup)(const char* str);
FS_Startup _FS_Startup = nullptr;


void FS_Startup_Hook(const char* str) {
	Console::print("----- FS_Startup -----");
	Console::print("----- FS_Startup: " + std::string(str) + " -----");
	_FS_Startup(str);
}




void PrintPatches::init() {
	Console::infoPrint("PrintPatches::init()");
	//FS_Startup
	MH_CreateHook(reinterpret_cast<void*>(base + 0x7BE630), reinterpret_cast<void*>(&FS_Startup_Hook), reinterpret_cast<void**>(&_FS_Startup));
	MH_EnableHook(reinterpret_cast<void*>(base + 0x7BE630));

}
