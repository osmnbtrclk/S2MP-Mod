#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
//#include "Hook.h"
#include <array>
#include "ExtConsole.h"
#include <signal.h>
#include "ExtConsoleGui.h"
#include "Console.h"
#include <thread>
#include "FuncPointers.h"

HANDLE hProcess;
HINSTANCE hInst;






//these prints will be for external console only
void ExtConsole::coutInit(const std::string& s) {
	std::cout << "[INIT] " << s << std::endl;
}

void ExtConsole::coutInfo(const std::string& s) {
	std::cout << "[INFO] " << s << std::endl;
}

void ExtConsole::coutCustom(const std::string& s, const std::string& s2) {
	std::cout << "[" << s << "] " << s2 << std::endl;
}

void ExtConsole::consoleMainLoop() {
	std::string in;
	std::cout << "----------[ S2MP External Console ]----------" << std::endl;
	while (true) {
		std::cout << "> ";
		getline(std::cin, in);
		//Console::execCmd(in);
	}
}


//0 - CLI, 1 - GUI, 2 - BOTH
void ExtConsole::extConInit(int extConsoleMode) {
	hProcess = GetCurrentProcess();
	//------- console setup --------

	//Functions::_SetScreen(1);
	//Console::execCmd("disconnect");

	if (extConsoleMode >= 1) {
		//Wait for external console gui to be fully ready
		while (!ExternalConsoleGui::isExtConGuiReady()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
	}
	if (extConsoleMode == 0 || extConsoleMode == 2) {

		//title stuff
		int size = MultiByteToWideChar(CP_UTF8, 0, "S2MP-Mod External Console", -1, NULL, 0);
		wchar_t* wtitle = new wchar_t[size];
		MultiByteToWideChar(CP_UTF8, 0, "S2MP-Mod External Console", -1, wtitle, size);
		SetConsoleTitle(wtitle);
		std::cout << "extConsoleMode:" << extConsoleMode << "; CLI will be used" << std::endl;
	}

	uintptr_t t9base = (uintptr_t)GetModuleHandle(NULL);
	std::ostringstream oss;
	oss << "0x" << std::hex << t9base;
	std::string addressStr = oss.str();
	Console::infoPrint("s2_mp64_ship Base at: " + addressStr);
	//Console::print("Sys_Cwd(): " + std::string(Functions::_Sys_Cwd()));
	if (extConsoleMode == 0 || extConsoleMode == 2) {
		consoleMainLoop();
	}
}