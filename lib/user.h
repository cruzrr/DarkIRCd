#ifndef USER_H
#define USER_H

typedef struct client {
	char *UID;
	char *nick;
	char *host;
	char *username;
	char *realname;
	char **modes[];
	int modecount;
	int lastpong;
} client;

#endif
