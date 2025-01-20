#include "pch.h"
#include "GameUtil.h"
#include "FuncPointers.h"

void GameUtil::Cbuf_AddText(LocalClientNum_t localClientNum, const char* text) {
    uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
    uintptr_t cmd_textArrayAddr = base + 0xAC664B8;

    Functions::_Sys_EnterCriticalSection(0);
    if (((*text - 80) & 0xDF) == 0 && text[1] == 48) {
        text += 2;
        //skips leading spaces
        for (localClientNum = LOCAL_CLIENT_0; *text == 32; ++text)
            ;
    }
    int v4 = 0;
    CmdText* cmd_textArray = reinterpret_cast<CmdText*>(cmd_textArrayAddr);
    CmdText* v5 = &cmd_textArray[localClientNum];
    for (const char* i = text; *i; ++v4)
        ++i;
    __int64 cmdsize = v5->cmdsize;
    if ((int)cmdsize + v4 < v5->maxsize) {
        unsigned __int8* v8 = &v5->data[cmdsize];
        __int64 v9 = v4 + 1;
        if (v4 != -1) {
            do {
                char v10 = *text;
                ++v8;
                ++text;
                *(v8 - 1) = v10;
                --v9;
            } while (v9);
        }
        v5->cmdsize += v4;
    }
    Functions::_Sys_LeaveCriticalSection(0);
}
