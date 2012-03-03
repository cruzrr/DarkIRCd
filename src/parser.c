#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.h"

typedef struct _s {
    char *command;
    char *prefix;
    char *postfix;
} event;

event parse(char *str)
{
    char *save = str;
    int i,j = 0;
    event ret;
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
    *str++;
    ret.postfix = str;
    return ret;
}
