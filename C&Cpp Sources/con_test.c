#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE stdHandle;
char progress[] = { '|', '/', '-', '\\' };

long time;
int min = 0, sec = 0, prog;

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

void parseSec() {
	while(sec >= 60) {
		if(sec >= 60) {
			sec -= 60;
			min += 1;
		} else break;
	}
}

int main(int argc, char *argv[]) {
	if(argc > 2) {
		sec = atoi(argv[2]);
		min = atoi(argv[1]);
	} else sec = atoi(argv[1]);
	if(sec >= 60) parseSec();
	Console_Init();
	system("cls");
	while(min > 0 || sec > 0) {
		printf("Optimizing %c %02im:%02is", progress[prog], min, sec);
		prog++;
		if(prog > 3) prog = 0;
		Sleep(1000);
		sec -= 1;
		if(sec < 0) {
			min--;
			sec = 59;
		}
		Console_SetXY(0, 0);
	}
}