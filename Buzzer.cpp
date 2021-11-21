#include "Buzzer.h"

Buzzer::Buzzer(byte pin, int frequency) {
  this -> pin = pin;
  this -> frequency = frequency;
  pinMode(pin, OUTPUT);
}

void Buzzer::on() {
  tone(pin, frequency);
}

void Buzzer::off() {
  noTone(pin);
}

void Buzzer::reset() {
  buzzerCountDownReset = false;
  buzzerCountDown = 0;
  buzzerDuration = 0;
  lastBuzzer = 0;
}

void Buzzer::beepDuration(unsigned long duration) {
  tone(pin, frequency, duration);
}

void Buzzer::thirtyMinuteCountDown() {
  if (!buzzerCountDownReset) {
    buzzerCountDown = millis();
    buzzerCountDownReset = true;
  }
  bool thirtyMinutesPassed = millis() -
                             buzzerCountDown >= THIRTY_MINUTES;

  if (thirtyMinutesPassed) { activateTenSeconds(); }
}

void Buzzer::activateTenSeconds() {
  bool tenSecondPassed = millis() -
                         lastBuzzer >= TEN_SECOND;
  bool oneSecondPassed = millis() -
                         buzzerDuration >= ONE_SECOND;
  if (oneSecondPassed) {
    off();
    buzzerDuration = millis();
  }
  if (tenSecondPassed) {
    on();
    lastBuzzer = millis();
  }
}
