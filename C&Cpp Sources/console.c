#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE stdHandle;

void Console_Init() {
	stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo( stdHandle, &csbi );
}

void Console_SetXY ( short x, short y ) { 
	COORD Cursor_Position; 
	Cursor_Position.X = x; 
	Cursor_Position.Y = y; 
	SetConsoleCursorPosition( stdHandle, Cursor_Position ); 
} 

COORD *Console_GetXY () {
	COORD *c;
	c->X = csbi.dwCursorPosition.X;
	c->Y = csbi.dwCursorPosition.Y;
	return c;
}

void Console_Clear(  ) {
   COORD coordScreen = {0, 0};
   DWORD cCharsWritten;
   DWORD dwConSize;
   if( !GetConsoleScreenBufferInfo( stdHandle, &csbi )) return;
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
   if( !FillConsoleOutputCharacter( stdHandle, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten )) return;
   if( !GetConsoleScreenBufferInfo( stdHandle, &csbi )) return;
   if( !FillConsoleOutputAttribute( stdHandle, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten )) return;
   Console_SetXY(0, 0);
}

int main(int argc, char *argv[]) {
	printf("Tst");
	Sleep(200);
	Console_Init();
	Console_Clear();
	return 0;
}