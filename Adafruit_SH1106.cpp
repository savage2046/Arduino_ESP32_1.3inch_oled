/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/
#include <stdlib.h>

#include <Wire.h>

#include "Adafruit_GFX.h"
#include "Adafruit_SH1106.h"

// the memory buffer for the LCD

static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8];

// the most basic function, set a single pixel
void Adafruit_SSD1306::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if ((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
    return;

  // check rotation, move pixel around if necessary
  switch (getRotation())
  {
  case 1:
    swap(x, y);
    x = WIDTH - x - 1;
    break;
  case 2:
    x = WIDTH - x - 1;
    y = HEIGHT - y - 1;
    break;
  case 3:
    swap(x, y);
    y = HEIGHT - y - 1;
    break;
  }

  // x is which column
  if (color == WHITE)
    buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= _BV((y % 8));
  else
    buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~_BV((y % 8));
}

// initializer for I2C - we only indicate the reset pin!
Adafruit_SSD1306::Adafruit_SSD1306() : Adafruit_GFX(SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT)
{
}

void Adafruit_SSD1306::begin()
{
  // I2C Init
  Wire.begin(); // Is this the right place for this?

  WriteCommand(0xAE); //display off

  WriteCommand(0x00); //set lower column address
  WriteCommand(0x10); //set higher column address

  WriteCommand(0x40); //set display start line

  WriteCommand(0xB0); //set page address

  WriteCommand(0x81); //对比度设置
  WriteCommand(0xCF); //0~255（对比度值……效果不是特别明显）

  WriteCommand(0xA1); //set segment remap

  WriteCommand(0xA6); //normal / reverse

  WriteCommand(0xA8); //multiplex ratio
  WriteCommand(0x3F); //duty = 1/64

  WriteCommand(0xC8); //Com scan direction

  WriteCommand(0xD3); //set display offset
  WriteCommand(0x00);

  WriteCommand(0xD5); //set osc division
  WriteCommand(0x80);

  WriteCommand(0xD9); //set pre-charge period
  WriteCommand(0xF1);

  WriteCommand(0xDA); //set COM pins
  WriteCommand(0x12);

  WriteCommand(0xDB); //set vcomh
  WriteCommand(0x40);

  WriteCommand(0x8D); //set charge pump enable
  WriteCommand(0x14);

  WriteCommand(0xAF); //display ON
}

void Adafruit_SSD1306::invertDisplay(uint8_t i)
{
  if (i)
  {
    WriteCommand(SSD1306_INVERTDISPLAY);
  }
  else
  {
    WriteCommand(SSD1306_NORMALDISPLAY);
  }
}

void Adafruit_SSD1306::WriteCommand(uint8_t c)
{

  // I2C
  uint8_t control = 0x00; // Co = 0, D/C = 0
  Wire.beginTransmission(SSD1306_I2C_ADDRESS);
  Wire.write(control);
  Wire.write(c);
  Wire.endTransmission();
}

// startscrollright
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void Adafruit_SSD1306::startscrollright(uint8_t start, uint8_t stop)
{
  WriteCommand(SSD1306_RIGHT_HORIZONTAL_SCROLL);
  WriteCommand(0X00);
  WriteCommand(start);
  WriteCommand(0X00);
  WriteCommand(stop);
  WriteCommand(0X01);
  WriteCommand(0XFF);
  WriteCommand(SSD1306_ACTIVATE_SCROLL);
}

// startscrollleft
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void Adafruit_SSD1306::startscrollleft(uint8_t start, uint8_t stop)
{
  WriteCommand(SSD1306_LEFT_HORIZONTAL_SCROLL);
  WriteCommand(0X00);
  WriteCommand(start);
  WriteCommand(0X00);
  WriteCommand(stop);
  WriteCommand(0X01);
  WriteCommand(0XFF);
  WriteCommand(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagright
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void Adafruit_SSD1306::startscrolldiagright(uint8_t start, uint8_t stop)
{
  WriteCommand(SSD1306_SET_VERTICAL_SCROLL_AREA);
  WriteCommand(0X00);
  WriteCommand(SSD1306_LCDHEIGHT);
  WriteCommand(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  WriteCommand(0X00);
  WriteCommand(start);
  WriteCommand(0X00);
  WriteCommand(stop);
  WriteCommand(0X01);
  WriteCommand(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagleft
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void Adafruit_SSD1306::startscrolldiagleft(uint8_t start, uint8_t stop)
{
  WriteCommand(SSD1306_SET_VERTICAL_SCROLL_AREA);
  WriteCommand(0X00);
  WriteCommand(SSD1306_LCDHEIGHT);
  WriteCommand(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  WriteCommand(0X00);
  WriteCommand(start);
  WriteCommand(0X00);
  WriteCommand(stop);
  WriteCommand(0X01);
  WriteCommand(SSD1306_ACTIVATE_SCROLL);
}

void Adafruit_SSD1306::stopscroll(void)
{
  WriteCommand(SSD1306_DEACTIVATE_SCROLL);
}

void Adafruit_SSD1306::ssd1306_data(uint8_t c)
{                         // I2C
  uint8_t control = 0x40; // Co = 0, D/C = 1
  Wire.beginTransmission(SSD1306_I2C_ADDRESS);
  Wire.write(control);
  Wire.write(c);
  Wire.endTransmission();
}

void Adafruit_SSD1306::setPosition(uint8_t x, uint8_t y)
{
  WriteCommand(0xb0 | (y & 0x0f));         //page 0-7
  WriteCommand(((x & 0xf0) >> 4) | 0x10); //|0x10 higher column
  WriteCommand(x & 0x0f);                 //|0x00 lower column
}

void Adafruit_SSD1306::display(void)
{
  // I2C
  for (uint16_t y = 0; y < (SSD1306_LCDHEIGHT / 8); y++)
  {
    setPosition(0, y);
    for (uint16_t x = 0; x < SSD1306_LCDWIDTH; x++)
    {
      // send a bunch of data in one xmission
      Wire.beginTransmission(SSD1306_I2C_ADDRESS);
      Wire.write(0x40);
      Wire.write(buffer[y * SSD1306_LCDWIDTH + x]);
      Wire.endTransmission();
    }
  }

  // WriteCommand(SSD1306_SETLOWCOLUMN | 0x0);  // low col = 0
  // WriteCommand(SSD1306_SETHIGHCOLUMN | 0x0); // hi col = 0
  // WriteCommand(SSD1306_SETSTARTLINE | 0x0);  // line #0

  // // I2C
  // for (uint16_t i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++)
  // {
  //   // send a bunch of data in one xmission
  //   Wire.beginTransmission(SSD1306_I2C_ADDRESS);
  //   Wire.write(0x40);
  //   for (uint8_t x = 0; x < 16; x++)
  //   {
  //     Wire.write(buffer[i]);
  //     i++;
  //   }
  //   Wire.endTransmission();
  // }
}

// clear everything
void Adafruit_SSD1306::clearDisplay(void)
{
  memset(buffer, 0, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8));
}
