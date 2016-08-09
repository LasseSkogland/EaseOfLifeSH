#include <windows.h>
#include <string>

using namespace std;

#define caseStringify(x) case x: return string(#x)
 
string vkToString(int vk) {
    char c[2] = {0};
    switch(vk) {
        // VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
        // 0x40 : unassigned
        // VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
        caseStringify(VK_LBUTTON);
        caseStringify(VK_RBUTTON);
        caseStringify(VK_CANCEL);
        caseStringify(VK_MBUTTON);  // NOT contiguous with L & RBUTTON
        caseStringify(VK_XBUTTON1); // NOT contiguous with L & RBUTTON
        caseStringify(VK_XBUTTON2); // NOT contiguous with L & RBUTTON
        case VK_BACK: c[0]=(char)0x08; return string(c);
        caseStringify(VK_TAB);
        caseStringify(VK_CLEAR);
        caseStringify(VK_RETURN);
        caseStringify(VK_SHIFT);
        caseStringify(VK_CONTROL);
        caseStringify(VK_MENU);
        caseStringify(VK_PAUSE);
        caseStringify(VK_CAPITAL);
        caseStringify(VK_KANA);
        caseStringify(VK_JUNJA);
        caseStringify(VK_FINAL);
        caseStringify(VK_KANJI);
        caseStringify(VK_ESCAPE);
        caseStringify(VK_CONVERT);
        caseStringify(VK_NONCONVERT);
        caseStringify(VK_ACCEPT);
        caseStringify(VK_MODECHANGE);
        case VK_SPACE: c[0]=(char)0x20; return string(c);
        caseStringify(VK_PRIOR);
        caseStringify(VK_NEXT);
        caseStringify(VK_END);
        caseStringify(VK_HOME);
        caseStringify(VK_LEFT);
        caseStringify(VK_UP);
        caseStringify(VK_RIGHT);
        caseStringify(VK_DOWN);
        caseStringify(VK_SELECT);
        caseStringify(VK_PRINT);
        caseStringify(VK_EXECUTE);
        caseStringify(VK_SNAPSHOT);
        caseStringify(VK_INSERT);
        caseStringify(VK_DELETE);
        caseStringify(VK_HELP);
        caseStringify(VK_LWIN);
        caseStringify(VK_RWIN);
        caseStringify(VK_APPS);
        caseStringify(VK_SLEEP);
        caseStringify(VK_NUMPAD0);
        caseStringify(VK_NUMPAD1);
        caseStringify(VK_NUMPAD2);
        caseStringify(VK_NUMPAD3);
        caseStringify(VK_NUMPAD4);
        caseStringify(VK_NUMPAD5);
        caseStringify(VK_NUMPAD6);
        caseStringify(VK_NUMPAD7);
        caseStringify(VK_NUMPAD8);
        caseStringify(VK_NUMPAD9);
        caseStringify(VK_MULTIPLY);
        caseStringify(VK_ADD);
        caseStringify(VK_SEPARATOR);
        caseStringify(VK_SUBTRACT);
        caseStringify(VK_DECIMAL);
        caseStringify(VK_DIVIDE);
        caseStringify(VK_F1);
        caseStringify(VK_F2);
        caseStringify(VK_F3);
        caseStringify(VK_F4);
        caseStringify(VK_F5);
        caseStringify(VK_F6);
        caseStringify(VK_F7);
        caseStringify(VK_F8);
        caseStringify(VK_F9);
        caseStringify(VK_F10);
        caseStringify(VK_F11);
        caseStringify(VK_F12);
        caseStringify(VK_F13);
        caseStringify(VK_F14);
        caseStringify(VK_F15);
        caseStringify(VK_F16);
        caseStringify(VK_F17);
        caseStringify(VK_F18);
        caseStringify(VK_F19);
        caseStringify(VK_F20);
        caseStringify(VK_F21);
        caseStringify(VK_F22);
        caseStringify(VK_F23);
        caseStringify(VK_F24);
        caseStringify(VK_NUMLOCK);
        caseStringify(VK_SCROLL);
        caseStringify(VK_OEM_NEC_EQUAL);  // '=' key on numpad
        caseStringify(VK_OEM_FJ_MASSHOU); // 'Unregister word' key
        caseStringify(VK_OEM_FJ_TOUROKU); // 'Register word' key
        caseStringify(VK_OEM_FJ_LOYA);    // 'Left OYAYUBI' key
        caseStringify(VK_OEM_FJ_ROYA);    // 'Right OYAYUBI' key
        caseStringify(VK_LSHIFT);
        caseStringify(VK_RSHIFT);
        caseStringify(VK_LCONTROL);
        caseStringify(VK_RCONTROL);
        caseStringify(VK_LMENU);
        caseStringify(VK_RMENU);
        caseStringify(VK_BROWSER_BACK);
        caseStringify(VK_BROWSER_FORWARD);
        caseStringify(VK_BROWSER_REFRESH);
        caseStringify(VK_BROWSER_STOP);
        caseStringify(VK_BROWSER_SEARCH);
        caseStringify(VK_BROWSER_FAVORITES);
        caseStringify(VK_BROWSER_HOME);
        caseStringify(VK_VOLUME_MUTE);
        caseStringify(VK_VOLUME_DOWN);
        caseStringify(VK_VOLUME_UP);
        caseStringify(VK_MEDIA_NEXT_TRACK);
        caseStringify(VK_MEDIA_PREV_TRACK);
        caseStringify(VK_MEDIA_STOP);
        caseStringify(VK_MEDIA_PLAY_PAUSE);
        caseStringify(VK_LAUNCH_MAIL);
        caseStringify(VK_LAUNCH_MEDIA_SELECT);
        caseStringify(VK_LAUNCH_APP1);
        caseStringify(VK_LAUNCH_APP2);
        caseStringify(VK_OEM_1);      // ';:' for US
        caseStringify(VK_OEM_PLUS);   // '+' any country
        caseStringify(VK_OEM_COMMA);  // ',' any country
        caseStringify(VK_OEM_MINUS);  // '-' any country
        caseStringify(VK_OEM_PERIOD); // '.' any country
        caseStringify(VK_OEM_2);  // '/?' for US
        caseStringify(VK_OEM_3);  // '`~' for US
        caseStringify(VK_OEM_4);  //  '[{' for US
        caseStringify(VK_OEM_5);  //  '\|' for US
        caseStringify(VK_OEM_6);  //  ']}' for US
        caseStringify(VK_OEM_7);  //  ''"' for US
        caseStringify(VK_OEM_8);
        caseStringify(VK_OEM_AX);   //  'AX' key on Japanese AX kbd
        caseStringify(VK_OEM_102);  //  "<>" or "\|" on RT 102-key kbd.
        caseStringify(VK_ICO_HELP); //  Help key on ICO
        caseStringify(VK_ICO_00);   //  00 key on ICO
        caseStringify(VK_PROCESSKEY);
        caseStringify(VK_ICO_CLEAR);
        caseStringify(VK_PACKET);
    }
	return string();
}

int main(int argc, char *argv[]) {
	if (argc < 2)  return 1;
	int i = 0;
	DWORD W;
	DWORD SZ;
	LPCSTR buffer;
	string tmp;
	HANDLE inf, outf;
	inf = CreateFile(argv[1], GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (argc == 3) {
		outf = CreateFile(argv[2], GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	} else outf = inf;
	SZ = GetFileSize(inf, NULL);
	buffer = (LPCSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, SZ + 1);
	ReadFile(inf, (LPVOID)buffer, SZ, &W, NULL);
	SetFilePointer(outf, 0, 0, FILE_BEGIN);
	for (i = 0; i < SZ; i++) {
		if(i > 0 && i < SZ)if(buffer[i==0 ? 0 : i - 1] == '[' && buffer[i==SZ-1 ? i : i+1] == ']') tmp = vkToString((unsigned char)buffer[i]);
		else tmp = "";
		WriteFile(outf, tmp == "" ? (char *)&buffer[i] : tmp.c_str(), tmp == "" ? 1 : lstrlen(tmp.c_str()), &W, NULL);
		tmp = "";
	}
	CloseHandle(inf);
	if (argc == 3) CloseHandle(outf);
	return 0;
}


