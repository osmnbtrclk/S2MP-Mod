#include "pch.h"
#include "Console.h"
#include "DebugPatches.hpp"
#include "GameUtil.hpp"
#include <MinHook.h>
#include <Windows.h>
#include <array>
#include <sstream>
#include <winternl.h>
#include <tlhelp32.h>


std::string DebugPatches::conLabel = "DP";
uintptr_t DebugPatches::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;


using CheckRemoteDebuggerPresent_t = BOOL(WINAPI*)(HANDLE, PBOOL);
CheckRemoteDebuggerPresent_t fpOriginalCheckRemoteDebuggerPresent = nullptr;

BOOL WINAPI HookedCheckRemoteDebuggerPresent(HANDLE hProcess, PBOOL pbDebuggerPresent) {
    if (pbDebuggerPresent) {
        *pbDebuggerPresent = FALSE;
    }
    Console::print("CheckRemoteDebuggerPresent");
    return TRUE;
}

// Function pointer for the original GetThreadContext
using GetThreadContext_t = BOOL(WINAPI*)(HANDLE, LPCONTEXT);
GetThreadContext_t fpOriginalGetThreadContext = nullptr;

BOOL WINAPI HookedGetThreadContext(HANDLE hThread, LPCONTEXT lpContext) {
    if (fpOriginalGetThreadContext && lpContext) {
        BOOL result = fpOriginalGetThreadContext(hThread, lpContext);


        lpContext->Dr0 = 0;
        lpContext->Dr1 = 0;
        lpContext->Dr2 = 0;
        lpContext->Dr3 = 0;
        lpContext->Dr6 = 0;
        lpContext->Dr7 = 0;

        Console::print("GetThreadContext Hooked - Debug registers cleared");
        return result;
    }
    return FALSE;
}

//IsDebuggerPresent
typedef BOOL(WINAPI* IsDebuggerPresent_t)();
IsDebuggerPresent_t fpOriginalIsDebuggerPresent = nullptr;


BOOL WINAPI HookedIsDebuggerPresent() {
    Console::print("IsDebuggerPresent");
    return FALSE;
}



void DebugPatches::init() {
	Console::infoPrint("DebugPatches::init()");

    MH_CreateHook(GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent"), &HookedIsDebuggerPresent, reinterpret_cast<LPVOID*>(&fpOriginalIsDebuggerPresent));
    MH_EnableHook(GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent"));

    MH_CreateHook(GetProcAddress(GetModuleHandleA("kernel32.dll"), "CheckRemoteDebuggerPresent"), &HookedCheckRemoteDebuggerPresent, reinterpret_cast<LPVOID*>(&fpOriginalCheckRemoteDebuggerPresent));
    MH_EnableHook(GetProcAddress(GetModuleHandleA("kernel32.dll"), "CheckRemoteDebuggerPresent"));

    void* gtcAddr = reinterpret_cast<void*>(GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetThreadContext"));
    if (gtcAddr) {
        MH_CreateHook(gtcAddr, &HookedGetThreadContext, reinterpret_cast<LPVOID*>(&fpOriginalGetThreadContext));
        MH_EnableHook(gtcAddr);
    }


}
