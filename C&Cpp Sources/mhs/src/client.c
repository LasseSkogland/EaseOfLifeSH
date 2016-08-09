#include "mhs.h"

char *data;
void HandleHttp();

void *cThread(int c) {
	struct client Client = clients[c];
	data = malloc(4096);
	memset(data, 0, 4096);
	while(alive == 1) {
		while(recv(Client.sock, data, 4096, 0) > 0) {
			printf("%s", data);
			HandleHttp();
			memset(data, 0, 4096);
		}
	}
}

void HandleHttp(){
	char *out = malloc(4096);
	memset(out, 0, 4096);
	out = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Lenght: 10\r\n\r\nHelloWorld";
	send(sock, out, sizeof(out), NULL);
}