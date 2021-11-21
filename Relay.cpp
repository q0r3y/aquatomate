#include "Relay.h"

Relay::Relay(byte pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
  on();
}

void Relay::on() {
  this->state = true;
  digitalWrite(pin, HIGH);
}

void Relay::off() {
  this->state = false;
  digitalWrite(pin, LOW);
}

bool Relay::shouldBeOn(byte currentHour, byte currentMinute) {
  bool relayShouldBeOn = (currentHour == amLightOnHour &&
                         currentMinute >= amLightOnMinute) ||
                         (currentHour > amLightOnHour &&
                         currentHour < pmLightOffHour);
  return relayShouldBeOn;
}

bool Relay::getState() {
  return state;
}

byte Relay::getAmLightOnHr() {
  return amLightOnHour;
}

byte Relay::getAmLightOnMin() {
  return amLightOnMinute;
}

byte Relay::getPmLightOffHr() {
  return pmLightOffHour;
}

void Relay::setAmLightOnHr(byte hour) {
  this->amLightOnHour = hour;
}

void Relay::setAmLightOnMin(byte minute) {
  this->amLightOnMinute = minute;
}

void Relay::setPmLightOffHr(byte hour) {
  this->pmLightOffHour = hour;
}
