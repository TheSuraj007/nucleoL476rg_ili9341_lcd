/*
 * ili9341_gfx.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Surajkumar
 */

#ifndef INC_ILI9341_GFX_H_
#define INC_ILI9341_GFX_H_

#include "stm32l4xx_hal.h"
#include "fonts.h"

#define HORIZONTAL_IMAGE	0
#define VERTICAL_IMAGE		1

void ILI9341_DrawHollowCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color);
void ILI9341_DrawFilledCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color);
void ILI9341_DrawHollowRectangleCoord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color);
void ILI9341_DrawFilledRectangleCoord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color);
void ILI9341_DrawChar(char ch, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);
void ILI9341_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);
void ILI9341_DrawImage(const uint8_t* image, uint8_t orientation);

void drawRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, uint16_t color);
void fillRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, uint16_t color);


#endif /* INC_ILI9341_GFX_H_ */
