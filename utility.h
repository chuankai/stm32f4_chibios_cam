/*
 * utility.h
 *
 *  Created on: 2013/3/19
 *      Author: Kyle.Lin
 */

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdint.h>

extern void assert_failed(uint8_t* file, uint32_t line);

#define ASSERT(val)			val == 0 ? assert_failed((uint8_t *)__FILE__, __LINE__): (void)0;


int16_t I2C_Write(uint16_t I2CAddr, uint8_t Address, uint8_t Value);
int16_t I2C_Read(uint16_t I2CAddr, uint8_t *Value);
void Log(char *str);
void LogP1(char *str, uint32_t p);
#endif /* UTILITY_H_ */
