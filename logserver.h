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

#define LOG_MSG_MAX_LENGTH			80

extern char msgbuf[];
#define LOGMSG(...)		{ snprintf(msgbuf, 80, __VA_ARGS__); \
						  logMsg(msgbuf); }

void createLogServerThrd(void);
void logMsg(char *str);
void logEnable(uint8_t en);

#endif /* LOGSERVER_H_ */
