#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SH1106.h"

Adafruit_SSD1306 display;

void testdrawchar(void)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++)
  {
    if (i == '\n')
      continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}

void setup()
{
  Serial.begin(9600);
  display.begin();
}

void loop()
{

  display.clearDisplay();
  // draw the first ~12 characters in the font
  testdrawchar();
  display.display();
  delay(2000);

  //draw line test
  display.clearDisplay();
  for (int16_t i = 0; i < display.width(); i += 4)
  {
    display.drawLine(0, 0, i, display.height() - 1, WHITE);
    display.display();
  }
  delay(2000);

  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 0); //x=0-131,y=0-63
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  delay(2000);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(" 0x");
  display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);

  // invert the display
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
}
