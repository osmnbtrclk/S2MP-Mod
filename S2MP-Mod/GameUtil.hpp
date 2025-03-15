#pragma once
#include <string>
#include <vector>
#include "structs.h"
class GameUtil {
public:
	static void Cbuf_AddText(LocalClientNum_t localClientNum, std::string text);
	static float safeStringToFloat(const std::string& str);
	static int safeStringToInt(const std::string& str);
	static std::string getAddressAsString(void* address);
	static char asciiToLower(char in);
	static bool stringToBool(const std::string& str);
};