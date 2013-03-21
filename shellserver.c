/*
 * shellserver.c
 *
 *  Created on: 2013/3/21
 *      Author: Kyle.Lin
 */

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

static WORKING_AREA(waShellServerThread, 512);
static ShellConfig cfg;

void test_cmd(BaseChannel *chp, int argc, char *argv[]);

static ShellCommand cmdtbl[] =
{
    { "test", test_cmd },
    { NULL, NULL }
};

void test_cmd(BaseChannel *chp, int argc, char *argv[])
{
	uint8_t i;

	chprintf(chp, "test: ");
	for (i = 0; i < argc; i++)
	{
		chprintf(chp, "%d ", *argv[i]);
	}
	chprintf(chp, "OK\r\n");
}

void createShell(void)
{
	shellInit();

	cfg.sc_channel = (BaseChannel *) &SD2;
	cfg.sc_commands = cmdtbl;

	shellCreateStatic(&cfg, waShellServerThread, sizeof(waShellServerThread), 32);
}
