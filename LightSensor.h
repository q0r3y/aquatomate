#ifndef MY_LIGHTSENSOR_H
#define MY_LIGHTSENSOR_H
#include <Arduino.h>
class LightSensor {

  private:
    byte pin;
    bool lightReadingAttempts = 0;

  public:
    LightSensor(byte pin);
    bool detectsNoLight();
    byte getAttempts();
    void setAttempts(byte attempts);
};
#endif
