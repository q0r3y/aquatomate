#include <ESP8266WiFi.h>
#include <DallasTemperature.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include "LightSensor.h"
#include "Relay.h"
#include "Buzzer.h"
#include "Button.h"
#include "Led.h"
#include "Fish.h"
#include "public_config.h"

#define VERSION 20211124

// Todo add light detection relay control
// Todo add button to turn on/off everything regardless of time/state
// Todo add screen
// Todo add thermometer
// Todo add leak detection
// Todo add mqtt capabilites, home base controller

Fish fish;
Relay relay(RELAY_PIN);
Led onboardLed(LED_PIN);
Button feedButton(INTERRUPT_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_FREQ);
WiFiUDP ntpUDP;
bool stateHasBeenResetThisHour = false;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
OneWire oneWire(TEMPERATURE_PIN);
//DallasTemperature temperatureSensor(&oneWire);

void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.print(F("Aquatomate v"));
  Serial.println(VERSION);
  initDisplay();
  setWifi();
  setTimeClient();
}

void setWifi() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to Wifi..");
  }
}

void setTimeClient() {
  timeClient.begin();
  timeClient.setTimeOffset(-14400);
  timeClient.update();
}

void setFeedState() {
  buzzer.reset();
  fish.setFedStatus(true);
  fish.setFeedTimeMinute(timeClient.getMinutes());
  fish.setFeedTimeHour(timeClient.getHours() - DAY_LIGHT_SAVINGS);
  onboardLed.setState(relay.getState());
  buzzer.off();
}

// void printTemperature() {
//   // https://lastminuteengineers.com/ds18b20-arduino-tutorial/
//   temperatureSensor.requestTemperatures();
//   float tempF = (temperatureSensor.getTempCByIndex(0) * 9.0) / 5.0 + 32.0;
//   Serial.print(tempF);
//   Serial.print((char)176); //shows degrees character
//   Serial.println("F");
// }

void resetState() {
  Serial.println("Resetting state");
  fish.reset();
  buzzer.reset();
  onboardLed.reset();
  timeClient.update();
  //lightSensor.setAttempts(0);
  stateHasBeenResetThisHour = true;
}

void setAquariumAmState() {
  relay.on();
  onboardLed.on();
  buzzer.beepDuration(500);
}

void setAquariumPmState() {
  relay.off();
  onboardLed.off();
  buzzer.beepDuration(500);
}

void loop() {
  byte currentMinute = timeClient.getMinutes();
  byte currentHour = timeClient.getHours() - DAY_LIGHT_SAVINGS;
  bool thirtySecondsPassed = millis() - displayUpdateTimer >= THIRTY_SECONDS;
  bool isTimeToResetState = currentHour == SIX_AM ||
                            currentHour == NOON ||
                            currentHour == SIX_PM ||
                            currentHour == MIDNIGHT;

  if (feedButton.isPressed()) {
    setFeedState();
  }

  if (fish.areHungry(currentHour, currentMinute)) {
    onboardLed.blinkOneSecond();
    buzzer.thirtyMinuteCountDown();
  }

  if (relay.shouldBeOn(currentHour, currentMinute)) {
    //Serial.println("Relay should be on");
    if (relay.getState() == false) {
      setAquariumAmState();
      Serial.println(F("Relay & LED On"));
      Serial.println(currentHour);
    }
    // else if (lightSensor.detectsNoLight() && lightSensor.getAttempts() < 3) {
    //   relay.off();
    //   delay(10000); // Ten seconds
    //   relay.on();
    // }
  } else {
    if (relay.getState() == true) {
      setAquariumPmState();
    }
  }

  if (isTimeToResetState) {
    if (!stateHasBeenResetThisHour) {
      resetState();
    }
  } else {
    stateHasBeenResetThisHour = false;
  }

  if (thirtySecondsPassed) {
    Serial.println(F("Updating Display"));
    updateDisplay(currentHour, currentMinute);
    displayUpdateTimer = millis();
  }
}
