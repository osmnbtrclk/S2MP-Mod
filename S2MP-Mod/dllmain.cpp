#include "pch.h"
#include <Windows.h>
#include "ExtConsole.h"
#include "ExtConsoleGui.h"
#include <thread>

HMODULE hm;
//0 - CLI, 1 - GUI, 2 - BOTH
const int EXTERNAL_CONSOLE_MODE = 1;

bool checkIfSteamVersion() {
	return true;//temp
}

DWORD WINAPI extConInitWrapper(LPVOID) {
	ExtConsole::extConInit(EXTERNAL_CONSOLE_MODE);
	return NULL;
}

void ExternalConsoleGuiInitWrapper() {
	ExternalConsoleGui::init(hm, 0, NULL, 1);
}

//Right now, we can run the dll thru dllmain or use the exported extConInitExported() function
//__declspec(dllexport)
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved) {
	hm = hModule;
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (checkIfSteamVersion()) {
			//CreateThread(0, 0, t6Cin, 0, 0, 0);
			if (EXTERNAL_CONSOLE_MODE == 0 || EXTERNAL_CONSOLE_MODE == 2) {
				AllocConsole();
				FILE* pFile = nullptr;
				freopen_s(&pFile, "CONOUT$", "w", stdout);
				freopen_s(&pFile, "CONIN$", "r", stdin);
			}
			if (EXTERNAL_CONSOLE_MODE >= 1) {
				std::thread t1(ExternalConsoleGuiInitWrapper);
				t1.detach();
			}

			CreateThread(0, 0, extConInitWrapper, 0, 0, 0);

		}
		else {
			ExitProcess(0);
		}
	}
	return TRUE;
}