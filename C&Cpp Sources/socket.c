#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
#endif

#define Write(MSG) send(sock, MSG, strlen(MSG), 0)
#define debug(MSG) printf("%s\n", MSG)

int sock, port = 80;
char *host = "localhost";

int main(void) {
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
	
	
	#ifdef _WIN32
	WSACleanup();
	#endif
	return 0;
}
