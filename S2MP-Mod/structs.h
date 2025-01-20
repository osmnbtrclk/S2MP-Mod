#pragma once
struct CmdText
{
    unsigned __int8* data;
    int maxsize;
    int cmdsize;
};

enum LocalClientNum_t : __int32
{
    LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
    LOCAL_CLIENT_0 = 0x0,
    LOCAL_CLIENT_LAST = 0x0,
    LOCAL_CLIENT_COUNT = 0x1,
};