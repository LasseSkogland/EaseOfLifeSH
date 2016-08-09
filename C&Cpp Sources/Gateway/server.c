#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>

#define Write(MSG) send(sock, MSG, strlen(MSG), 0)
#define debug(MSG) printf("%s\n", MSG)

typedef struct {
	pthread_t p;
	int group;
	int sock;
	struct sockaddr_in sin;
} client;

int sock, port = 80, alive = 0, cnum = 0;
client clients[256];

void setupSocket() {
	WSADATA	WsaData;
	WSAStartup (0x202, &WsaData);
	struct sockaddr_in sin;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		printf("Could not bind!\nPort %i is probably already taken...", port);
		exit(1);
	}
	listen(sock, 5);
	
}

void cThread(char *arg) {
	
}

int main(void) {
	setupSocket();
	while(alive) {
		client c = clients[cnum];
		c.sock = accept(sock, (struct sockaddr *) &c.sin, sizeof(c.sin));
		pthread_create(&c.p, NULL, cThread, cnum);
	}
	WSACleanup();
	return 0;
}
