#ifndef MY_BUZZER_H
#define MY_BUZZER_H
#include <Arduino.h>
class Buzzer {
  private:
    byte pin;
    int frequency;
    bool buzzerCountDownReset = false;
    unsigned long buzzerCountDown = 0;
    unsigned long buzzerDuration = 0;
    unsigned long lastBuzzer = 0;
    const int oneSecond = 1000;
    const int tenSecond = 1000*10;
    const unsigned long thirtyMinutes = 1000*1800;

  public:
    Buzzer(byte pin, int frequency);
    void on();
    void off();
    void reset();
    void thirtyMinuteCountDown();
    void activateTenSeconds();
};
#endif
