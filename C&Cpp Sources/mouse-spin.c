#include <windows.h> 
#include <math.h>
#include <time.h>

int main() {
	float PI2 = 2 * M_PI;
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int x = desktop.right/2, y = desktop.bottom/2, tx, ty, xsize = x, ysize = y;
	float angle = 0, stepsize = PI2 / 360;
	long time = clock();
	while(1 == 1) {		
		if(clock() - time >= 8) {
			tx = xsize * cos(angle);
			ty = ysize * sin(angle);
			angle += stepsize;
			if(angle == PI2) angle = 0.0;
			time += 8;
		}
		SetCursorPos ( x + tx, y + ty );
		if(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F12)) break;
		Sleep(1);
	}
	return 0;
}