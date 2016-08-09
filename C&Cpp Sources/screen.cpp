#include <windows.h>
#include <stdlib.h>
#include <time.h>

int main(void){
	int x = 0, y = 0;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int x2 = width, y2 = height;
	HDC hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	HDC tmp = CreateCompatibleDC(hDC);
	HBITMAP buf = CreateCompatibleBitmap(hDC, width, height);
	SelectObject(tmp, buf);
	while(true) {
		MoveToEx(tmp, x, y, NULL);
		LineTo(tmp, x2, y);
		
		MoveToEx(tmp, x2, y, NULL);
		LineTo(tmp, x2, y2);
		
		MoveToEx(tmp, x2, y2, NULL);
		LineTo(tmp, x, y2);
		
		MoveToEx(tmp, x, y2, NULL);
		LineTo(tmp, x, y);
		x++;
		y++;
		x2--;
		y2--;
		
		
		BitBlt(hDC, 0, 0, width, height, tmp, 0, 0, SRCCOPY);
		if(GetAsyncKeyState(VK_F12)) return 0;
		Sleep(10);
	}
	return 0;
}