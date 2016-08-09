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

#define debug(MSG) printf("%s\n", MSG)
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef struct hostent hostent;

int main(void){
	#ifdef _WIN32
	WSADATA WsaData;
	WSAStartup(0x202, &WsaData);
	#endif
	int sock;
	sockaddr_in sin;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	#ifdef _WIN32
	printf("Error: %i\n", WSAGetLastError());
	#else
	debug("Error!");
	#endif
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	hostent * host_addr = gethostbyname("dynamicdns.park-your-domain.com");
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
	if(connect(sock,(const sockaddr *)&sin, sizeof(sockaddr_in)) != 0) {
		debug("Failed to connect to host!");
		WSACleanup();
		return 1;
	}

	char *data = "GET /update?host=ds&domain=REDACTED&password=REDACTED HTTP/1.0\r\n\r\n", *receive = malloc(1024);
	memset(receive, 0, 1024);
	send(sock, data, strlen(data), 0);
	recv(sock, receive, 1024, 0);
	if(strstr(receive, "<ErrCount>0</ErrCount>") != NULL) {
		debug("Success...");
		char *pch = strstr(receive, "<IP>");
		int c, count = 0;
		pch++;pch++;pch++;pch++;
		printf("IP: ");
		while((c = pch[count++]) != '<') {
			printf("%c", c);
		}
		printf("\n");
	}else{
		debug("Failed...");
		#ifdef _WIN32
		WSACleanup();
		#endif
		return 1;
	}

	#ifdef _WIN32
	WSACleanup();
	#endif
	return 0;
}
