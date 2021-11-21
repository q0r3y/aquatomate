#ifndef MY_RELAY_H
#define MY_RELAY_H
#include <Arduino.h>
class Relay {

  private:
    byte pin;
    bool state = true;
    byte amLightOnHour = 7;
    byte amLightOnMinute = 40;
    byte pmLightOffHour = 20;

  public:
    Relay(byte pin);
    void on();
    void off();
    bool getState();
    byte getAmLightOnHr();
    byte getAmLightOnMin();
    byte getPmLightOffHr();
    void setAmLightOnHr(byte hour);
    void setAmLightOnMin(byte minute);
    void setPmLightOffHr(byte hour);
    bool shouldBeOn(byte currentHour, byte currentMinute);
};
#endif
