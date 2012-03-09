#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"

int init_server(int port)
{
	int yes = 1;
	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket failed :(");
		exit(1);
	}

	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		perror("setsockopt failed :(");
		exit(1);
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(port);
	memset(&(serveraddr.sin_zero), '\0', 8);

	if (bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
	{
		perror("bind failed :(");
		exit(1);
	}

	if (listen(listener, 10) == -1)
	{
		perror("listen failed :(");
		exit(1);
	}

	FD_SET(listener, &master);
	fdmax = listener;

	return 0;
}

void process_connections()
{
	read_fds = master;
	if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
	{
		perror("select failed :(");
		exit(1);
	}

	for (i = 0; i <= fdmax; i++)
	{
		if (FD_ISSET(i, &read_fds))
		{
			if (i == listener)
			{
				addrlen = sizeof(clientaddr);
				if ((newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
				{
					perror("accept failed :(");
				}
				else
				{
					FD_SET(newfd, &master);
					if (newfd > fdmax)
					{
						fdmax = newfd;
					}
					printf("New connection from %s on socket %d\n", inet_ntoa(clientaddr.sin_addr), newfd);
				}
			}
			else
			{
				if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
				{
					if (nbytes == 0)
						printf("socket %d hung up\n", i);
					else
						perror("recv failed :(");

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
									perror("send failed :(");
							}
						}
					}
				}
			}
		}
	}
}

