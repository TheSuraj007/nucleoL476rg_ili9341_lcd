/*
 * ili9341_stm32_driver.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Surajkumar
 */
#include "ili9341_stm32_driver.h"

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Deselect when Tx Complete */
  if(hspi == HSPI_INSTANCE)
  {
	  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
  }
}

static void ILI9341_SPI_Tx(uint8_t data)
{
	while(!__HAL_SPI_GET_FLAG(HSPI_INSTANCE, SPI_FLAG_TXE));
	HAL_SPI_Transmit_IT(HSPI_INSTANCE, &data, 1);
//	HAL_SPI_Transmit_DMA(HSPI_INSTANCE, &data, 1);
//	HAL_SPI_Transmit(HSPI_INSTANCE, &data, 1, 10);
}

static void ILI9341_SPI_TxBuffer(uint8_t *buffer, uint16_t len)
{
	while(!__HAL_SPI_GET_FLAG(HSPI_INSTANCE, SPI_FLAG_TXE));
	HAL_SPI_Transmit_IT(HSPI_INSTANCE, buffer, len);
//	HAL_SPI_Transmit_DMA(HSPI_INSTANCE, buffer, len);
//	HAL_SPI_Transmit(HSPI_INSTANCE, buffer, len, 10);
}

void ILI9341_WriteCommand(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	//command
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	//select
	ILI9341_SPI_Tx(cmd);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);	//deselect
}

void ILI9341_WriteData(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	//data
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	//select
	ILI9341_SPI_Tx(data);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);	//deselect
}

void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	//data
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	//select
	ILI9341_SPI_TxBuffer(buffer, len);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);	//deselect
}

void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint8_t buffer[4];
	buffer[0] = x1 >> 8;
	buffer[1] = x1;
	buffer[2] = x2 >> 8;
	buffer[3] = x2;

	ILI9341_WriteCommand(0x2A);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	buffer[0] = y1 >> 8;
	buffer[1] = y1;
	buffer[2] = y2 >> 8;
	buffer[3] = y2;

	ILI9341_WriteCommand(0x2B);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	ILI9341_WriteCommand(0x2C);
}

void ILI9341_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);	//Disable
	HAL_Delay(10);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		//Select
	HAL_Delay(10);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);		//Enable
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET); 		//Deselect
}

void ILI9341_Enable(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);		//Enable
}

void ILI9341_Init(void)
{
	ILI9341_Enable();
	ILI9341_Reset();

	//SOFTWARE RESET
	ILI9341_WriteCommand(0x01);
	HAL_Delay(10);

	//POWER CONTROL A
	ILI9341_WriteCommand(0xCB);
	ILI9341_WriteData(0x39);
	ILI9341_WriteData(0x2C);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x34);
	ILI9341_WriteData(0x02);

	//POWER CONTROL B
	ILI9341_WriteCommand(0xCF);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_WriteCommand(0xE8);
	ILI9341_WriteData(0x85);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_WriteCommand(0xEA);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_WriteCommand(0xED);
	ILI9341_WriteData(0x64);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x12);
	ILI9341_WriteData(0x81);

	//PUMP RATIO CONTROL
	ILI9341_WriteCommand(0xF7);
	ILI9341_WriteData(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_WriteCommand(0xC0);
	ILI9341_WriteData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_WriteCommand(0xC1);
	ILI9341_WriteData(0x10);

	//VCM CONTROL
	ILI9341_WriteCommand(0xC5);
	ILI9341_WriteData(0x3E);
	ILI9341_WriteData(0x28);

	//VCM CONTROL 2
	ILI9341_WriteCommand(0xC7);
	ILI9341_WriteData(0x86);

	//MEMORY ACCESS CONTROL
	ILI9341_WriteCommand(0x36);
	ILI9341_WriteData(0x48);

	//PIXEL FORMAT
	ILI9341_WriteCommand(0x3A);
	ILI9341_WriteData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_WriteCommand(0xB1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x18);

	//DISPLAY FUNCTION CONTROL
	ILI9341_WriteCommand(0xB6);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x82);
	ILI9341_WriteData(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_WriteCommand(0xF2);
	ILI9341_WriteData(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_WriteCommand(0x26);
	ILI9341_WriteData(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE0);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x2B);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x4E);
	ILI9341_WriteData(0xF1);
	ILI9341_WriteData(0x37);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x10);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x09);
	ILI9341_WriteData(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x14);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x11);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x48);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x36);
	ILI9341_WriteData(0x0F);

	//EXIT SLEEP
	ILI9341_WriteCommand(0x11);
	HAL_Delay(100);

	//TURN ON DISPLAY
	ILI9341_WriteCommand(0x29);

	//STARTING ROTATION
	ILI9341_SetRotation(SCREEN_VERTICAL_1);
}

