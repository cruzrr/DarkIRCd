#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void darkircd_error(int type, char *err)
{
	if (type == 0)
		perror("WARNING: %s", err);
	else {
		perror("FATAL: %s", err);
		exit(1);
	}
}
