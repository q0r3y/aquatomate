#include "LightSensor.h"

LightSensor::LightSensor(byte pin) {
  this -> pin = pin;
}

bool LightSensor::detectsNoLight() {
  return false; // Need to limit the reading of this
}

byte LightSensor::getAttempts() {
  return lightReadingAttempts;
}

void LightSensor::setAttempts(byte attempts) {
  this -> lightReadingAttempts = attempts;
}
