#ifndef MHS_H
#define MHS_H
#include <winsock2.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define debug(MSG) printf("%s\n", MSG);

typedef uint32_t socklen_t;
struct client{
	int sock;
	socklen_t clilen;
	struct sockaddr_in addr_in;
	pthread_t p;
};

void *cThread(int id);
struct client clients[128];
extern int cNum, alive, sock, port;
#endif //MHS_H