#include <Windows.h>

DWORD APIHook(DWORD HookFunc, DWORD MyFunc, DWORD OrigFunc)
{
	unsigned char NewData[5], DetourJump[5], OldData[5];
	DWORD OldProtect;
	int i;
	unsigned char* HookFuncPtr = (unsigned char*)HookFunc;
	unsigned char* HookDetour = (unsigned char*)malloc(25);
	for (i = 0; i < 25; i++)
		HookDetour[i] = 0x90; //NOP
	NewData[0] = 0xE9; //JMP (near)
	*(PDWORD)&NewData[1] = (DWORD)((DWORD)MyFunc - ((DWORD)HookFunc + 5));
	DetourJump[0] = 0xE9;
	*(PDWORD)&DetourJump[1] = (DWORD)((DWORD)HookFunc - ((DWORD)HookDetour + 14 + 5));
	VirtualProtectEx(GetCurrentProcess(), (void*)HookFunc, 10, PAGE_EXECUTE_WRITECOPY, &OldProtect);
	for (i = 0; i < 5; i++)
	{
		OldData[i] = HookFuncPtr[i];
		HookFuncPtr[i] = NewData[i];
	}
	VirtualProtectEx(GetCurrentProcess(), (void*)HookFunc, 10, OldProtect, NULL);
	VirtualProtectEx(GetCurrentProcess(), (void*)HookDetour, 25, PAGE_EXECUTE_WRITECOPY, &OldProtect);
	for (i = 0; i < 5; i++)
		HookDetour[i] = OldData[i];
	HookDetour[24 - 5] = DetourJump[0];
	HookDetour[24 - 4] = DetourJump[1];
	HookDetour[24 - 3] = DetourJump[2];
	HookDetour[24 - 2] = DetourJump[3];
	HookDetour[24 - 1] = DetourJump[4];
	HookDetour[24] = 0xC3; //RET
	VirtualProtectEx(GetCurrentProcess(), (void*)HookDetour, 25, OldProtect, NULL);
	OrigFunc = (DWORD)HookDetour;
	return OrigFunc;
}