#include "Fish.h"

Fish::Fish() {
}

bool Fish::areHungry(byte currentHour, byte currentMinute) {
  bool fishNeedFoodAm = ((currentHour == amFeedHour &&
                        currentMinute >= amFeedMinute) ||
                        (currentHour > amFeedHour &&
                        currentHour < NOON)) &&
                        !hasBeenFed;

  bool fishNeedFoodPm = (currentHour >= pmFeedHour &&
                        currentHour < MIDNIGHT) &&
                        !hasBeenFed;

  return (fishNeedFoodAm || fishNeedFoodPm);
}

void Fish::reset() {
  this -> hasBeenFed = false;
}

byte Fish::getAmFeedHour() {
  return amFeedHour;
}

byte Fish::getAmFeedMinute() {
  return amFeedMinute;
}

byte Fish::getPmFeedHour() {
  return pmFeedHour;
}

bool Fish::getFedStatus() {
  return hasBeenFed;
}

byte Fish::getFeedTimeHour() {
  return feedTimeHour;
}

byte Fish::getFeedTimeMinute() {
  return feedTimeMinute;
}

void Fish::setFeedTimeHour(byte hour) {
  this -> feedTimeHour = hour;
}

void Fish::setFeedTimeMinute(byte minute) {
  this -> feedTimeMinute = minute;
}

void Fish::setAmFeedHour(byte hour) {
  this -> amFeedHour = hour;
}

void Fish::setPmFeedHour(byte hour) {
  this -> pmFeedHour = hour;
}

void Fish::setAmFeedMinute(byte minute) {
  this -> amFeedMinute = minute;
}

void Fish::setFedStatus(bool status) {
  this -> hasBeenFed = status;
}
