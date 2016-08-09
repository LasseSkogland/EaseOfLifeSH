#include <windows.h>

void EmulateKey( BYTE b ) {
	keybd_event( b, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0 );
	keybd_event( b, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

int CheckKeyState( BYTE b ) {
	BYTE keyState[256];
	GetKeyboardState((LPBYTE)&keyState);
	return keyState[b] & 1;
}

int sleepTime = 333;

int main(int argc, char *argv[]) {
	if(CheckKeyState(VK_NUMLOCK)) EmulateKey(VK_NUMLOCK);
	if(CheckKeyState(VK_CAPITAL)) EmulateKey(VK_CAPITAL);
	if(CheckKeyState(VK_SCROLL)) EmulateKey(VK_SCROLL);
	
	while(1 == 1) {
		EmulateKey(VK_NUMLOCK);
		Sleep(sleepTime);
		EmulateKey(VK_CAPITAL);
		Sleep(sleepTime);
		EmulateKey(VK_SCROLL);
		Sleep(sleepTime);
		EmulateKey(VK_NUMLOCK);
		Sleep(sleepTime);
		EmulateKey(VK_CAPITAL);
		Sleep(sleepTime);
		EmulateKey(VK_SCROLL);
		Sleep(sleepTime);
	}
	return 0;
}
	