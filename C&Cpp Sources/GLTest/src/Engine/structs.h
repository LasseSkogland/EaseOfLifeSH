#ifndef STRUCTS_H_
#define STRUCTS_H_

int FLAG_DEAD, FLAG_ALIVE;

typedef struct {
	double x, y, speed;
	int flags, rotation;
} Entity;

typedef struct {
	Entity ent;
	double accel, decel, speed, maxspd, idlerot;
} Ship;

typedef struct {
	double x, y, w, h;
} Rect;


#endif
