#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const byte Y_CHARACTER_OFFSET = 9;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("[-] SSD1306 allocation failed, Check screen connections");
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);
  display.print(F("Aquatomate "));
  display.print(VERSION);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void updateDisplay(byte currentHour, byte currentMinute) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Aquatomate "));
  display.print(VERSION);
  display.setCursor(0, Y_CHARACTER_OFFSET*1);
  display.print(F("Current Time: "));
  display.print(currentHour);
  display.print(F(":"));
  if (currentMinute < 10) { display.print(F("0")); }
  display.print(currentMinute);
  display.setCursor(0, Y_CHARACTER_OFFSET*6);
  display.print(F("Fed: "));
  display.print(fish.getFeedTimeHour());
  display.print(F(":"));
  if (fish.getFeedTimeMinute() < 10) { display.print(F("0")); }
  display.print(fish.getFeedTimeMinute());
  display.print(F(" | Temp: 79"));
  display.display();
}
