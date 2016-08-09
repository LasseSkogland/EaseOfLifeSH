#include"common.h"

char *fromClip() {
	return (char *) GetClipboardData(CF_TEXT);
}

void toClip(char *str){
	EmptyClipboard();
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (strlen(str)+1));
    LPTSTR sMem = (TCHAR*)GlobalLock(hMem);
    memcpy(sMem, str, (strlen(str)));
    GlobalUnlock(hMem);
    SetClipboardData(CF_TEXT, hMem);
}

int fromHex(char *str){
	return (int)strtol(str, NULL, 16);
}