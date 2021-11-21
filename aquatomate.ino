#include <ESP8266WiFi.h>
#include <DallasTemperature.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <OneWire.h>
//#include <Wire.h>
#include "LightSensor.h"
#include "Relay.h"
#include "Buzzer.h"
#include "Led.h"
#include "Fish.h"
#include "config.h"


#define VERSION 20211115

// Todo add light detection relay control
// Todo add button to turn on/off everything regardless of time/state
// Todo add screen
// Todo add thermometer
// Todo add leak detection
// Todo add mqtt capabilites, home base controller

Fish fish;
Relay relay(RELAY_PIN);
Led onboardLed(LED_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_FREQ);
//LightSensor lightSensor(PHOTORESISTOR_PIN);
WiFiUDP ntpUDP;
bool stateHasBeenResetThisHour = true;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
OneWire oneWire(TEMPERATURE_PIN);
//DallasTemperature temperatureSensor(&oneWire);
void ICACHE_RAM_ATTR feedButtonPressed();

void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.print("Aquatomate v");
  Serial.println(VERSION);
  setFeedButtonInterrupt();
//  temperatureSensor.begin();
  setWifi();
  setTimeClient();
}

void setFeedButtonInterrupt() {
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN),
                           feedButtonPressed, FALLING);
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

void feedButtonPressed() {
  fish.setFedStatus(true);
  buzzer.reset();
  buzzer.off();
  onboardLed.setState(relay.getState());
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
  buzzer.beepDuration(2000);
}

void setAquariumPmState() {
  relay.off();
  onboardLed.off();
  buzzer.beepDuration(2000);
}

void loop() {
  byte currentMinute = timeClient.getMinutes();
  byte currentHour = timeClient.getHours() - DAY_LIGHT_SAVINGS;
  bool isTimeToResetState = currentHour == SIX_AM ||
                            currentHour == NOON ||
                            currentHour == SIX_PM ||
                            currentHour == MIDNIGHT;

  //Serial.print(currentHour);
  //Serial.println(currentMinute);

  if (fish.areHungry(currentHour, currentMinute)) {
    Serial.println("Fish are Hungry");
    onboardLed.blinkOneSecond();
    buzzer.thirtyMinuteCountDown();
  }

  if (relay.shouldBeOn(currentHour, currentMinute)) {
    //Serial.println("Relay should be on");
    if (relay.getState() == false) {
      setAquariumAmState();
      Serial.println("Relay & LED On");
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
      Serial.println("Relay & LED Off");
      Serial.println(currentHour);
    }
  }

  if (isTimeToResetState) {
    if (!stateHasBeenResetThisHour) {
      resetState();
    }
  } else {
    stateHasBeenResetThisHour = false;
  }
}
