#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <arpa/inet.h>

int init_server(int port);
void process_connections();

#endif
