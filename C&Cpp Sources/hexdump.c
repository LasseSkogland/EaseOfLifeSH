#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long pos = 0, size;
char i, c, len = 1;
int fpeek(FILE *);

int main(int argc, char *argv[]) {
	FILE *in, *out = stdout;
	if(argc >= 3) {
		for(i = 1; i < argc; i++) {
			if(strstr(argv[i], "-i") != NULL && argc > i + 1) in = fopen(argv[i + 1], "rb");
			if(strstr(argv[i], "-o") != NULL && argc > i + 1) out = fopen(argv[i + 1], "wb");
			if(strstr(argv[i], "-l") != NULL && argc > i + 1) len = atoi(argv[i + 1]) > 127 ? 127 : atoi(argv[i + 1]);
		}
	} else exit(1);
	char *tmp = malloc(len + 1);
	fseek(in, 0L, SEEK_END);
	size = ftell(in);
	fseek(in, 0L, SEEK_SET);
	while (feof(in) == 0) {
		if(size / len > 16777215) {fprintf(out, "%08X: ", pos);}
		else if(size / len > 65535) {fprintf(out, "%06X: ", pos);}
		else if(size / len > 255) {fprintf(out, "%04X: ", pos);}
		else fprintf(out, "%02X: ", pos);
		memset(tmp, 0, len + 1);
		for(i = 0; i <= len -1; i++) {
			fprintf(out, "%02X", fpeek(in) == EOF ? 0xFF : fpeek(in));
			if(fpeek(in) == EOF) break;
			tmp[i] = fgetc(in);
		}
		for(i = 0; i < len; i++) {
			if(tmp[i] == '\n' || tmp[i] == '\r') tmp[i] = ' ';
			if(tmp[i] == 0) tmp[i] = '.';
		}
		fprintf(out, " - %s\n", tmp);
		if(fpeek(in) == EOF) break;
		pos += i;
	}
	fclose(in);
	fclose(out);
	return 0;
}

int fpeek(FILE *stream) {
    int c = fgetc(stream);
    ungetc(c, stream);
    return c;
}