void ILI9341_SetRotation(uint8_t rotation)
{
	ILI9341_WriteCommand(0x36);
	HAL_Delay(1);

	switch(rotation)
	{
	case SCREEN_VERTICAL_1:
		ILI9341_WriteData(0x40|0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		ILI9341_WriteData(0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		ILI9341_WriteData(0x80|0x08);
		LCD_WIDTH  = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		ILI9341_WriteData(0x40|0x80|0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		break;
	}
}

void ILI9341_DrawColor(uint16_t color)
{
	uint8_t buffer[2] = {color>>8, color};
	ILI9341_WriteBuffer(buffer, sizeof(buffer));
}

void ILI9341_DrawColorBurst(uint16_t color, uint32_t size)
{
	uint32_t BufferSize = 0;

	if((size*2) < BURST_MAX_SIZE)
	{
		BufferSize = size;
	}
	else
	{
		BufferSize = BURST_MAX_SIZE;
	}

	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

	uint8_t chifted = color>>8;
	uint8_t BurstBuffer[BufferSize];

	for(uint32_t j = 0; j < BufferSize; j+=2)
	{
		BurstBuffer[j] = chifted;
		BurstBuffer[j+1] = color;
	}

	uint32_t SendingSize = size * 2;
	uint32_t SendingInBlock = SendingSize / BufferSize;
	uint32_t RemainderFromBlock = SendingSize % BufferSize;

	if(SendingInBlock != 0)
	{
		for(uint32_t j = 0; j < (SendingInBlock); j++)
		{
			HAL_SPI_Transmit(HSPI_INSTANCE, BurstBuffer, BufferSize, 10);
		}
	}

	HAL_SPI_Transmit(HSPI_INSTANCE, BurstBuffer, RemainderFromBlock, 10);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void ILI9341_FillScreen(uint16_t color)
{
	ILI9341_SetAddress(0, 0, LCD_WIDTH, LCD_HEIGHT);
	ILI9341_DrawColorBurst(color, LCD_WIDTH*LCD_HEIGHT);
}

void ILI9341_DrawPixel(uint16_t x,uint16_t y,uint16_t color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	uint8_t bufferX[4] = {x>>8, x, (x+1)>>8, (x+1)};
	uint8_t bufferY[4] = {y>>8, y, (y+1)>>8, (y+1)};
	uint8_t bufferC[2] = {color>>8, color};

	ILI9341_WriteCommand(0x2A);						//ADDRESS
	ILI9341_WriteBuffer(bufferX, sizeof(bufferX));	//XDATA

	ILI9341_WriteCommand(0x2B);						//ADDRESS
	ILI9341_WriteBuffer(bufferY, sizeof(bufferY));	//YDATA

	ILI9341_WriteCommand(0x2C);						//ADDRESS
	ILI9341_WriteBuffer(bufferC, sizeof(bufferC));	//COLOR
}

void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH)
	{
		width=LCD_WIDTH-x;
	}

	if((y+height-1)>=LCD_HEIGHT)
	{
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x+width-1, y+height-1);
	ILI9341_DrawColorBurst(color, height*width);
}

void ILI9341_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH)
	{
		width=LCD_WIDTH-x;
	}

	ILI9341_SetAddress(x, y, x+width-1, y);
	ILI9341_DrawColorBurst(color, width);
}

void ILI9341_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((y+height-1)>=LCD_HEIGHT)
	{
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x, y+height-1);
	ILI9341_DrawColorBurst(color, height);
}

/**************************************************************************************/
void drawFastHLine(int16_t x, int16_t y,int16_t w, uint16_t color)
{
	writeFastHLine(x, y, w, color);
}

void drawFastVLine(int16_t x, int16_t y,int16_t h, uint16_t color)
{
  writeFastVLine(x, y, h, color);
}
/**************************************************************************************/
void drawEllipseHelper(int32_t x, int32_t y,int32_t rx, int32_t ry,uint8_t cornername, uint16_t color)
{
  if (rx < 0 || ry < 0 || ((rx == 0) && (ry == 0)))
  {
    return;
  }
  if (ry == 0)
  {
    drawFastHLine(x - rx, y, (ry << 2) + 1, color);
    return;
  }
  if (rx == 0)
  {
    drawFastVLine(x, y - ry, (rx << 2) + 1, color);
    return;
  }

  int32_t xt, yt, s, i;
  int32_t rx2 = rx * rx;
  int32_t ry2 = ry * ry;

  i = -1;
  xt = 0;
  yt = ry;
  s = (ry2 << 1) + rx2 * (1 - (ry << 1));
  do
  {
    while (s < 0)
      s += ry2 * ((++xt << 2) + 2);
    if (cornername & 0x1)
    {
      writeFastHLine(x - xt, y - yt, xt - i, color);
    }
    if (cornername & 0x2)
    {
      writeFastHLine(x + i + 1, y - yt, xt - i, color);
    }
    if (cornername & 0x4)
    {
      writeFastHLine(x + i + 1, y + yt, xt - i, color);
    }
    if (cornername & 0x8)
    {
      writeFastHLine(x - xt, y + yt, xt - i, color);
    }
    i = xt;
    s -= (--yt) * rx2 << 2;
  } while (ry2 * xt <= rx2 * yt);

  i = -1;
  yt = 0;
  xt = rx;
  s = (rx2 << 1) + ry2 * (1 - (rx << 1));
  do
  {
    while (s < 0)
      s += rx2 * ((++yt << 2) + 2);
    if (cornername & 0x1)
    {
      writeFastVLine(x - xt, y - yt, yt - i, color);
    }
    if (cornername & 0x2)
    {
      writeFastVLine(x + xt, y - yt, yt - i, color);
    }
    if (cornername & 0x4)
    {
      writeFastVLine(x + xt, y + i + 1, yt - i, color);
    }
    if (cornername & 0x8)
    {
      writeFastVLine(x - xt, y + i + 1, yt - i, color);
    }
    i = yt;
    s -= (--xt) * ry2 << 2;
  } while (rx2 * yt <= ry2 * xt);
}

