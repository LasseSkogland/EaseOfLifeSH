#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <winsock2.h>


#define Write(MSG) send(sock, MSG, strlen(MSG), 0)

int sock, port = 80;
char *host = "localhost";

int main(int argc, char *argv[]) {
	if(argc == 3) {
		host = argv[1];
		port = atoi(argv[2]);
	}
	WSADATA	WsaData;
	WSAStartup (0x202, &WsaData);
	struct sockaddr_in sin;
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if(sock < 0) printf("Error: %i\n", WSAGetLastError());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	struct hostent * host_addr = gethostbyname(host);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	if(connect(sock,(const struct sockaddr *)&sin, sizeof(struct sockaddr_in)) != 0) printf("Error: %i\n", WSAGetLastError());
	char *tmp = malloc(256);
	char *c = malloc(2);
	memset(c, 0, 2);
	while(1 == 1) {
		memset(tmp, 0, 256);
		while((c[0] = getc(stdin)) != '\n') strcat(tmp, c);
		Write(tmp);
	}
	
	WSACleanup();
	return 0;
}
