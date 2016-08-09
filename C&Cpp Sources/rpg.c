#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char ValidChars[77] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '#', '$', '%', '<', '>', '/', '\\', '[', ']', '(', ')', '{', '}', '='};
long unsigned int seed;
const int BUFFER_SIZE = 33554432;
#define random() (seed = (long)(16807 * (seed & 0xFFFF) + ((((16807 * (seed >> 16)) & 0x7FFF) << 16) + ((16807 * (seed >> 16)) >> 15)) & 0x7FFFFFFF) + (16807 * (seed & 0xFFFF) + ((((16807 * (seed >> 16)) & 0x7FFF) << 16) + ((16807 * (seed >> 16)) >> 15)) >> 31))

char *generate(int size){
	seed = time(NULL);
	int i, num = 77;
	char *tmp = calloc(size + 1, 1);
	for(i = 0 ; i < size ; i++) tmp[i] = ValidChars[random() % num];
	return tmp;
}

void main(int argc, char **argv){
	if(argc >= 2){
		unsigned long int size = atoi(argv[1]);
		if (__builtin_strstr(argv[1], "G") != 0) size *= 1024*1024*1024;
		if (__builtin_strstr(argv[1], "M") != 0) size *= 1024*1024;
		if (__builtin_strstr(argv[1], "K") != 0) size *= 1024;
		char *tmp;
		while(size > BUFFER_SIZE) {
			printf("%s", tmp = generate(BUFFER_SIZE));
			size -= BUFFER_SIZE;
			free(tmp);
		}
		
		printf("%s", tmp = generate(size));
		free(tmp);
	}else{
		printf("Usage: rpg <SIZE>");
	}
}