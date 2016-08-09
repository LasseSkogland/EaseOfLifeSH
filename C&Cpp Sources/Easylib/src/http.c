#include "easylib.h"

char *HttpGet(char *get) {
	char *data = calloc(32*1024*1024+1, 1);
	Write(get);
	Read(data, 32*1024*1024);
	return data;
}