#ifndef MY_LED_H
#define MY_LED_H
#include <Arduino.h>
class Led {
  private:
    byte pin;
    bool state = true;
    unsigned long lastLedBlink = 0;
    const int oneSecond = 1000;

  public:
    Led(byte pin);
    void on();
    void off();
    void reset();
    void inverse();
    bool getState();
    void setState(bool state);
    void blinkOneSecond();
    unsigned long getLastLedBlink();
    void setLastLedBlink(unsigned long duration);
};
#endif
