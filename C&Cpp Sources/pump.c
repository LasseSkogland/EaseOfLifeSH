#include <stdlib.h>
#include <stdio.h>
char Byte = 0x00;
unsigned int Size = 0, tSize = 0, Times = 1, tTimes = 0, Progress = 0, tProgress = 0;

void main(int argc, char **argv) {
	if(argc > 1) {
		int i = 0;
		for(i = 1 ; i < argc - 1 ; i++) {
			if(argv[i][0] == '-' && argv[i][1] == 'n') {
				Size = atoi(argv[i + 1]);
				if(argc == 5) Times = atoi(argv[i + 2]);
			}
		}
		FILE *f = fopen(argv[i], "a");
		tTimes = Times;
		char *tmp = calloc(Size, sizeof(char));
		printf("Writing %i bytes %i times\n", Size, Times);
		while(tTimes > 0) {
			fwrite(tmp, sizeof(char), Size, f);
			tTimes--;
		}
		fclose(f);
	} else return;
}