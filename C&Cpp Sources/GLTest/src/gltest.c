#include "gltest.h"

GLuint model[1];
unsigned int i;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(player.ent.x, player.ent.y, 0);
	glRotated(player.ent.rotation, 0, 0, 1);
	
	glCallList(model[0]);	
	glPopMatrix();

	glPushMatrix();
	glTranslated(enemy.ent.x, enemy.ent.y, 0);
	glRotated(enemy.ent.rotation, 0, 0, 1);
	glCallList(model[0]);
	glPopMatrix();
	for(i = 0; i < MAX_BULLETS; i++) {
		if(bullets[i].flags & FLAG_ALIVE) {
			glPushMatrix();
			glTranslated(bullets[i].x, bullets[i].y, 0);
			glBegin(GL_TRIANGLES);
			glColor3f(0.5f, 0.5f, 0.5f);
			glQuad(-1.5, 1.5, 1.5, -1.5);
			glEnd();
			glPopMatrix();
		}
	}
	SDL_GL_SwapBuffers();
}

void gameLogic() {
	int ticks;
	SDL_Thread *keyThread;
	keyThread = SDL_CreateThread(keyHandler, NULL);
	while(e.type != SDL_QUIT) {
		ticks = SDL_GetTicks();
		SDL_PollEvent(&e);
		for(i = 0; i < MAX_BULLETS; i++) {
			if(bullets[i].x > SCRSZ || bullets[i].x < -SCRSZ || bullets[i].y > SCRSZ || bullets[i].y < -SCRSZ) {
				bullets[i].flags = FLAG_DEAD;
			} else {
				bullets[i].x += (bullets[i].speed) * (float) sin(RAD(bullets[i].rotation));
				bullets[i].y -= (bullets[i].speed) * (float) cos(RAD(bullets[i].rotation));
			}
		}
		if(enemy.ent.rotation + 180 < getAngle(player.ent.x, player.ent.y, enemy.ent.x, enemy.ent.y) - 180)enemy.ent.rotation += enemy.speed;
		else enemy.ent.rotation -= enemy.speed;
		enemy.ent.x += (enemy.speed / 2) * (float) sin(RAD(enemy.ent.rotation));
		enemy.ent.y -= (enemy.speed / 2) * (float) cos(RAD(enemy.ent.rotation));
		renderScene();
		if(SDL_GetTicks() - ticks < 1000/FPS) SDL_Delay((1000/FPS) - (SDL_GetTicks() - ticks));
	}
	SDL_WaitThread(keyThread, NULL);
}

void initObjects() {
	nextBullet = 0;
	FLAG_DEAD = 0;
	FLAG_ALIVE = 1;
	
	player.ent.flags = FLAG_ALIVE;
	player.ent.rotation = 0;
	player.accel = 0.5;
	player.decel = 0.5;
	player.speed = 0;
	player.maxspd = 2.0;

	enemy.ent.flags = FLAG_ALIVE;
	enemy.ent.x = 100;
	enemy.ent.y = 100;
	enemy.ent.rotation = 180;
	enemy.accel = 0.5;
	enemy.decel = 0.25;
	enemy.speed = 2;
	enemy.maxspd = 2.0;
}

void initModels() {
	model[0] = glGenLists(1); //Ship Model - Start
	glNewList(model[0], GL_COMPILE);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.5);
	glFreeQuad(-2.0, -6.0, 2.0, -6.0, 5.0, 5.0, -5.0, 5.0);
	glQuad(-10.0, 10.0, 10.0, 5.0);
	glQuad(12.0, 2.0, 10.0, 10.0);
	glQuad(-10.0, 2.0, -12.0, 10.0);
	glEnd();
	glPopMatrix();
	glEndList(); //Ship Model - End
	initObjects();
}

void init() {
	glEnable(GL_CULL_FACE);
	glShadeModel( GL_SMOOTH );
    glClearColor( 0, 0, 0, 0 );
	gluOrtho2D(-SCRSZ, SCRSZ, SCRSZ, -SCRSZ);
	initModels();
}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);
	SDL_WM_SetCaption("GLTest", 0);
	init();
	gameLogic();
	SDL_Quit();
	return 0;
}
