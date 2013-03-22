/*
 * i2cutil.c
 *
 *  Created on: 2013/3/21
 *      Author: Kyle.Lin
 */

#include "ch.h"
#include "hal.h"

int16_t I2C_Write(const uint16_t I2CAddr, const uint8_t reg, const uint8_t val)
{
	msg_t err = RDY_OK;
	uint8_t txbuf[2];

	txbuf[0] = reg;
	txbuf[1] = val;
	err = i2cMasterTransmitTimeout(&I2CD2, I2CAddr, txbuf, sizeof(txbuf), 0, 0,
			MS2ST(50) );

	return err;
}

int16_t I2C_Read(const uint16_t I2CAddr, const uint8_t reg, uint8_t *val)
{
	msg_t err;

	err = i2cMasterTransmitTimeout(&I2CD2, I2CAddr, reg, sizeof(reg), 0, 0,
			MS2ST(50) );
	if (err != RDY_OK)
		return err;

	err = i2cMasterReceiveTimeout(&I2CD2, I2CAddr, val, sizeof(*val),
			MS2ST(50) );

	return err;
}
