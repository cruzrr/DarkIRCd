/*
 * DarkIRCd - Small and Lightweight TS6 IRCd
 *
 * http://www.github.com/cruzrr/DarkIRCd
 * Copyright 2012 (C) Cruzrr
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "server.h"

int main(int argc, char *argv[])
{
	init_server(6667);

	for(;;)
	{
		process_connections();
	}
}
