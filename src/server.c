#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"
#include "error.h"
/* Feel free to remove static if other files need access to the listener fd. */
static int listener, fdmax;
static fd_set master, read_fds;

int init_server(int port)
{
	int yes = 1;
    struct sockaddr_in serveraddr;

	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		darkircd_error(1, "failed to create socket");

	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		darkircd_error(1, "couldn't use setsockopt on undeifined socket");

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(port);
	memset(&(serveraddr.sin_zero), '\0', 8);

	if (bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
		darkircd_error(1, "failed to bind to socket.");

	if (listen(listener, 10) == -1)
		darkircd_error(1, "failed to listen on undefined socket.");

	FD_SET(listener, &master);
	fdmax = listener;

	return 0;
}

void process_connections()
{
    int i, j, nbytes, addrlen, newfd;
    char buf[1024];
    struct sockaddr_in clientaddr;

    read_fds = master;

	if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
		darkircd_error(1, "failed to use select on undefined socket.");

	for (i = 0; i <= fdmax; i++)
	{
		if (FD_ISSET(i, &read_fds))
		{
			if (i == listener)
			{
				addrlen = sizeof(clientaddr);
				if ((newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
					darkircd_error(0, "couldnt accept the new connection");
				else
				{
					FD_SET(newfd, &master);
					if (newfd > fdmax)
					{
						fdmax = newfd;
					}
					//printf("New connection from %s on socket %d\n", inet_ntoa(clientaddr.sin_addr), newfd);
				}
			}
			else
			{
				if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
				{
					if (nbytes == 0)
						//printf("socket %d hung up\n", i);
					else
						darkircd_error(0, "couldnt use recv on socket");

					close(i);
					FD_CLR(i, &master);
				}
				else
				{
					for (j = 0; j <= fdmax; j++)
					{
						if (FD_ISSET(j, &master))
						{
							if (j != listener && j != i)
							{
								if (send(j, buf, nbytes, 0) == -1)
									darkircd_error(0, "couldnt use send on socket");
							}
						}
					}
				}
			}
		}
	}
}

