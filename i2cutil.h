/*
 * i2cutil.h
 *
 *  Created on: 2013/3/21
 *      Author: Kyle.Lin
 */

#ifndef I2CUTIL_H_
#define I2CUTIL_H_

int16_t I2C_Write(const uint16_t I2CAddr, const uint8_t reg, const uint8_t val);
int16_t I2C_Read(const uint16_t I2CAddr, const uint8_t reg, uint8_t *val);

#endif /* I2CUTIL_H_ */
