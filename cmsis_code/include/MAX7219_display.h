#ifndef MAX7219_DISPLAY_H
#define MAX7219_DISPLAY_H

#include "stm32f4xx.h"
#include <stdint.h>

#define DISP_COL 	 8
#define DISP_ROW	 1

#define X_MAX			 DISP_COL*8-1
#define Y_MAX			 DISP_ROW*8-1


void SPI_Config(void);
void SPI_Select(void);
void SPI_Deselect(void);
uint8_t SPI_Transmit(uint8_t);
void MAX7219_sendCommand(uint8_t, uint8_t);
void MAX7219_SendCommandStealth(uint8_t, uint8_t);
void MAX7219_DisplayTest(void);
void MAX7219_ScanLimit(void);
void MAX7219_DecodeMode(void);
void MAX7219_ClearDisplay(void);
void MAX2719_SetIntensity(uint8_t);
void MAX7219_TurnOn(void);
void MAX7219_Init(void);
void MAX7219_UpdateDisplay(void);
void MAX7219_SetPoint(int16_t,int16_t);
void MAX7219_ClearVirtualDisplay(void);

#endif // MAX7219_DISPLAY_H