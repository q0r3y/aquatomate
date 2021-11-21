#ifndef MY_FISH_H
#define MY_FISH_H
#include <Arduino.h>
class Fish {
  private:
    const byte NOON = 12;
    const byte MIDNIGHT = 23;
    bool hasBeenFed = false;
    byte amFeedTime = 7;
    byte pmFeedTime = 19;

  public:
    Fish();
    void reset();
    bool getFedStatus();
    void setFedStatus(bool status);
    byte getAmFeedTime();
    byte getPmFeedTime();
    void setAmFeedTime(byte time);
    void setPmFeedTime(byte time);
    bool areHungry(byte currentHour);
};
#endif
