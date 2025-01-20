#pragma once
#include <string>
#include <vector>
#include "structs.h"
class GameUtil {
public:
	static void Cbuf_AddText(LocalClientNum_t localClientNum, const char* text);
};