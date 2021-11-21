#include <ESP8266WiFi.h>
#include <DallasTemperature.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include "config.h"
#include "Relay.h"
#include "Buzzer.h"
#include "Led.h"
#include "Fish.h"

// https://roboticsbackend.com/arduino-object-oriented-programming-oop/

/** Globals **/
Fish fish;
Relay relay(RELAY_PIN);
Led onboardLed(LED_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_FREQ);
WiFiUDP ntpUDP;
bool stateHasBeenResetThisHour = true;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temperatureSensor(&oneWire);
void ICACHE_RAM_ATTR feedButtonPressed();

void setup() {
  delay(3000);
  Serial.begin(115200);
  temperatureSensor.begin();
  setInterruptPin();
  setWifi();
  setTimeClient();
}

void setInterruptPin() {
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN),
                           feedButtonPressed, FALLING);
}

void setWifi() {
  WiFi.begin(ssid, password);
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

void printTemperature() {
  // https://lastminuteengineers.com/ds18b20-arduino-tutorial/
  temperatureSensor.requestTemperatures();
  //print the temperature in Fahrenheit
  Serial.print((temperatureSensor.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");
}

void resetState() {
  Serial.println("Resetting state");
  fish.reset();
  buzzer.reset();
  onboardLed.reset();
  timeClient.update();
  stateHasBeenResetThisHour = true;
}

void loop() {
  byte currentMinute = timeClient.getMinutes();
  byte currentHour = timeClient.getHours() - DAY_LIGHT_SAVINGS;
  bool isTimeToResetState = currentHour == SIX_AM ||
                            currentHour == NOON ||
                            currentHour == SIX_PM ||
                            currentHour == MIDNIGHT;


  if (fish.areHungry(currentHour)) {
    onboardLed.blinkOneSecond();
    buzzer.thirtyMinuteCountDown();
  }

  if (relay.shouldBeOn(currentHour, currentMinute)) {
    if (relay.getState() == false) {
      Serial.println("Relay & LED On");
      Serial.println(currentHour);
      relay.on();
      onboardLed.on();
    }
  } else {
    if (relay.getState() == true) {
      Serial.println("Relay & LED Off");
      Serial.println(currentHour);
      relay.off();
      onboardLed.off();
    }
  }

  if (isTimeToResetState) {
    if (!stateHasBeenResetThisHour) { resetState(); }
  } else {
    stateHasBeenResetThisHour = false;
  }
}
