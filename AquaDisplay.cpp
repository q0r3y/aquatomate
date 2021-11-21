#include "AquaDisplay.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

AquaDisplay::AquaDisplay(uint8_t width,
                         uint8_t height,
                         int8_t resetPin,
                         uint8_t i2cAddr) {
  this -> display = Adafruit_SSD1306(width, height, &Wire, resetPin);
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2cAddr)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(2000);
}


void AquaDisplay::testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}
