#include "Led.h"

Led::Led(byte pin) {
  this -> pin = pin;
  pinMode(pin, OUTPUT);
  on();
}

void Led::on() {
  this -> state = true;
  digitalWrite(pin, LOW);
}

void Led::off() {
  this -> state = false;
  digitalWrite(pin, HIGH);
}

void Led::inverse() {
  this -> state = !state;
  digitalWrite(pin, !state);
}

bool Led::getState() {
  return state;
}

void Led::setState(bool state) {
  this -> state = state;
  digitalWrite(pin, !state);
}

void Led::reset() {
  lastLedBlink = 0;
}

void Led::blinkOneSecond() {
  bool oneSecondPassed = millis() -
                         lastLedBlink >= oneSecond;
  if (oneSecondPassed) {
    inverse();
    lastLedBlink = millis();
  }
}

unsigned long Led::getLastLedBlink() {
  return lastLedBlink;
}

void Led::setLastLedBlink(unsigned long duration) {
  this -> lastLedBlink = duration;
}
