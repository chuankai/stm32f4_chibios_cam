#ifndef _SSD1289_H_
#define _SSD1289_H_

#include <stddef.h>
#include <stdio.h>
#include "app_stm32f4xx.h"
#include "AsciiLib.h"

// LCD -> FSMC_Bank1_NOR/SRAM1 and NE1 is like !CS
#define LCD_REG       (*((volatile unsigned short *) 0x60000000)) // RS = 0
#define LCD_RAM       (*((volatile unsigned short *) 0x60020000)) // RS = 1

// New FunctionalState for LCD operations
#define SLEEP 		2

// Colors for LCD Module
#define White        0xFFFF
#define Black        0x0000
#define Grey         0xF7DE
#define Blue         0xF800
#define Blue2        0xFD00
#define Red          0x001F
#define Magenta      0xF81F
#define Green        0x07E0
#define Cyan         0xFFEF
#define Yellow       0x07FF

void LCD_Init_SSD1289(void);
void LCD_SetFunctionalState(FunctionalState NewState);
void LCD_SetCursor(uint16_t PosX,uint16_t PosY);
void LCD_Clear(uint16_t Color);
void LCD_BackLight(uint8_t Percent);
void LCD_SetPoint(uint16_t PosX, uint16_t PosY, uint16_t Color);
void LCD_PutChar(uint16_t PosX, uint16_t PosY, unsigned char c, uint16_t CharColor,
				 uint16_t BackColor);
void LCD_GUI_Text(uint16_t PosX, uint16_t PosY, uint8_t *str,
			 	  uint16_t TextColor, uint16_t BackColor);
void LCD_DrawCalibPoint(uint16_t PosX, uint16_t PosY);
__inline void LCD_WriteRAM_Prepare(void);
__inline void LCD_WriteRAM(uint16_t RGB_Code);

#endif /* SSD1289_H_ */
