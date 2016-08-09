#include "engine.h"

Uint8 *keyPress;
unsigned int i, t1 = 0, t2 = 0;

int keyHandler(void *null) {
	distance = 2.0f;
	while(e.type != SDL_QUIT) {
		keyPress = SDL_GetKeyState(NULL);
		if(keyPress[SDLK_ESCAPE]) {
			SDL_Quit();
			break;
		}
		if(keyPress[SDLK_w] || keyPress[SDLK_UP]) {
			player.idlerot = player.ent.rotation;
			if(player.speed < player.maxspd && SDL_GetTicks() - t2 >= 200) {
				player.speed += player.accel;
				t2 = SDL_GetTicks();
			}
			player.ent.x += player.speed * (float) sin(RAD(player.ent.rotation));
			player.ent.y -= player.speed * (float) cos(RAD(player.ent.rotation));
		} else if(player.speed > 0.0f) {
			if(SDL_GetTicks() - t2 >= 200) {
				player.speed -= (player.speed / 2) * player.decel;
				t2 = SDL_GetTicks();
				if(player.speed < 0.01f) {
					player.speed = 0.0f;
				}
			}
			player.ent.x += player.speed * (float) sin(RAD(player.idlerot));
			player.ent.y -= player.speed * (float) cos(RAD(player.idlerot));
		}
		
		if(keyPress[SDLK_d] || keyPress[SDLK_RIGHT]) {
			player.ent.rotation += distance * 1.0f;
		} else if(keyPress[SDLK_a] || keyPress[SDLK_LEFT]) {
			player.ent.rotation -= distance * 1.0f;
		}
		if(t1 == 0 || SDL_GetTicks() - t1 > 100) {
			t1 = SDL_GetTicks();
			if(keyPress[SDLK_SPACE]) {
				bullets[nextBullet] = player.ent;
				bullets[nextBullet].speed = 3 + player.maxspd;
				bullets[nextBullet++].flags = FLAG_ALIVE;
				if(nextBullet >= MAX_BULLETS) nextBullet = 0;
			}
		}
		if(player.ent.rotation > 359) player.ent.rotation = 0;
		else if(player.ent.rotation < 0) player.ent.rotation = 359;
		//free(keyPress);
		SDL_Delay(10);
	}
	return 0;
}
