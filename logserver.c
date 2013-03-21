/*
 * logserver.c
 *
 *  Created on: 2013/3/21
 *      Author: Kyle.Lin
 */

#include <string.h>
#include "ch.h"
#include "chprintf.h"
#include "hal.h"

#define LOG_MSG_MB_SIZE 			64
#define LOG_MSG_MP_SIZE				64
#define LOG_MSG_MAX_LENGTH			80

static char logMPbuffer[LOG_MSG_MP_SIZE][LOG_MSG_MAX_LENGTH];
static MEMORYPOOL_DECL(logMP, LOG_MSG_MAX_LENGTH, NULL);
static msg_t logMBbuffer[LOG_MSG_MB_SIZE];
static MAILBOX_DECL(logMB, logMBbuffer, LOG_MSG_MB_SIZE);

char msgbuf[LOG_MSG_MAX_LENGTH];

static WORKING_AREA(waLogServerThread, 128);

static msg_t logServerThrd(void *arg);

void createLogServerThrd(void)
{
	chThdCreateStatic(waLogServerThread, sizeof(waLogServerThread), LOWPRIO,logServerThrd, NULL);
}

static msg_t logServerThrd(void *arg)
{
	int i;

	(void) arg;
	chRegSetThreadName("log");

	sdStart(&SD2, NULL);
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));

	chprintf((BaseChannel *) &SD2, "Log server started\r\n");

//	chPoolInit(&logMP, LOG_MSG_MAX_LENGTH, NULL);

	for (i = 0; i < LOG_MSG_MP_SIZE; i++)
	{
	    chPoolFree(&logMP, logMPbuffer[i]);
	}

//	chMBInit(&logMB, logmsgbuf, sizeof(logmsgbuf));

	msg_t m, res;

	while (TRUE)
	{
		 res = chMBFetch(&logMB, &m, TIME_INFINITE);
		 if (res == RDY_OK)
		 {
				chprintf((BaseChannel *) &SD2,(char *)m);
				chPoolFree(&logMP, (void *)m);
		 }
	}

	return -1;
}

void logmsg(char *str)
{
	msg_t m;

	m = (msg_t)chPoolAlloc(&logMP);
	if ((void *)m != NULL)
	{
		strncpy((char *)m, str, LOG_MSG_MAX_LENGTH);
		((char *)m)[LOG_MSG_MAX_LENGTH - 1] = '\0';
		chMBPost(&logMB, m, TIME_IMMEDIATE );
	}
}

