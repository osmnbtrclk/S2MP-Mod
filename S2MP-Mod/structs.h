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

//from iw6, double check for s2
struct dvar_t
{
    const char* name;
    unsigned int flags;
    unsigned __int8 type;
    bool modified;
    DvarValue current;
    DvarValue latched;
    DvarValue reset;
    DvarLimits domain;
    bool(__fastcall* domainFunc)(dvar_t*, DvarValue);
    dvar_t* hashNext;
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