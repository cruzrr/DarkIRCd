#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "parser.h"

ircClientRaw client_parse(char *str)
{
    char *save = str;
    int i,j = 0;
    ircClientRaw ret;

    for(i = 0;(*str != ' ') && (*str != '\0'); *str++) i++;
    ret.command = strndup(save, i);
    if(*str == '\0')
    {
        ret.prefix  = "";
        ret.postfix = "";
        return ret;
    }
    while((*str == ' ') && (*str != '\0')) *str++;
    save = str;
    if(*str == '\0')
    {
        ret.prefix  = "";
        ret.postfix = "";
        return ret;
    }
    for(i = 0; (*str != ':') && (*str != '\0'); i++) *str++;
    if(*str == '\0')
    {
        ret.prefix = "";
        ret.postfix = "";
        return ret;
    }
    ret.prefix = strndup(save, i);
    char *tmp = ret.prefix;
    for(i = 0; *tmp != '\0'; *tmp++ ) if(*tmp == ' ') i++;
    ret.arg_count = i + 1;
    *str++;
    ret.postfix = str;
    return ret;
}

ircServerRaw server_parse(char *str)
{
    ircServerRaw ret;
    int i;
    int j;
    char *save = str;
    for(i=0; *str != ' '; *str++) i++;
    ret.sid = strndup(save, i);
    *str++;
    save = str;
    for(j=0; *str != ' '; *str++) j++;
    ret.command = strndup(save, j);
    *str++;
    ret.args = str;
    return ret;
}