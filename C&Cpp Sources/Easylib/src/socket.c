#include "easylib.h"

int sock;

int SetupSocket(char *host, int port) {
	WSADATA	WsaData;
	WSAStartup (0x0202, &WsaData);
	struct hostent *h = gethostbyname(host); 
	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons( (unsigned short)port);
	sin.sin_addr.s_addr = *((int*)*h->h_addr_list);
	if(connect(sock, (const struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == -1) return -1;
	return 1;
}