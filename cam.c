/*
 * cam.c
 *
 *  Created on: 2013/3/18
 *      Author: Kyle.Lin
 */

#include "stm32f4xx_conf.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "cam.h"
#include "OV7670.h"

#define HOST_I2C                      	I2C2
#define HOST_I2C_ADDRESS			  	0x55
#define HOST_I2C_CLK                  	RCC_APB1Periph_I2C2
#define HOST_I2C_GPIO_CLOCK           	RCC_AHB1Periph_GPIOB
#define HOST_I2C_GPIO_AF              	GPIO_AF_I2C2
#define HOST_I2C_GPIO                 	GPIOB
#define HOST_I2C_SCL_PIN              	GPIO_Pin_10
#define HOST_I2C_SDA_PIN              	GPIO_Pin_11
#define HOST_I2C_SCL_PINSRC           	GPIO_PinSource10
#define HOST_I2C_SDA_PINSRC           	GPIO_PinSource11

static WORKING_AREA(waCamThread, 512);
static msg_t CamThread(void *arg)
{
	uint32_t err;
	I2CConfig ic;
	NVIC_InitTypeDef NVIC_InitStructure;

	(void) arg;

	chRegSetThreadName("cam");

//	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(HOST_I2C_GPIO_CLOCK, ENABLE);

//	GPIO_InitStructure.GPIO_Pin = HOST_I2C_SCL_PIN | HOST_I2C_SDA_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(HOST_I2C_GPIO, &GPIO_InitStructure);
//
//	GPIO_PinAFConfig(HOST_I2C_GPIO, HOST_I2C_SCL_PINSRC, HOST_I2C_GPIO_AF );
//	GPIO_PinAFConfig(HOST_I2C_GPIO, HOST_I2C_SDA_PINSRC, HOST_I2C_GPIO_AF );

	palSetGroupMode(GPIOB, 0b0000110000000000,
			0,
			//FEDCBA9876543210
			PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUDR_FLOATING | PAL_STM32_OSPEED_MID2);

	ic.op_mode = OPMODE_I2C;
	ic.clock_speed = 100000;
	ic.duty_cycle = STD_DUTY_CYCLE;
	i2cStart(&I2CD2, &ic);

	err = Camera_Init();
//	ASSERT(err);

	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DCMI_ITConfig(DCMI_IT_FRAME, DISABLE);	//FIXME
	DCMI_Cmd(ENABLE);
	DCMI_CaptureCmd(ENABLE);
	DMA_Cmd(DMA_CameraToRAM_Stream, ENABLE);

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
	chThdCreateStatic(waCamThread, sizeof(waCamThread), HIGHPRIO, CamThread,
			NULL );
}
