#include "easylib.h"

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

Coord *Console_GetXY () {
	Coord *c;
	c->x = csbi.dwCursorPosition.X;
	c->y = csbi.dwCursorPosition.Y;
	return c;
}

void Console_Clear() {
	char *tmp = malloc(csbi.dwSize.X * csbi.dwSize.Y);
	memset(tmp, ' ', csbi.dwSize.X * csbi.dwSize.Y);
	Console_SetXY(0, 0);
	printf("%s", tmp);
	Console_SetXY(0, 0);
}