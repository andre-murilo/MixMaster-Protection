#include <Windows.h>
#include "Splash.h"
#include "util.h"
#include "detectwnd.h"
#include <functional>
#include <stack>


extern "C" __declspec(dllexport) void Start();




void SplashShow()
{
	CSplash splash1(TEXT(".\\Data/Protect.bmp"), RGB(128, 128, 128));
	splash1.ShowSplash();
	Sleep(2500);
	splash1.CloseSplash();
}

void Start()
{
	long result = ASPH("");
	AMACRO();
}

template<typename T>
T readMemory(LPVOID adr)
{
	return *((T*)adr);
}


void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, int byteNum)
{
	unsigned long OldProtection;
	VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy((LPVOID)addressToWrite, valueToWrite, byteNum);
	VirtualProtect((LPVOID)(addressToWrite), byteNum, OldProtection, NULL);
}


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		SplashShow();
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Start), NULL, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return true;
}