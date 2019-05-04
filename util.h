#ifndef _EIKASIA_H // Multi def protection
#define _EIKASIA_H

#include <Windows.h>

// The Eikasia Core Functions
DWORD APIHook(DWORD HookFunc, DWORD MyFunc, DWORD OrigFunc);

// The main function executed when a Proccess is Attach
void ProcessAttach(void);

// The AntiWPE Function
unsigned long __stdcall AWPE(void* pVoid);

// The AntiSpeed Hack Function
unsigned long __stdcall ASPH(void* pVoid);

// The AntiMacro Function
void WINAPI AMACRO(void);



// The Data Obfuscation Function
void DataObfuscation(void);

// The AntiBot Function
void WINAPI antibot(SOCKET s, const char* buf, int *len, int flags);

// The Expire Time function
bool IsExpired(int ounixtime);

// The Get MAC Address function
void GetMACaddress(char *mac_address);

// The Get Hardware ID function
void GetHWID(char *hardware_id);


// The AntiMacro Function
void WINAPI AntiMacroHook(void);


#endif