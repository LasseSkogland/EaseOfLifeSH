#include "engine.h"
int deg = 180 / M_PI;
int tmp;

float rndFloat() {
	return (float)rand() / (float)RAND_MAX;
}

int checkCollision(Rect r1, Rect r2) {
	if (r1.x < r2.w && r1.w > r2.x && r1.y < r2.h && r1.h > r2.y) return 1;
	return 0;
}

double getAngle(float x, float y, float w, float h) {
	return (360 - (atan2((w - x), (h - y)) * deg));
}
