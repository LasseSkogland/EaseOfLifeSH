#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define debug(MSG) printf("%s\n", MSG)
void brute(int);
void fillArray();

int lastPass;

char *allowed, aSize, *test;

int main(int argc, char *argv[]) {
	test = argv[1];
	fillArray();
	brute(strlen(test));
	return 0;
}

int sendPass(char *inpass, int size) {
	char *pass = malloc(size + 1), c;
	memset(pass, 0, size + 1);
	for(c = 0; c < size; c++) pass[c] = allowed[inpass[c]];
	if(strstr(pass, test) != NULL) {
		printf("Password: %s\nTime spent: %ims\n", pass, ((clock() / (CLOCKS_PER_SEC / 1000)) - lastPass));
		free(pass);
		return 1;
	}
	free(pass);
	return 0;
}

void brute(int size) {
	char *pass = malloc(size * sizeof(char)), i;
	lastPass = clock() / (CLOCKS_PER_SEC / 1000);
	while (1) {
		for (i = 0; i < size; i++) {
			if (pass[i] > aSize) {
				pass[i + 1]++;
				pass[i] = 0;
			}
		}
		if(sendPass(pass, size) == 1) break;
		pass[0]++;
	}
	free(pass);
}

void fillArray() {
	allowed = calloc(sizeof(char), 36);
	memset(allowed, 0, 36);
	char i, arr = 0;
	for (i = 0x30; i < 0x3A; i++) allowed[arr++] = i;
	for (i = 0x61; i < 0x7B; i++) allowed[arr++] = i;
	aSize = arr - 1;
}