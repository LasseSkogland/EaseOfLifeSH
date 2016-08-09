#define _WIN32_WINNT 0x0500
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, GetModuleHandle(NULL), 0);
	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	return 0;
}