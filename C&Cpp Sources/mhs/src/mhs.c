#include "mhs.h"

int cNum = 0, alive = 1, sock, port;
void *aThread(char *arg);
void SetSock(int port);

int main(int argc, char *argv[]) {
	if(argc > 1) {SetSock(atoi(argv[1]));}
	else SetSock(80);
	pthread_t accept;
	pthread_create(&accept, NULL, aThread, "NULL");
	
	while(alive == 1) {
		char *cmd = malloc(256);
		memset(cmd, 0, 256);
		scanf("%s", cmd);
		if(strcmp(cmd, "shutdown") == 0) break;
	}
	
	pthread_cancel(accept);
	int i;
	for( i = 0 ; i < cNum ; i++ ) pthread_cancel(clients[i].p);
	return 0;
}

void *aThread(char *arg) {
	while(cNum <= 128) {
		clients[cNum].clilen = sizeof(clients[cNum].addr_in);
		clients[cNum].sock = accept(sock, (struct sockaddr *) &clients[cNum].addr_in, &clients[cNum].clilen);
		pthread_create(&clients[cNum].p, NULL, cThread, cNum);
		printf("Client connected with ID: %i\n", cNum);
		cNum++;
		if(cNum >= 128) break;
	}
}

void SetSock(int port) {
	WSADATA	WsaData;
	WSAStartup (0x101, &WsaData);
	struct sockaddr_in sin;
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if(sock < 0) printf("Error: %i\nPort %i probably taken...", WSAGetLastError(), port);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		printf("Error: %i\nPort %i probably already taken...", WSAGetLastError(), port);
		exit(1);
	}
	listen(sock, 5);
}