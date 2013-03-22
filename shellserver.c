/*
 * shellserver.c
 *
 *  Created on: 2013/3/21
 *      Author: Kyle.Lin
 */

#include "stdlib.h"
#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "i2cutil.h"
#include "logserver.h"

static WORKING_AREA(waShellServerThread, 512);
static ShellConfig cfg;

static void i2r_cmd(BaseChannel *chp, int argc, char *argv[]);
static void log_cmd(BaseChannel *chp, int argc, char *argv[]);

static ShellCommand cmdtbl[] =
{
{ "i2r", i2r_cmd },
{ "log", log_cmd },
{ NULL, NULL } };

static void i2r_cmd(BaseChannel *chp, int argc, char *argv[])
{
	if (argc < 2)
	{
		chprintf(chp, "Usage: i2r addr reg\r\n");
	}
	else
	{
		uint16_t err;
		uint8_t val;

		err = I2C_Read(atoi(argv[0]), atoi(argv[1]), &val);
		if (err == 0)
		{
			chprintf(chp, "%02X\r\n", val);
			chprintf(chp, "OK\r\n");
		}
		else
		{
			chprintf(chp, "ERR:%d\r\n", err);

		}
	}
}

static void log_cmd(BaseChannel *chp, int argc, char *argv[])
{
	if (argc < 1)
	{
		chprintf(chp, "Usage: log [0|1]\r\n");
	}
	else
	{
		logEnable(atoi(argv[0]));
	}
}

void createShell(void)
{
	shellInit();

	cfg.sc_channel = (BaseChannel *) &SD2;
	cfg.sc_commands = cmdtbl;

	shellCreateStatic(&cfg, waShellServerThread, sizeof(waShellServerThread),
			32);
}
