#include "Fish.h"

Fish::Fish() {
}

bool Fish::areHungry(byte currentHour) {
  bool fishNeedFoodAm = (currentHour >= amFeedTime &&
                        currentHour < NOON) &&
                        !hasBeenFed;

  bool fishNeedFoodPm = (currentHour >= pmFeedTime &&
                        currentHour < MIDNIGHT) &&
                        !hasBeenFed;

  return (fishNeedFoodAm || fishNeedFoodPm);
}

void Fish::reset() {
  this -> hasBeenFed = false;
}

byte Fish::getAmFeedTime() {
  return amFeedTime;
}

byte Fish::getPmFeedTime() {
  return pmFeedTime;
}

bool Fish::getFedStatus() {
  return hasBeenFed;
}

void Fish::setAmFeedTime(byte time) {
  this -> amFeedTime = time;
}

void Fish::setPmFeedTime(byte time) {
  this -> pmFeedTime = time;
}

void Fish::setFedStatus(bool status) {
  this -> hasBeenFed = status;
}
