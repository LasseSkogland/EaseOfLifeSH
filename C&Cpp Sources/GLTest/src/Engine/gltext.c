#include "engine.h"



void glText(char *string, double x, double y) {
	glBegin(GL_TRIANGLES);
	glColor3f(.5, .5, .5);
	glFreeQuad(250, -350, 350, -350, 350, -300, 250, -300);
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(255, -345, 0);
	char *p;
	for(p = string; *p; p++) {
		
	}
	glPopMatrix();
	glEnd();
}