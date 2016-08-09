#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	if(argc < 2) return 1;
	char *hashthis = argv[1];
	int i, h = 0;
	for(i = 0 ; i < strlen(hashthis) ; i++ ) {
		h = 31 * h + hashthis[i];
	}
	if(h < 0) h = -h;
	h = h % 65535;
	printf("%i\n", h);
	return 0;
}