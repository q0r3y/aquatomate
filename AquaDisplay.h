#ifndef MY_AQUA_DISPLAY_H
#define MY_AQUA_DISPLAY_H
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class AquaDisplay {

  private:
    Adafruit_SSD1306 display;

  public:
    AquaDisplay(uint8_t width,
                uint8_t height,
                int8_t resetPin,
                uint8_t i2cAddr);
    void testdrawrect();

};
#endif
