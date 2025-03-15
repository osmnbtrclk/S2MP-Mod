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

enum errorParm_t
{
    ERR_FATAL = 0x0,
    ERR_DROP = 0x1,
    ERR_SERVERDISCONNECT = 0x2,
    ERR_DISCONNECT = 0x3,
    ERR_SCRIPT = 0x4,
    ERR_SCRIPT_DROP = 0x5,
    ERR_LOCALIZATION = 0x6,
    ERR_MAPLOADERRORSUMMARY = 0x7,
};

struct DvarLimits_integer
{
    int min;
    int max;
};

struct DvarLimits_value
{
    float min;
    float max;
};

union DvarLimits
{
    DvarLimits_integer integer;
    DvarLimits_value floats;
};


enum dvarType_t
{
    DVAR_TYPE_FLOAT = 0xB,
};

union DvarValue
{
    bool enabled;
    int integer;
    unsigned int unsignedInt;
    float value;
    float vector[4];
    const char* string;
    unsigned __int8 color[4];
};

struct dvar_t {
    char* name;
    char padding[8]; //8 bytes of stuff i dont care about
    DvarValue current;
};

//making this from scratch
struct playerState_s
{
    int commandTime;
    int pm_type;
    int pm_time;
    int pm_flags;
    int otherFlags;
    int linkFlags;
    int bobCycle;
    float origin[3];
    float velocity[3];
    //more...
};