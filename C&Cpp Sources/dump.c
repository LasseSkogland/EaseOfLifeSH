#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>

#define Write(MSG) send(sock, MSG, strlen(MSG), 0)
#define debug(MSG) printf("%s\n", MSG)

int sock, port = 80;
char *host, *path;

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
	struct sockaddr_in sin;
	if(sock < 0) printf("Error: %i\n", WSAGetLastError());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	struct hostent * host_addr = gethostbyname(host);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	char *data = malloc(8192 * 4);
	int i = 0;
	char *c = calloc(1024, 1);
	strcpy(c, "GET ");
	strcat(c, path);
	strcat(c, " HTTP/1.0\r\nHost: ");
	strcat(c, host);
	strcat(c, "\r\n\r\n");
	int size = strlen(c);
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if(connect(sock, (const struct sockaddr *)&sin, sizeof(struct sockaddr_in)) != 0) {
		debug("Failed to connect to host!");
		return 1;
	}
	send(sock, c, size, 0);	
	int ret = 1;
	while(ret > 0) {
		ret = recv(sock, data, 8192 * 4, 0);
		printf("%s", data);
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}
