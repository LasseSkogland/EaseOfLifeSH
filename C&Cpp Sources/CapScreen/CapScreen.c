#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>

#define debug(MSG) printf("%s\n", MSG)

int arrSize = 0;

int GetCompleteBitmapInfo( BITMAPINFO* BitmapInfo, HBITMAP* hBitmap );

int main( int argc, char *argv[] ) {
	HDC hdc = GetDC(NULL);
	HDC hDest = CreateCompatibleDC(hdc);
	int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	HBITMAP hbDesktop = CreateCompatibleBitmap(hdc, width > 1920 ? 1920 : width, height);
	SelectObject(hDest, hbDesktop);
	StretchBlt(hDest, 0, 0, width, height, hdc, 0, height-1, width, -height, SRCCOPY);
	BITMAPINFO bi;
	GetCompleteBitmapInfo(&bi, &hbDesktop);
	arrSize = bi.bmiHeader.biWidth * bi.bmiHeader.biHeight * (bi.bmiHeader.biBitCount >> 3);
	void* Pixels = (void*) malloc(arrSize);
	GetDIBits(hdc, hbDesktop, 0, bi.bmiHeader.biHeight, Pixels, &bi, DIB_RGB_COLORS);
	ReleaseDC(NULL, hdc);
	SDL_Surface *sur = SDL_CreateRGBSurface(SDL_SWSURFACE, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight, 32, 0xff0000, 0xff00, 0xff, 0);
	sur->pixels = Pixels;
	SDL_SaveBMP(sur, "out.bmp");
	return 0;
}

int GetCompleteBitmapInfo( BITMAPINFO* BitmapInfo, HBITMAP* hBitmap ) {
	BITMAP Bitmap;
	if (GetObject(*hBitmap, sizeof(BITMAP), &Bitmap) == 0) return 1;
	BitmapInfo->bmiHeader.biBitCount = 32;
	BitmapInfo->bmiHeader.biClrImportant = 0;
	BitmapInfo->bmiHeader.biClrUsed = 0;
	BitmapInfo->bmiHeader.biCompression = BI_RGB;
	BitmapInfo->bmiHeader.biHeight = Bitmap.bmHeight;
	BitmapInfo->bmiHeader.biPlanes = Bitmap.bmPlanes;
	BitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BitmapInfo->bmiHeader.biSizeImage = 0;
	BitmapInfo->bmiHeader.biWidth = Bitmap.bmWidth;
	BitmapInfo->bmiColors->rgbRed = NULL;
	BitmapInfo->bmiColors->rgbGreen = NULL;
	BitmapInfo->bmiColors->rgbBlue = NULL;
	BitmapInfo->bmiColors->rgbReserved = NULL;
	return 0;
}