/**************************************************************************************/
void writeFillRectPreclipped(int16_t x, int16_t y, int16_t w, int16_t h,
                                          uint16_t color)
{
  // Overwrite in subclasses if desired!
  for (int16_t i = y; i < y + h; i++)
  {
    writeFastHLine(x, i, w, color);
  }
}
/**************************************************************************************/
void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color)
{
  if (w && h)
  { // Nonzero width and height?
    if (w < 0)
    {             // If negative width...
      x += w + 1; //   Move X to left edge
      w = -w;     //   Use positive width
    }
    if (x <= ILI9341_SCREEN_WIDTH-1)
    { // Not off right
      if (h < 0)
      {             // If negative height...
        y += h + 1; //   Move Y to top edge
        h = -h;     //   Use positive height
      }
      if (y <= ILI9341_SCREEN_HEIGHT-1)
      { // Not off bottom
        int16_t x2 = x + w - 1;
        if (x2 >= 0)
        { // Not off left
          int16_t y2 = y + h - 1;
          if (y2 >= 0)
          { // Not off top
            // Rectangle partly or fully overlaps screen
            if (x < 0)
            {
              x = 0;
              w = x2 + 1;
            } // Clip left
            if (y < 0)
            {
              y = 0;
              h = y2 + 1;
            } // Clip top
            if (x2 > ILI9341_SCREEN_WIDTH-1)
            {
              w = ILI9341_SCREEN_WIDTH-1 - x + 1;
            } // Clip right
            if (y2 > ILI9341_SCREEN_HEIGHT-1)
            {
              h = ILI9341_SCREEN_HEIGHT-1 - y + 1;
            } // Clip bottom
            writeFillRectPreclipped(x, y, w, h, color);
          }
        }
      }
    }
  }
}

/**************************************************************************************/
void writeFastHLine(int16_t x, int16_t y,int16_t w, uint16_t color)
{
  for (int16_t i = x; i < x + w; i++)
  {
	  ILI9341_DrawPixel(i, y, color);
  }
}


void writeFastVLine(int16_t x, int16_t y,
                                 int16_t h, uint16_t color)
{
  for (int16_t i = y; i < y + h; i++)
  {
	  ILI9341_DrawPixel(x, i, color);
  }
}

/*****************************************************************************************/
void fillEllipseHelper(int32_t x, int32_t y,int32_t rx, int32_t ry,uint8_t corners, int16_t delta, uint16_t color)
{
  if (rx < 0 || ry < 0 || ((rx == 0) && (ry == 0)))
  {
    return;
  }
  if (ry == 0)
  {
    drawFastHLine(x - rx, y, (ry << 2) + 1, color);
    return;
  }
  if (rx == 0)
  {
    drawFastVLine(x, y - ry, (rx << 2) + 1, color);
    return;
  }

  int32_t xt, yt, i;
  int32_t rx2 = (int32_t)rx * rx;
  int32_t ry2 = (int32_t)ry * ry;
  int32_t s;

  writeFastHLine(x - rx, y, (rx << 1) + 1, color);
  i = 0;
  yt = 0;
  xt = rx;
  s = (rx2 << 1) + ry2 * (1 - (rx << 1));
  do
  {
    while (s < 0)
    {
      s += rx2 * ((++yt << 2) + 2);
    }
    if (corners & 1)
    {
      writeFillRect(x - xt, y - yt, (xt << 1) + 1 + delta, yt - i, color);
    }
    if (corners & 2)
    {
      writeFillRect(x - xt, y + i + 1, (xt << 1) + 1 + delta, yt - i, color);
    }
    i = yt;
    s -= (--xt) * ry2 << 2;
  } while (rx2 * yt <= ry2 * xt);

  xt = 0;
  yt = ry;
  s = (ry2 << 1) + rx2 * (1 - (ry << 1));
  do
  {
    while (s < 0)
    {
      s += ry2 * ((++xt << 2) + 2);
    }
    if (corners & 1)
    {
      writeFastHLine(x - xt, y - yt, (xt << 1) + 1 + delta, color);
    }
    if (corners & 2)
    {
      writeFastHLine(x - xt, y + yt, (xt << 1) + 1 + delta, color);
    }
    s -= (--yt) * rx2 << 2;
  } while (ry2 * xt <= rx2 * yt);
}
