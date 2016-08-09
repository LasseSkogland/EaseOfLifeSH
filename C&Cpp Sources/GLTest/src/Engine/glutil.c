#include "engine.h"

void glQuad(float x, float y, float x2, float y2) {
	glVertex2f(x, y);
	glVertex2f(x2, y);
	glVertex2f(x2, y2);
	glVertex2f(x, y);
	glVertex2f(x2, y2);
	glVertex2f(x, y2);
}

void glFreeQuad(float x, float y, float x2, float y2, float x3, float y3, float x4, float y4) {
	glVertex2f(x, y);
	glVertex2f(x3, y3);
	glVertex2f(x2, y2);
	glVertex2f(x, y);
	glVertex2f(x4, y4);
	glVertex2f(x3, y3);
}

/*GLint glLoadTexture(const char *filename, int width, int height) {
	char *data = calloc(sizeof(char), width * height * 3);
	gzFile f = gzopen(filename, "r");
	gzread(f, data, width * height * 3);
	gzclose(f);
	
	GLint texture;
	glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
	
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  			 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	glEnable(GL_TEXTURE_2D);
	free(data);
	return texture;
}//*/
