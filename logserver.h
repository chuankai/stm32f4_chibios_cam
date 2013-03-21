/*
 * logserver.h
 *
 *  Created on: 2013/3/21
 *      Author: Kyle.Lin
 */

#ifndef LOGSERVER_H_
#define LOGSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ch.h"

extern Mailbox logMB;
extern MemoryPool logMP;

//TODO: snprintf requires syscall.c
extern char msgbuf[];
#define LOGMSG(...)		{ snprintf(msgbuf, 80, __VA_ARGS__); \
						  logmsg(msgbuf); }

void createLogServerThrd(void);
void logmsg(char *str);

#endif /* LOGSERVER_H_ */
