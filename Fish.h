#ifndef MY_FISH_H
#define MY_FISH_H
#include <Arduino.h>
class Fish {
  private:
    const byte NOON = 12;
    const byte MIDNIGHT = 23;
    bool hasBeenFed = false;
    byte amFeedHour = 7;
    byte amFeedMinute = 41;
    byte pmFeedHour = 19;

  public:
    Fish();
    void reset();
    byte getAmFeedHour();
    byte getAmFeedMinute();
    byte getPmFeedHour();
    bool getFedStatus();
    void setFedStatus(bool status);
    void setAmFeedHour(byte hour);
    void setPmFeedHour(byte hour);
    void setAmFeedMinute(byte minute);
    bool areHungry(byte currentHour, byte currentMinute);
};
#endif
