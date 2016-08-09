#include <SDL/SDL.h>
#include <windows.h>

struct Pos {
	unsigned int x, y;
};

SDL_Surface *bmp, *screen;
SDL_Rect r;
SDL_Event e;
int w, h, Alive = 1;

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_VideoInfo *info = SDL_GetVideoInfo();
	w = info->current_w;
	h = info->current_h;
	screen = SDL_SetVideoMode( w, h, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );
	bmp = SDL_DisplayFormat(SDL_LoadBMP("idrift.bmp"));
	r.x = (w/2) - (bmp->w/2);
	r.y = (h/2) - (bmp->h/2);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	
	while(Alive == 1) {
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT: Alive = 0; break;
				case SDL_KEYDOWN: Alive = 0; break;
				case SDL_MOUSEBUTTONDOWN: Alive = 0; break;
			}
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		SDL_BlitSurface(bmp, NULL, screen, &r);
		SDL_Flip(screen);
		SDL_Delay(50);
	}
	SDL_ShowCursor(SDL_ENABLE);
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	SDL_Quit();
	return 0;
}