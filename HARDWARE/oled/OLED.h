#ifndef __OLED_H__
#define __OLED_H__
#include "main.h"

void OLED_WriteCommand(uint8_t cmd);
void OLED_WriteData(uint8_t data, uint8_t Mode);
void OLED_Init(void);
void OLED_Fill(uint8_t DAT);
void OLED_SetCursor(uint8_t Y, uint8_t X);
#endif
