#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>
#include <stdlib.h>
#include "structs.h"

#define WIDTH 800
#define HEIGHT 600
#define FPS 60
#define SCRSZ 350
#define RAD(VAL) ((VAL * M_PI) / 180)
#define MAX_BULLETS 256

//KEYS.c
void keys(unsigned char, int, int);
int keyHandler(void *);
Entity bullets[MAX_BULLETS];
Ship player, enemy;

unsigned char nextBullet;
float distance;
SDL_Event e;

//UTIL.c
float rndFloat();
double getAngle(float, float, float, float);

//GLUTIL.c
void glQuad(float, float, float, float);
void glFreeQuad(float, float, float, float, float, float, float, float);

//GLTEXT.c
void glText(char *, double, double);

#endif
