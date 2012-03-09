#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <arpa/inet.h>

fd_set master;
fd_set read_fds;
struct sockaddr_in serveraddr;
struct sockaddr_in clientaddr;

int fdmax;
int listener;
int newfd;

char buf[1024];
int nbytes;
int addrlen;
int i, j;

int init_server(int port);
void process_connections();

#endif
