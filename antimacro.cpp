#include <stdio.h>
#include <windows.h>
#include "util.h"


typedef BOOL(WINAPI *PRHK)(HWND hWnd, int id, UINT fsModifiers, UINT vk);
typedef void (WINAPI *Pkeybd_event) (BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo);
typedef UINT(WINAPI *PSI) (UINT nInputs, LPINPUT pInputs, int cbSize);

PRHK OrigRHK;
Pkeybd_event Origkeybd_event;
PSI OrigSI;

void WINAPI MyRHK(HWND hWnd, int id, UINT fsModifiers, UINT vk) {
}

void WINAPI Mykeybd_event(BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo) {
}

void WINAPI MySI(UINT nInputs, LPINPUT pInputs, int cbSize) {
}




void WINAPI AMACRO(void)
{
	*(PDWORD)&OrigRHK = APIHook((DWORD)GetProcAddress(GetModuleHandle("User32.dll"), "RegisterHotKey"), (DWORD)MyRHK, (DWORD)OrigRHK);
	*(PDWORD)&Origkeybd_event = APIHook((DWORD)GetProcAddress(GetModuleHandle("User32.dll"), "keybd_event"), (DWORD)Mykeybd_event, (DWORD)Origkeybd_event);
	*(PDWORD)&OrigSI = APIHook((DWORD)GetProcAddress(GetModuleHandle("User32.dll"), "SendInput"), (DWORD)MySI, (DWORD)OrigSI);

}
