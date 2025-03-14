#pragma once
#include "structs.h"
#include <string>
class DebugPatches {
public:
	static void init();
	static uintptr_t base;
	static uintptr_t rawBase;

	static std::string conLabel;
};
