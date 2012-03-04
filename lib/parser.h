#ifndef PARSER_H
#define PARSER_H

typedef struct _c
{
	char *command;
	char *prefix;
	char *postfix;
	int arg_count;
} ircClientRaw;

typedef struct _s {
    char *sid;
    char *command;
    char *args;
} ircServerRaw;

#endif
