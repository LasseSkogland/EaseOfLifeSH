#include"common.h"

#define log(MSG) printf("%s\n", MSG)

int main(int argc, char **argv) {
	log("Opening Clipboard...");
	if (!OpenClipboard(NULL)) return 1;
	char *hex = fromClip();
	printf("In: %s\n", hex);
	char *string[strlen(hex) / 2];
	int count = strlen(hex) / 2, i, t = 0;
	char tmp[2];
	for( i = 0 ; i < count-2 ; i += 2 ) {
		tmp[0] = hex[i];
		tmp[1] = hex[i+1];
		string[t++] = fromHex(tmp);
	}
	printf("Out: %s\n", string);
	toClip(string);
    CloseClipboard();
}