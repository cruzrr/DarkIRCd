#ifndef USER_H
#define USER_H

typedef struct client {
	char *UID;
	char *nick;
	char *host;
	char *username;
	char *realname;
	int lastpong;
} client;

#endif
