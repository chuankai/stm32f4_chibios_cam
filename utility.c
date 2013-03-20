/*
 * utility.c
 *
 *  Created on: 2013/3/19
 *      Author: Kyle.Lin
 */

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "utility.h"

int16_t I2C_Write(uint16_t I2CAddr, uint8_t Address, uint8_t Value)
{
	msg_t err = RDY_OK;
	uint8_t txbuf[2];

	txbuf[0] = Address;
	txbuf[1] = Value;
	err = i2cMasterTransmitTimeout(&I2CD2, I2CAddr, txbuf, sizeof(txbuf), 0, 0,
			MS2ST(50) );

	return err;
}

int16_t I2C_Read(uint16_t I2CAddr, uint8_t *Value)
{
	msg_t err;
	uint8_t txbuf[1], rxbuf[1];

	txbuf[0] = 0x0A;
	err = i2cMasterTransmitTimeout(&I2CD2, I2CAddr, txbuf, sizeof(txbuf), 0, 0,
			MS2ST(50) );
	if (err != RDY_OK)
		return err;
	err = i2cMasterReceiveTimeout(&I2CD2, I2CAddr, rxbuf, sizeof(rxbuf),
			MS2ST(50) );
	if (err == RDY_OK)
		*Value = rxbuf[0];

	return err;
}
