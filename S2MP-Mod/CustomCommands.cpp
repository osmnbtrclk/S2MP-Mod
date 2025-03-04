#include "pch.h"
#include "CustomCommands.hpp"
#include "Console.h"
#include "FuncPointers.h"
#include <array>

uintptr_t CustomCommands::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;
uintptr_t CustomCommands::rawBase = (uintptr_t)GetModuleHandle(NULL);
bool CustomCommands::isGodmode = false;

void CustomCommands::toggleGodmode() {
	int* health = (int*)(rawBase + 0xA0C740C);
	if (CustomCommands::isGodmode) {
		*health = 100;
		Console::print("God: OFF");
	}
	else {
		*health = -1;
		Console::print("God: ON");
	}
	CustomCommands::isGodmode = !CustomCommands::isGodmode;
}