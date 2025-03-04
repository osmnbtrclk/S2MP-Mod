#pragma once
#include <string>
class CustomCommands {
public:
	static uintptr_t base;
	static uintptr_t rawBase;
	static void toggleGodmode();
private:
	static bool isGodmode;
};