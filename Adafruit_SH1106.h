#ifndef _ADAFRUIT_SH1106_H
#define _ADAFRUIT_SH1106_H

#include "Arduino.h"

#include <Adafruit_GFX.h>

#define BLACK 0
#define WHITE 1

#define SSD1306_I2C_ADDRESS 0x3C  //oled address

//////////////important/////////////////////////////////////////
#define SSD1306_LCDWIDTH 132     //change if not same
#define SSD1306_LCDHEIGHT 64     //change if not same
/////////////////////////////////////////////////////////////////

#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

class Adafruit_SSD1306 : public Adafruit_GFX
{
public:
  Adafruit_SSD1306(void);

  void begin();

  void clearDisplay(void);
  void invertDisplay(uint8_t i);
  void display();

  void startscrollright(uint8_t start, uint8_t stop);
  void startscrollleft(uint8_t start, uint8_t stop);

  void startscrolldiagright(uint8_t start, uint8_t stop);
  void startscrolldiagleft(uint8_t start, uint8_t stop);
  void stopscroll(void);

private:
  void WriteCommand(uint8_t c);
  void ssd1306_data(uint8_t c);
  void setPosition(uint8_t x, uint8_t y);
  void drawPixel(int16_t x, int16_t y, uint16_t color);//必须重载
};

#endif