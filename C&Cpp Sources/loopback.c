#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef uint32_t socklen_t;
int sock;
socklen_t clilen;
struct sockaddr_in addr_in;

void SetSock(int port);

int alive = 1, sock, port;

int main(int argc, char *argv[]) {
	if(argc > 1) {SetSock(atoi(argv[1]));}
	else SetSock(80);
	clilen = sizeof(addr_in);
	sock = accept(sock, (struct sockaddr *) &addr_in, &clilen);
	printf("Client connected: %s\n", sock);
	char *in = malloc(256);
	memset(in, 0, 256);
	while(1 == 1) {
		while(recv(sock, in, 256, 0) >= 0) {
			printf("%s", in);
			//send(sock, in, 256, 0);
			memset(in, 0, 256);
		}
	}
	return 0;
}

void SetSock(int port) {
	WSADATA	WsaData;
	WSAStartup (0x101, &WsaData);
	struct sockaddr_in sin;
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if(sock < 0) printf("Error: %i\nSomething went wrong", WSAGetLastError());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		printf("Error: %i\nPort %i probably already taken...", WSAGetLastError(), port);
		exit(1);
	}
	listen(sock, 5);
}