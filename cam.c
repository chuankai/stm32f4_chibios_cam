/*
 * cam.c
 *
 *  Created on: 2013/3/18
 *      Author: Kyle.Lin
 */

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "cam.h"
#include "utility.h"
#include "OV7670.h"

static WORKING_AREA(waCamThread, 128);
static msg_t CamThread(void *arg)
{
	uint32_t err;
	I2CConfig ic;

	(void) arg;

	chRegSetThreadName("cam");

	ic.op_mode = OPMODE_I2C;
	ic.clock_speed = 100000;
	ic.duty_cycle = STD_DUTY_CYCLE;
	i2cStart(&I2CD2, &ic);

	err = Camera_Init();
	ASSERT(err);

	while (TRUE)
	{
		palSetPad(GPIOD, GPIOD_LED3);
		/* Orange.  */
		chThdSleepMilliseconds(500);
		palClearPad(GPIOD, GPIOD_LED3);
		/* Orange.  */
		chThdSleepMilliseconds(500);
	}
}

void CreateCamThread(void)
{
	chThdCreateStatic(waCamThread, sizeof(waCamThread), NORMALPRIO, CamThread,
			NULL );
}
