/** Defines **/
#define DEBUG 1
#define RELAY_ON HIGH
#define RELAY_OFF LOW
#define LED_ON LOW
#define LED_OFF HIGH
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x78
#define ASCII 48
#define RELAY_PIN D6
#define INTERRUPT_PIN D4
#define LED_PIN D0
#define TEMPERATURE_PIN D2
#define BUZZER_PIN D7
#define BUZZER_FREQ 1000
#define PHOTORESISTOR_PIN D3

/** Configuration **/
const byte NOON = 12;
const byte MIDNIGHT = 0;
const byte SIX_AM = 6;
const byte SIX_PM = 18;
const byte DAY_LIGHT_SAVINGS = 1;
const int THIRTY_SECONDS = 30*1000;
const char *SSID PROGMEM = "";
const char *PASSWORD PROGMEM = "";
unsigned long displayUpdateTimer = 0;
