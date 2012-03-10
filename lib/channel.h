#ifndef CHANNEL_H
#define CHANNEL_H

typedef struct channel {
	char *channelname;
	int creationtime;
	char **modes[];
	int modecount;
	char *topic;
	char **userlist[];
} channel;

#endif

