#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_I2CDevice.h>
#include <Fonts/FreeMono9pt7b.h>
#include <SPI.h>
#include "img.h"

const uint16_t  Display_Color_Black        = 0x0000;
const uint16_t  Display_Color_Blue         = 0x001F;
const uint16_t  Display_Color_Red          = 0xF800;
const uint16_t  Display_Color_Green        = 0x07E0;
const uint16_t  Display_Color_Cyan         = 0x07FF;
const uint16_t  Display_Color_Magenta      = 0xF81F;
const uint16_t  Display_Color_Yellow       = 0xFFE0;
const uint16_t  Display_Color_White        = 0xFFFF;

#define cs   10
#define dc   9
#define rst  8

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
  tft.setSPISpeed(40000000);
  tft.setFont(&FreeMono9pt7b);
  tft.fillScreen(ST77XX_BLACK);
  tft.drawBitmap(0,0,logo_1,128,40, Display_Color_Red);
  tft.drawBitmap(25,17,logo_2,79,7, Display_Color_White);
}

void loop() {
  delay(200);
}
