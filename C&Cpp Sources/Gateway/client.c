#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>

#define Write(MSG) send(sock, MSG, strlen(MSG), 0)
#define debug(MSG) printf("%s\n", MSG)

int sock, port = 80;
char *host = "localhost";

void setupSocket() {
	WSADATA	WsaData;
	WSAStartup (0x202, &WsaData);
	struct sockaddr_in sin;
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if(sock < 0) printf("Error: %i\n", WSAGetLastError());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	struct hostent * host_addr = gethostbyname(host);
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	if(connect(sock,(const struct sockaddr *)&sin, sizeof(struct sockaddr_in)) != 0) {
		debug("Failed to connect to host!");
		exit(1);
	}
}

int main(void) {
	
	
	WSACleanup();
	return 0;
}
