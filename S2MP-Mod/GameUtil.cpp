#include "pch.h"
#include "GameUtil.hpp"
#include "FuncPointers.h"
#include "Console.h"
#include <sstream>
#include <algorithm>
typedef unsigned int    uint32;
#define _DWORD uint32

void GameUtil::Cbuf_AddText(LocalClientNum_t localClientNum, std::string text) {
    Console::print("GameUtil::Cbuf_AddText(" + std::to_string(localClientNum) + ", " + text + ")");
    uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
    uintptr_t cmd_textArrayAddr = base + 0xAC674B8; //adjusted for 0x1000 offset

    //Functions::_Sys_EnterCriticalSection(193);
    //v2 = &(&cmd_textArray)[2 * v1];
    //v3 = *((int*)v2 + 3);
    //if ((int)v3 + 20 < *((_DWORD*)v2 + 2))
    //{
    //    strcpy(&(*v2)[v3], "exec default_mp.cfg\n");
    //    *((_DWORD*)v2 + 3) += 20;
    //}
    //Functions::_Sys_LeaveCriticalSection(193);
}

std::string GameUtil::getAddressAsString(void* address) {
    std::stringstream ss;
    ss << address;
    return ss.str();
}

char GameUtil::asciiToLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

bool GameUtil::stringToBool(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), GameUtil::asciiToLower);

    return (lowerStr == "1" || lowerStr == "true");
}